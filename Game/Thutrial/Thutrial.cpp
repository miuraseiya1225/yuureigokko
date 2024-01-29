#include"Thutrial.h"

#include "../GameMain.h"
#include"Explanation/BoxExplanation.h"
#include"Explanation/EnemyExplanation.h"
#include"Explanation/StageExplanation.h"

#include"../GameData/GameData.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
ThutrialScene::ThutrialScene(GameData* pGameData)
	:mFlow{ FLOW::INITIALIZE }
	,mpGameData{pGameData}
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
ThutrialScene::~ThutrialScene()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void ThutrialScene::Initialize()
{
	mpGameData->SetStageSelect(GameData::STAGE::THUTRIAL1);

	mpExplanation = new BoxExplanation(mpGameData);
	mpExplanation->Initialize();

}

/*--------------------------------------------------
�X�V
�߂�l	:���̃V�[���ԍ�
--------------------------------------------------*/
GAME_SCENE ThutrialScene::Update()
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
			bool res = FadeInUpdate(FADE_TIME);

			if (res == false)
				mFlow = FLOW::MAIN;
			break;
		}
		case FLOW::MAIN:
		{
			if (IsButtonPressed(PAD_INPUT_4))
				mFlow = FLOW::FADE_OUT;

			mpExplanation->Update();

			Next();

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
void ThutrialScene::Draw()
{
	mpExplanation->Draw();
}

/*--------------------------------------------------
�I������
--------------------------------------------------*/
void ThutrialScene::Finalize()
{
	mpExplanation->Finalize();

	delete mpExplanation;
	mpExplanation = nullptr;
}

/*--------------------------------------------------
���̐�����
--------------------------------------------------*/
void ThutrialScene::Next()
{
	//�������I�������f���[�g���Ď��̐����̃R���X�g���N�^�Ŏ��̉�����

	switch (mpExplanation->FinalFlag())
	{
		case Explanation::THUTRIAL::BOX:
		{
			Reset();

			mpExplanation->Finalize();

			delete mpExplanation;
			mpExplanation = nullptr;

			mpGameData->SetStageSelect(GameData::STAGE::THUTRIAL2);

			mpExplanation = new EnemyExplanation(mpGameData);
			mpExplanation->Initialize();
			break;
		}
		case Explanation::THUTRIAL::ENEMY:
		{
			Reset();

			mpExplanation->Finalize();

			delete mpExplanation;
			mpExplanation = nullptr;

			mpGameData->SetStageSelect(GameData::STAGE::THUTRIAL3);

			mpExplanation = new StageExplanation(mpGameData);
			mpExplanation->Initialize();
			break;
		}
		case Explanation::THUTRIAL::STAGE:
		{
			Reset();

			mFlow = FLOW::FADE_OUT;
		}
		default:
			break;
	}
}

/*--------------------------------------------------
���Z�b�g
--------------------------------------------------*/
void ThutrialScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
}