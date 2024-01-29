/*
�@�N���X�F���ƌ��̐���
  �쐬�ҁF�O�Y����
  �쐬���F�P/�P�@�@�@�@
*/
#include "BoxExplanation.h"
#include"../../GameData/GameData.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
BoxExplanation::BoxExplanation(GameData* pGameData)
{
	mpStage = new Stage(pGameData->GetStageSelect(),Stage::MODE::THUTRIAL,pGameData);
	pGameData->GameDataReset();
	mpGameData = pGameData;
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
BoxExplanation::~BoxExplanation()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void BoxExplanation::Initialize()
{
	//���b�Z�[�W�pCSV�t�@�C���̓ǂݍ���
	LoadCSV(0,9);

	//���b�Z�[�W�N���X�̎��̉�
	mpSM = new ScrollMassage();

	//�X�e�[�W�N���X�̏�����
	mpStage->Initialize();
	mpStage->Update();
}

/*--------------------------------------------------
�X�V
--------------------------------------------------*/
void BoxExplanation::Update()
{
	if (mMessage.size() - 2 == mCounter)
		mPlayFlag = true;
	if (mPlayFlag == true)
	{
		mpStage->SetTimerLimit(0);

		mpStage->Update();
	}
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void BoxExplanation::Draw()
{
	mpStage->Draw();

	DrawBox(SCREEN_LEFT, SCREEN_BOTTOM - 150, SCREEN_RIGHT - 128, SCREEN_BOTTOM, GetColor(0, 0, 0), true);
	int defaultSize = GetFontSize();

	SetFontSize(30);

	DrawFormatString(SCREEN_LEFT + 40, SCREEN_BOTTOM - 140, GetColor(255, 0, 0), "�`���[�g���A���F�N���A�����ɂ���");

	SetFontSize(defaultSize);
	mpSM->SetMessage(mMessage[mCounter].mMessage,
					 mMessage[mCounter].mPos,
					 mMessage[mCounter].mColor,
					 mMessage[mCounter].mSize,
					 mMessage[mCounter].mVel,
					 mMessage[mCounter].mLine,
					 mMessage[mCounter].mType);

	int MSize = mMessage.size() - 2;
	if (mpSM->DrawScrollMassage() == true && IsButtonPressed(PAD_INPUT_1)&& MSize > mCounter)
	{
			mpSM->Reset();
			mCounter++;
	}

	MSize = mMessage.size() - 1;
	if (mpStage->KeyCheckFlag() == true && MSize > mCounter)
	{
		mpSM->Reset();
		mCounter++;
	}

	MSize = mMessage.size() - 2;
	if (IsButtonPressed(PAD_INPUT_2) && MSize >= mCounter)
		mpSM->DrawMassageAll();
	
	
}

/*--------------------------------------------------
�I���t���O
--------------------------------------------------*/
Explanation::THUTRIAL BoxExplanation::FinalFlag()
{
	if(mpStage->GameEnd()==Stage::RESULTSCENE::THUTRIAL)
		return Explanation::THUTRIAL::BOX;
	return Explanation::THUTRIAL::NONE;
}
