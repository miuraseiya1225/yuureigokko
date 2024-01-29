/*
　クラス：ステージの説明
  作成者：三浦聖矢
  作成日：１/2　　　　
*/
#include "StageExplanation.h"
#include"../../GameData/GameData.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
StageExplanation::StageExplanation(GameData* pGameData)
{
	mpStage = new Stage(pGameData->GetStageSelect(), Stage::MODE::THUTRIAL3,pGameData);
	mpGameData = pGameData;
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
StageExplanation::~StageExplanation()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void StageExplanation::Initialize()
{
	//メッセージ用CSVファイルの読み込み
	LoadCSV(15, 22);

	//メッセージクラスの実体化
	mpSM = new ScrollMassage();

	//ステージクラスの初期化
	mpStage->Initialize();
	mpStage->SetTimerLimit(mpGameData->GetTimerLimit());

	mpStage->Update();
	mpStage->Update();
}

/*--------------------------------------------------
更新
--------------------------------------------------*/
void StageExplanation::Update()
{
	if (mMessage.size() - 1 == mCounter)
		mPlayFlag = true;

	if (mPlayFlag == true)
	{
		mpStage->Update();
		mpStage->SetTimerLimit(mpGameData->SubTimerLimit());
	}
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void StageExplanation::Draw()
{
	mpStage->Draw();
	DrawBox(SCREEN_LEFT, SCREEN_BOTTOM - 150, SCREEN_RIGHT - 128, SCREEN_BOTTOM, GetColor(0, 0, 0), true);
	int defaultSize = GetFontSize();

	SetFontSize(30);

	DrawFormatString(SCREEN_LEFT + 40, SCREEN_BOTTOM - 140, GetColor(255, 0, 0), "チュートリアル：ステージについて");

	SetFontSize(defaultSize);
	mpSM->SetMessage(mMessage[mCounter].mMessage,
		mMessage[mCounter].mPos,
		mMessage[mCounter].mColor,
		mMessage[mCounter].mSize,
		mMessage[mCounter].mVel,
		mMessage[mCounter].mLine,
		mMessage[mCounter].mType);

	int MSize = mMessage.size() - 1;
	if (mpSM->DrawScrollMassage() == true && IsButtonPressed(PAD_INPUT_1) && MSize > mCounter)
	{
		mpSM->Reset();
		mCounter++;
	}

	if (IsButtonPressed(PAD_INPUT_2) && MSize >= mCounter)
		mpSM->DrawMassageAll();
}

/*--------------------------------------------------
終了フラグ
--------------------------------------------------*/
Explanation::THUTRIAL StageExplanation::FinalFlag()
{
	if (mpStage->GameEnd() == Stage::RESULTSCENE::THUTRIAL3)
		return Explanation::THUTRIAL::STAGE;
	return Explanation::THUTRIAL::NONE;
}