/*
　クラス：箱と鍵の説明
  作成者：三浦聖矢
  作成日：１/１　　　　
*/
#include "BoxExplanation.h"
#include"../../GameData/GameData.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
BoxExplanation::BoxExplanation(GameData* pGameData)
{
	mpStage = new Stage(pGameData->GetStageSelect(),Stage::MODE::THUTRIAL,pGameData);
	pGameData->GameDataReset();
	mpGameData = pGameData;
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
BoxExplanation::~BoxExplanation()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void BoxExplanation::Initialize()
{
	//メッセージ用CSVファイルの読み込み
	LoadCSV(0,9);

	//メッセージクラスの実体化
	mpSM = new ScrollMassage();

	//ステージクラスの初期化
	mpStage->Initialize();
	mpStage->Update();
}

/*--------------------------------------------------
更新
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
描画
--------------------------------------------------*/
void BoxExplanation::Draw()
{
	mpStage->Draw();

	DrawBox(SCREEN_LEFT, SCREEN_BOTTOM - 150, SCREEN_RIGHT - 128, SCREEN_BOTTOM, GetColor(0, 0, 0), true);
	int defaultSize = GetFontSize();

	SetFontSize(30);

	DrawFormatString(SCREEN_LEFT + 40, SCREEN_BOTTOM - 140, GetColor(255, 0, 0), "チュートリアル：クリア条件について");

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
終了フラグ
--------------------------------------------------*/
Explanation::THUTRIAL BoxExplanation::FinalFlag()
{
	if(mpStage->GameEnd()==Stage::RESULTSCENE::THUTRIAL)
		return Explanation::THUTRIAL::BOX;
	return Explanation::THUTRIAL::NONE;
}
