/*
�^�C�g���V�[��
*/
#include "TitleScene.h"
#include "../GameMain.h"

#include"../Resource/Resource.h"

//�v���[���[�̕`����W
static const int PLAYER_POSX = SCREEN_RIGHT - 300;
static const int PLAYER_POSY = SCREEN_TOP + 150;

//�^�C�g���̕`����W
static const int TITLE_POSX = SCREEN_CENTER_X-400;
static const int TITLE_POSY = SCREEN_CENTER_Y+30;

//�G�̕`����W
static const int ENEMY_POSX = SCREEN_CENTER_X - 50;
static const int ENEMY_POSY = SCREEN_TOP + 150;
/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
TitleScene::TitleScene() :mState{STATE::START},mFlow{FLOW::INITIALIZE},mTimer{},mpTL{},mColor3{}
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
TitleScene::~TitleScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void TitleScene::Initialize()
{
	//���\�[�X�}�l�[�W���[�̃C���X�^���X���擾����
	ResourceManager* Resource = ResourceManager::GetInstance();

	//�����擾
	mAudio = Resource->LoadAudio(eAUDIO::TITLE, "TitleBGM.mp3");
	mPushAudio = Resource->LoadAudio(eAUDIO::SCORE, "Push.mp3");

	//�摜�����\�[�X�}�l�[�W���[�ɓo�^���ĉ摜�n���h�����擾����
	mTexture = Resource->LoadTexture(eTEXTURE::CHARA, "Player.png");

	mSprite[0].SetTexture(mTexture);
	mSprite[0].src.x = 0;
	mSprite[0].src.y = 80;
	mSprite[0].size.x = 40;
	mSprite[0].size.y = 40;
	mSprite[0].scale.x = 0.8f * 5.0f;
	mSprite[0].scale.y = 0.8f * 5.0f;

	mSprite[0].pos.x = PLAYER_POSX;
	mSprite[0].pos.y = PLAYER_POSY;

	//�摜�����\�[�X�}�l�[�W���[�ɓo�^���ĉ摜�n���h�����擾����
	mTexture = Resource->LoadTexture(eTEXTURE::TITLE, "Title.png");

	mSprite[1].SetTexture(mTexture);
	mSprite[1].src.x = 0;
	mSprite[1].src.y = 0;
	mSprite[1].size.x = 95;
	mSprite[1].size.y = 490;
	mSprite[1].scale.x = 1.5f;
	mSprite[1].scale.y = 1.5f;
	mSprite[1].pos.x = TITLE_POSX;
	mSprite[1].pos.y = TITLE_POSY;

	mTexture = Resource->LoadTexture(eTEXTURE::NORMALLIGHT, "NormalGhostAll.png");

	mSprite[2].SetTexture(mTexture);
	mSprite[2].src.x = 0;
	mSprite[2].src.y = 32;
	mSprite[2].size.x = 32;
	mSprite[2].size.y = 32;
	mSprite[2].scale.x = 5.0f;
	mSprite[2].scale.y = 5.0f;
	mSprite[2].pos.x = ENEMY_POSX;
	mSprite[2].pos.y = ENEMY_POSY;
	
	//�}�X�N�N���X�̎��̉��Ə�����
	mpMask = new Mask();
	mpMask->Initialize();

	//�w�i���[�v�N���X�̎��̉��Ə�����
	mpTL = new TitleLoad();
	mpTL->Initialize();

	//���N���X�̎��̉��Ə�����	
	mpMist = new Mist();
	mpMist->Initialize();

	mPos[0].mX = PLAYER_POSX;
	mPos[0].mY = PLAYER_POSY;

	mPos[1].mX = ENEMY_POSX;
	mPos[1].mY = ENEMY_POSY;
}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
--------------------------------------------------*/
GAME_SCENE TitleScene::Update()
{
	switch (mFlow)
	{
		case FLOW::INITIALIZE:
		{
			PlaySoundMem(mAudio, DX_PLAYTYPE_LOOP);

			Reset();

			mFlow = FLOW::FADE_IN;

			SetFadeOut();
			break;
		}
		case FLOW::FADE_IN:
		{
			int res = FadeInUpdate(FADE_TIME);

			if (res == false)
				mFlow = FLOW::MAIN;
			break;
		}
		case FLOW::MAIN:
		{
			//�㉺�L�[�ŃV�[����I���ł���悤�ɂ���=================================
			if (IsButtonPressed(PAD_INPUT_DOWN) && mState == STATE::EXPLANATION)
				mState = STATE::END;

			if (IsButtonPressed(PAD_INPUT_DOWN) && mState == STATE::START)
				mState = STATE::EXPLANATION;

			if (IsButtonPressed(PAD_INPUT_UP) && mState == STATE::EXPLANATION)
				mState = STATE::START;

			if (IsButtonPressed(PAD_INPUT_UP) && mState == STATE::END)
				mState = STATE::EXPLANATION;
			//======================================================================



			if (IsButtonPressed(PAD_INPUT_1))
			{
				PlaySoundMem(mPushAudio, DX_PLAYTYPE_BACK);
				mFlow = FLOW::FADE_OUT;

			}
			CharaMotion();

			mpMask->SetAlpha(mPos[0], 0.005f);
			mpMask->SetAlpha(mPos[1], 0.005f);
			mpTL->Update();
			mpMist->Update();
			break;
		}
		case FLOW::FADE_OUT:
		{
			//�t�F�[�h�̍X�V
			int res = FadeOutUpdate(FADE_TIME);

			//�t�F�[�h���I�������玟�̏�Ԃ�
			if (res == false)
				mFlow = FLOW::FINALIZE;

			break;
		}
		case FLOW::FINALIZE:
		{
			mFlow = FLOW::INITIALIZE;

			if(mState==STATE::START)
				return GAME_SCENE::SELECT;
			if (mState == STATE::EXPLANATION)
				return GAME_SCENE::THUTRIAL;
			if (mState == STATE::END)
				mEndFlag = true;
			break;
		}
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void TitleScene::Draw()
{
	DrawBox(0, 0, SCREEN_RIGHT, SCREEN_BOTTOM, GetColor(128, 128, 128), true);

	mpTL->Draw();
	mSprite[0].Draw();
	mSprite[2].Draw();

	mpMask->Draw();

	int defaultSize = GetFontSize();

	SetFontSize(80);

	for (int i = 0; i < 3; i++)
	{
		mColor3[i].mRed = 255;
		mColor3[i].mGreen = 255;
		mColor3[i].mBlue = 255;
	}

	if (mState == STATE::START)
	{
		mColor3[0].mRed = 255;
		mColor3[0].mGreen = 0;
		mColor3[0].mBlue = 0;
	}
	if (mState == STATE::EXPLANATION)
	{
		mColor3[1].mRed = 255;
		mColor3[1].mGreen = 0;
		mColor3[1].mBlue = 0;
	}
	if (mState == STATE::END)
	{
		mColor3[2].mRed = 255;
		mColor3[2].mGreen = 0;
		mColor3[2].mBlue = 0;
	}

	DrawFormatString(SCREEN_CENTER_X -150, SCREEN_CENTER_Y  -50 , GetColor(mColor3[0].mRed, mColor3[0].mGreen, mColor3[0].mBlue), "�X�e�[�W�I����ʂ�");
	DrawFormatString(SCREEN_CENTER_X -150, SCREEN_CENTER_Y + 100, GetColor(mColor3[1].mRed, mColor3[1].mGreen, mColor3[1].mBlue), "�`���[�g���A��");
	DrawFormatString(SCREEN_CENTER_X -150, SCREEN_CENTER_Y + 250, GetColor(mColor3[2].mRed, mColor3[2].mGreen, mColor3[2].mBlue), "�I��");

	SetFontSize(defaultSize);
		
	mSprite[1].Draw();

	mpMist->Draw();
}

/*--------------------------------------------------
�I������
--------------------------------------------------*/
void TitleScene::Finalize()
{
	delete mpMask;
	delete mpMist;
	delete mpTL;

	mpMask = nullptr;
	mpMist = nullptr;
	mpTL = nullptr;
}

/*--------------------------------------------------
���Z�b�g
--------------------------------------------------*/
void TitleScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
	mState = STATE::START;
}

/*--------------------------------------------------
�L�����̃A�j���[�V����
--------------------------------------------------*/
void TitleScene::CharaMotion()
{
	mTimer++;
	
	if (mTimer == 12 )
	{
		mSprite[0].src.x += 80;
		mSprite[2].src.x += 64;
	}

	if (mTimer >= 24)
	{
		mSprite[0].src.x -= 80;
		mSprite[2].src.x -= 64;

		mTimer = 0;
	}
}

