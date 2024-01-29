/*
�@�N���X�F�G�̐���
  �쐬�ҁF�O�Y����
  �쐬���F�P/�P�@�@�@�@
*/

#include "EnemyExplanation.h"
#include"../../GameData/GameData.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
EnemyExplanation::EnemyExplanation(GameData* pGameData)
{
	mpStage = new Stage(pGameData->GetStageSelect(), Stage::MODE::THUTRIAL2,pGameData);
	pGameData->GameDataReset();
	mpGameData = pGameData;

}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
EnemyExplanation::~EnemyExplanation()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void EnemyExplanation::Initialize()
{
	//���b�Z�[�W�pCSV�t�@�C���̓ǂݍ���

	LoadCSV(10,14);

	//���b�Z�[�W�N���X�̎��̉�
	mpSM = new ScrollMassage();

	//�X�e�[�W�N���X�̏�����
	mpStage->Initialize();
	mpStage->SetTimerLimit(0);

	mpStage->Update();
}

/*--------------------------------------------------
�X�V
--------------------------------------------------*/
void EnemyExplanation::Update()
{
	if (mMessage.size() - 1 == mCounter)
		mPlayFlag = true;

	
	if (mPlayFlag == true)
	{
		mpStage->Update();
	}
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void EnemyExplanation::Draw()
{
	mpStage->Draw();
	DrawBox(SCREEN_LEFT, SCREEN_BOTTOM - 150, SCREEN_RIGHT - 128, SCREEN_BOTTOM, GetColor(0, 0, 0), true);
	int defaultSize = GetFontSize();

	SetFontSize(30);

	DrawFormatString(SCREEN_LEFT + 40, SCREEN_BOTTOM - 140, GetColor(255, 0, 0), "�`���[�g���A���F�G�ɂ���");

	SetFontSize(defaultSize);
	mpSM->SetMessage(mMessage[mCounter].mMessage,
		mMessage[mCounter].mPos,
		mMessage[mCounter].mColor,
		mMessage[mCounter].mSize,
		mMessage[mCounter].mVel,
		mMessage[mCounter].mLine,
		mMessage[mCounter].mType);

	int MSize= mMessage.size() - 1;
	if (mpSM->DrawScrollMassage() == true && IsButtonPressed(PAD_INPUT_1) && MSize > mCounter)
	{
		mpSM->Reset();
		mCounter++;
	}

	if (IsButtonPressed(PAD_INPUT_2) && MSize >= mCounter)
		mpSM->DrawMassageAll();
}

/*--------------------------------------------------
�I���t���O
--------------------------------------------------*/
Explanation::THUTRIAL EnemyExplanation::FinalFlag()
{
	if (mpStage->GameEnd() == Stage::RESULTSCENE::THUTRIAL2)
		return Explanation::THUTRIAL::ENEMY;
	return Explanation::THUTRIAL::NONE;
}