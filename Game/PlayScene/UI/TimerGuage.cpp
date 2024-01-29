/*
�@�N���X�F��������
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/9�@�@�@�@
*/
#include"TimerGuage.h"
#include"../Player/Player.h"
#include"../../GameMain.h"
#include"../../GameData/GameData.h"

//=============================================
//			�R���X�g���N�^
//=============================================
TimerGuage::TimerGuage(GameData* pGameData):mTimerLimit{}
{
	mpGameData = pGameData;
}

//=============================================
//			�f�X�g���N�^
//=============================================
TimerGuage::~TimerGuage()
{

}

//=============================================
//			������
//=============================================
void TimerGuage::Initialize()
{
	//�v���[���[�N���X�̃A�h���X�擾
	mpPlayer = GetpPlayer();

	//�������Ԃ̎擾
	mTimerLimit = mpPlayer->GetTimerLimit();
}

//=============================================
//			�X�V
//=============================================
void TimerGuage::Update()
{
	//�������Ԃ̎擾
	mTimerLimit = mpPlayer->GetTimerLimit();
}

//=============================================
//			�`��
//=============================================
void TimerGuage::Draw()
{
	//�w�i=================================================================================
	DrawBox(SCREEN_RIGHT - 128, 192, SCREEN_RIGHT, SCREEN_BOTTOM, GetColor(255, 0, 0), true);
	DrawBox(SCREEN_RIGHT - 128, 192, SCREEN_RIGHT, 256, GetColor(0, 0, 255), true);
	//===================================================================================

	//���Ԃ̕\��=================================================================================================
	int defaultSize = GetFontSize();

	SetFontSize(40);

	DrawFormatString(SCREEN_RIGHT - 110, 204, GetColor(0, 0, 0), "%d�F%02d", mTimerLimit / 3600, (mTimerLimit / 60) - (((mTimerLimit / 3600)) * 60));

	SetFontSize(defaultSize);
	//===============================================================================================

	//���Ԃ̃o�[�̕`��============================================================================================
	//�o�[���Z���Ȃ�قǍ����甒�ɕω�����
	if (mpGameData->GetStageSelect() != static_cast<int>(GameData::STAGE::FINALSTAGE))
	{
		int num = GameData::TIME / 255;
		int TimeRate = GameData::TIME / 450;
		int Color = (255 - (mTimerLimit / (num + 1)));
		if (Color > 255)
			Color = 255;
		DrawBox(SCREEN_RIGHT - 120, 264, SCREEN_RIGHT - 8, SCREEN_BOTTOM - 8, GetColor(255, 255, 255), true);
		DrawBox(SCREEN_RIGHT - 120, static_cast<int>(SCREEN_BOTTOM - (mTimerLimit / TimeRate)) + 8, SCREEN_RIGHT - 8, SCREEN_BOTTOM - 8,GetColor(Color, Color, Color), true);
	}
	else
	{
		int num = GameData::FINALSTAGE_TIME / 255;
		int TimeRate = GameData::FINALSTAGE_TIME / 450;
		int Color = (255 - (mTimerLimit / (num + 1)));
		if (Color > 255)
			Color = 255;
		DrawBox(SCREEN_RIGHT - 120, 264, SCREEN_RIGHT - 8, SCREEN_BOTTOM - 8, GetColor(255, 255, 255), true);
		DrawBox(SCREEN_RIGHT - 120, static_cast<int>(SCREEN_BOTTOM - (mTimerLimit / TimeRate)) + 8, SCREEN_RIGHT - 8, SCREEN_BOTTOM - 8,GetColor(Color, Color, Color), true);
	}
	//================================================================================================================
}