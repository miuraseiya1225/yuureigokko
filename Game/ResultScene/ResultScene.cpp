/*
���U���g�V�[��
*/
#include"ResultScene.h"

#include "../GameMain.h"
#include"../Resource/Resource.h"
#include"../GameData/GameData.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
ResultScene::ResultScene(GameData* pGameData)
	:mFlow{FLOW::INITIALIZE}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
ResultScene::~ResultScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void ResultScene::Initialize()
{
	//���\�[�X�}�l�[�W���[�̃C���X�^���X���擾����
	ResourceManager* Resource = ResourceManager::GetInstance();

	//�摜�����\�[�X�}�l�[�W���[�ɓo�^���ĉ摜�n���h�����擾����
	mTexture = Resource->LoadTexture(eTEXTURE::RESULT_LOGO, "clear.png");

	mSprite[0].SetTexture(mTexture);
	mSprite[0].src.x = 0;
	mSprite[0].src.y = 0;
	mSprite[0].size.x = 819;
	mSprite[0].size.y = 136;
	mSprite[0].scale.x = 1.5f;
	mSprite[0].scale.y = 1.5f;
	mSprite[0].pos.x = SCREEN_CENTER_X;
	mSprite[0].pos.y = SCREEN_CENTER_Y - 200;

	//�摜�����\�[�X�}�l�[�W���[�ɓo�^���ĉ摜�n���h�����擾����
	mTexture = Resource->LoadTexture(eTEXTURE::RESULT_BACK, "ResultBack.png");
	mSprite[1].SetTexture(mTexture);
	mSprite[1].src.x = 0;
	mSprite[1].src.y = 0;
	mSprite[1].size.x = SCREEN_RIGHT;
	mSprite[1].size.y = SCREEN_BOTTOM;
	mSprite[1].pos.x = SCREEN_CENTER_X;
	mSprite[1].pos.y = SCREEN_CENTER_Y;

	mpScore = new Score(mpGameData);
	mpScore->Initialize();
}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
--------------------------------------------------*/
GAME_SCENE ResultScene::Update()
{
	switch (mFlow)
	{
		case FLOW::INITIALIZE:
		{
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
			if (IsButtonPressed(PAD_INPUT_1) && mpScore->NextFlag() == true)
				mFlow = FLOW::FADE_OUT;

			mpGameData->OutputData();

			mpScore->Update();
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

			return GAME_SCENE::TITLE;
			break;
		}
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void ResultScene::Draw()
{
	mSprite[1].Draw();

	mSprite[0].Draw();

	mpScore->Draw();
}

/*--------------------------------------------------
�I������
--------------------------------------------------*/
void ResultScene::Finalize()
{
	delete mpScore;
	mpScore = nullptr;
}

void ResultScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
}
