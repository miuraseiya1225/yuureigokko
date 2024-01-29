/*
リザルトシーン
*/
#include"ResultScene.h"

#include "../GameMain.h"
#include"../Resource/Resource.h"
#include"../GameData/GameData.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
ResultScene::ResultScene(GameData* pGameData)
	:mFlow{FLOW::INITIALIZE}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
ResultScene::~ResultScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void ResultScene::Initialize()
{
	//リソースマネージャーのインスタンスを取得する
	ResourceManager* Resource = ResourceManager::GetInstance();

	//画像をリソースマネージャーに登録して画像ハンドルを取得する
	mTexture = Resource->LoadTexture(eTEXTURE::RESULT_LOGO, "clear.png");

	mSprite[0].SetTexture(mTexture);
	mSprite[0].src.x = 0;
	mSprite[0].src.y = 0;
	mSprite[0].size.x = 819;
	mSprite[0].size.y = 136;
	mSprite[0].scale.x = 1.5f;
	mSprite[0].scale.y = 1.5f;
	mSprite[0].pos.x = SCREEN_CENTER_X;
	mSprite[0].pos.y = SCREEN_CENTER_Y - 200;

	//画像をリソースマネージャーに登録して画像ハンドルを取得する
	mTexture = Resource->LoadTexture(eTEXTURE::RESULT_BACK, "ResultBack.png");
	mSprite[1].SetTexture(mTexture);
	mSprite[1].src.x = 0;
	mSprite[1].src.y = 0;
	mSprite[1].size.x = SCREEN_RIGHT;
	mSprite[1].size.y = SCREEN_BOTTOM;
	mSprite[1].pos.x = SCREEN_CENTER_X;
	mSprite[1].pos.y = SCREEN_CENTER_Y;

	mpScore = new Score(mpGameData);
	mpScore->Initialize();
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE ResultScene::Update()
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
			int res = FadeInUpdate(FADE_TIME);

			if (res == false)
				mFlow = FLOW::MAIN;
			break;
		}
		case FLOW::MAIN:
		{
			if (IsButtonPressed(PAD_INPUT_1) && mpScore->NextFlag() == true)
				mFlow = FLOW::FADE_OUT;

			mpGameData->OutputData();

			mpScore->Update();
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
void ResultScene::Draw()
{
	mSprite[1].Draw();

	mSprite[0].Draw();

	mpScore->Draw();
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void ResultScene::Finalize()
{
	delete mpScore;
	mpScore = nullptr;
}

void ResultScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
}
