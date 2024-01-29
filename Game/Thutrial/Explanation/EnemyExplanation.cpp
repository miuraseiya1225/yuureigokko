/*
　クラス：敵の説明
  作成者：三浦聖矢
  作成日：１/１　　　　
*/

#include "EnemyExplanation.h"
#include"../../GameData/GameData.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
EnemyExplanation::EnemyExplanation(GameData* pGameData)
{
	mpStage = new Stage(pGameData->GetStageSelect(), Stage::MODE::THUTRIAL2,pGameData);
	pGameData->GameDataReset();
	mpGameData = pGameData;

}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
EnemyExplanation::~EnemyExplanation()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void EnemyExplanation::Initialize()
{
	//メッセージ用CSVファイルの読み込み

	LoadCSV(10,14);

	//メッセージクラスの実体化
	mpSM = new ScrollMassage();

	//ステージクラスの初期化
	mpStage->Initialize();
	mpStage->SetTimerLimit(0);

	mpStage->Update();
}

/*--------------------------------------------------
更新
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
描画
--------------------------------------------------*/
void EnemyExplanation::Draw()
{
	mpStage->Draw();
	DrawBox(SCREEN_LEFT, SCREEN_BOTTOM - 150, SCREEN_RIGHT - 128, SCREEN_BOTTOM, GetColor(0, 0, 0), true);
	int defaultSize = GetFontSize();

	SetFontSize(30);

	DrawFormatString(SCREEN_LEFT + 40, SCREEN_BOTTOM - 140, GetColor(255, 0, 0), "チュートリアル：敵について");

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
終了フラグ
--------------------------------------------------*/
Explanation::THUTRIAL EnemyExplanation::FinalFlag()
{
	if (mpStage->GameEnd() == Stage::RESULTSCENE::THUTRIAL2)
		return Explanation::THUTRIAL::ENEMY;
	return Explanation::THUTRIAL::NONE;
}