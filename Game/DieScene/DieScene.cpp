/*
���U���g�V�[��
*/
#include"DieScene.h"

#include "../GameMain.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
DieScene::DieScene():mpBlood{},mModeSelect{MODE_SELECT::PLAY},mFlow{FLOW::MAIN},mColor3{}
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
DieScene::~DieScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void DieScene::Initialize()
{
	//���\�[�X�}�l�[�W���[
	ResourceManager* prm = ResourceManager::GetInstance();

	mPushAudio = prm->LoadAudio(eAUDIO::SCORE, "Push.mp3");

	//�摜�̓ǂݍ���
	mTexture = prm->LoadTexture(eTEXTURE::GAMEOVER_LOGO, "GameOver.png");

	//�摜�̐ݒ�========================================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 549;
	mSprite.size.y = 123;
	mSprite.scale.x = 2.0f;
	mSprite.scale.y = 2.0f;
	mSprite.pos.x = SCREEN_CENTER_X;
	mSprite.pos.y = SCREEN_TOP + 150;
	//=============================================================

	//���N���X�̎��̉��Ə�����=======
	mpBlood = new Blood();
	mpBlood->Initialize();
	//=========================-----

	FadeInUpdate(1.0f);
}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
--------------------------------------------------*/
GAME_SCENE DieScene::Update()
{
	switch (mFlow)
	{
		case FLOW::MAIN:
		{			
			//�F�̏�����==================
			for (int i = 0; i < 2; i++)
			{
				mColor3[i].mRed = 255;
				mColor3[i].mGreen = 255;
				mColor3[i].mBlue = 255;
			}
			//=============================

			//���̍X�V
			if (mpBlood->End() == false)
				mpBlood->Update();
			else
			{
				//�V�[���I��=============================
				if (IsButtonPressed(PAD_INPUT_UP))
					mModeSelect = MODE_SELECT::PLAY;
				if (IsButtonPressed(PAD_INPUT_DOWN))
					mModeSelect = MODE_SELECT::TITLE;

				switch (mModeSelect)
				{
					case MODE_SELECT::PLAY:
					{
						mColor3[0].mRed = 255;
						mColor3[0].mGreen = 0;
						mColor3[0].mBlue = 255;
						break;
					}
					case MODE_SELECT::TITLE:
					{
						mColor3[1].mRed = 255;
						mColor3[1].mGreen = 0;
						mColor3[1].mBlue = 255;
						break;
					}
					default:
						break;
				}
				//=====================================-

				if (IsButtonPressed(PAD_INPUT_1))
				{
					PlaySoundMem(mPushAudio, DX_PLAYTYPE_BACK);
					mFlow = FLOW::FADE_OUT;
				}
			}
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
			Reset();

			//���̃V�[����================================
			if(mModeSelect==MODE_SELECT::PLAY)
				return GAME_SCENE::PLAY;
			if (mModeSelect == MODE_SELECT::TITLE)
				return GAME_SCENE::TITLE;
			//===========================================

			break;
		}
	}
	
	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void DieScene::Draw()
{
	//���̕`��
	mpBlood->Draw();

	//�����Ȃǂ̕`��===============================================================================================================================================
	if (mpBlood->End() == true)
	{
		mSprite.Draw();

		int defaultSize = GetFontSize();

		SetFontSize(120);

		DrawFormatString(SCREEN_CENTER_X - 400, (SCREEN_CENTER_Y - 100), GetColor(mColor3[0].mRed, mColor3[0].mGreen, mColor3[0].mBlue), "�R���e�B�j���[");
		DrawFormatString(SCREEN_CENTER_X - 300, (SCREEN_CENTER_Y + 100), GetColor(mColor3[1].mRed, mColor3[1].mGreen, mColor3[1].mBlue), "�^�C�g����");

		SetFontSize(defaultSize);
	}
	//==============================================================================================================================================================
}

/*--------------------------------------------------
�I������
--------------------------------------------------*/
void DieScene::Finalize()
{
	delete mpBlood;
	mpBlood = nullptr;
}

void DieScene::Reset()
{
	mFlow = FLOW::MAIN;
}
