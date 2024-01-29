#include"Thutrial.h"

#include "../GameMain.h"
#include"Explanation/BoxExplanation.h"
#include"Explanation/EnemyExplanation.h"
#include"Explanation/StageExplanation.h"

#include"../GameData/GameData.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
ThutrialScene::ThutrialScene(GameData* pGameData)
	:mFlow{ FLOW::INITIALIZE }
	,mpGameData{pGameData}
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
ThutrialScene::~ThutrialScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void ThutrialScene::Initialize()
{
	mpGameData->SetStageSelect(GameData::STAGE::THUTRIAL1);

	mpExplanation = new BoxExplanation(mpGameData);
	mpExplanation->Initialize();

}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
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
			//フェードの更新
			int res = FadeOutUpdate(FADE_TIME);

			//フェードが終了したら次の状態へ
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
描画
--------------------------------------------------*/
void ThutrialScene::Draw()
{
	mpExplanation->Draw();
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void ThutrialScene::Finalize()
{
	mpExplanation->Finalize();

	delete mpExplanation;
	mpExplanation = nullptr;
}

/*--------------------------------------------------
次の説明へ
--------------------------------------------------*/
void ThutrialScene::Next()
{
	//説明が終わったらデリートして次の説明のコンストラクタで実体化する

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
リセット
--------------------------------------------------*/
void ThutrialScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
}