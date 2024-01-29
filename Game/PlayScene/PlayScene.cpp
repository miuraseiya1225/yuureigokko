/*
�v���C�V�[��
*/
#include "PlayScene.h"

#include "../GameMain.h"
#include"../GameData/GameData.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
PlayScene::PlayScene(GameData* pGameData):mpStage{},mFlow{FLOW::INITIALIZE},mNext{NEXT::GOAL}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
PlayScene::~PlayScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void PlayScene::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�����f�[�^�擾
	mAudio = prm->LoadAudio(eAUDIO::ROOM, "kimoroop3.wav");

	//�X�e�[�W�N���X�̎��̉��Ə�����
	mpStage = new Stage(mpGameData->GetStageSelect(),Stage::MODE::PLAY,mpGameData);
	mpStage->Initialize();

	//BGM
	PlaySoundMem(mAudio, DX_PLAYTYPE_LOOP, true);
}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
--------------------------------------------------*/
GAME_SCENE PlayScene::Update()
{
	switch (mFlow)
	{
		case FLOW::INITIALIZE:
		{
			Reset();

			mpGameData->GameDataReset();

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
			//�������Ԃ̎擾
			mpStage->SetTimerLimit(mpGameData->SubTimerLimit());

			//�X�V
			mpStage->Update();

			//�S�[�������烊�U���g��
			if (mpStage->GameEnd() == Stage::RESULTSCENE::GOAL)
			{
				StopSoundMem(mAudio);
				mFlow = FLOW::FADE_OUT;
				mNext = NEXT::GOAL;
			}
			//�G�ɕ߂܂����玀�S�V�[����
			else if (mpStage->GameEnd() == Stage::RESULTSCENE::DIE)
			{
				StopSoundMem(mAudio);
				mFlow = FLOW::FADE_OUT;
				mNext = NEXT::DIE;

				return GAME_SCENE::DIE;
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

			if(mNext==NEXT::GOAL)
				return GAME_SCENE::RESULT;

			if (mNext == NEXT::DIE)
				return GAME_SCENE::DIE;
			break;
		}
	}

#if defined(_DEBUG)
	if (IsButtonPressed(PAD_INPUT_10) == TRUE)
	{
		StopSoundMem(mAudio);
		return GAME_SCENE::RESULT;
	}
#endif

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void PlayScene::Draw()
{
	mpStage->Draw();
}

/*--------------------------------------------------
�I������
--------------------------------------------------*/
void PlayScene::Finalize()
{

	mpStage->Finalize();

	delete mpStage;
	mpStage = nullptr;
}

void PlayScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
}
