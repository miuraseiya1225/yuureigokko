/*
　クラス：制限時間
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/9　　　　
*/
#include"TimerGuage.h"
#include"../Player/Player.h"
#include"../../GameMain.h"
#include"../../GameData/GameData.h"

//=============================================
//			コンストラクタ
//=============================================
TimerGuage::TimerGuage(GameData* pGameData):mTimerLimit{}
{
	mpGameData = pGameData;
}

//=============================================
//			デストラクタ
//=============================================
TimerGuage::~TimerGuage()
{

}

//=============================================
//			初期化
//=============================================
void TimerGuage::Initialize()
{
	//プレーヤークラスのアドレス取得
	mpPlayer = GetpPlayer();

	//制限時間の取得
	mTimerLimit = mpPlayer->GetTimerLimit();
}

//=============================================
//			更新
//=============================================
void TimerGuage::Update()
{
	//制限時間の取得
	mTimerLimit = mpPlayer->GetTimerLimit();
}

//=============================================
//			描画
//=============================================
void TimerGuage::Draw()
{
	//背景=================================================================================
	DrawBox(SCREEN_RIGHT - 128, 192, SCREEN_RIGHT, SCREEN_BOTTOM, GetColor(255, 0, 0), true);
	DrawBox(SCREEN_RIGHT - 128, 192, SCREEN_RIGHT, 256, GetColor(0, 0, 255), true);
	//===================================================================================

	//時間の表示=================================================================================================
	int defaultSize = GetFontSize();

	SetFontSize(40);

	DrawFormatString(SCREEN_RIGHT - 110, 204, GetColor(0, 0, 0), "%d：%02d", mTimerLimit / 3600, (mTimerLimit / 60) - (((mTimerLimit / 3600)) * 60));

	SetFontSize(defaultSize);
	//===============================================================================================

	//時間のバーの描画============================================================================================
	//バーが短くなるほど黒から白に変化する
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