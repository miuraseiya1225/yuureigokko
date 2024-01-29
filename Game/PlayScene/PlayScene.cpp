/*
プレイシーン
*/
#include "PlayScene.h"

#include "../GameMain.h"
#include"../GameData/GameData.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
PlayScene::PlayScene(GameData* pGameData):mpStage{},mFlow{FLOW::INITIALIZE},mNext{NEXT::GOAL}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
PlayScene::~PlayScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void PlayScene::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//音源データ取得
	mAudio = prm->LoadAudio(eAUDIO::ROOM, "kimoroop3.wav");

	//ステージクラスの実体化と初期化
	mpStage = new Stage(mpGameData->GetStageSelect(),Stage::MODE::PLAY,mpGameData);
	mpStage->Initialize();

	//BGM
	PlaySoundMem(mAudio, DX_PLAYTYPE_LOOP, true);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE PlayScene::Update()
{
	switch (mFlow)
	{
		case FLOW::INITIALIZE:
		{
			Reset();

			mpGameData->GameDataReset();

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
			//制限時間の取得
			mpStage->SetTimerLimit(mpGameData->SubTimerLimit());

			//更新
			mpStage->Update();

			//ゴールしたらリザルトへ
			if (mpStage->GameEnd() == Stage::RESULTSCENE::GOAL)
			{
				StopSoundMem(mAudio);
				mFlow = FLOW::FADE_OUT;
				mNext = NEXT::GOAL;
			}
			//敵に捕まったら死亡シーンへ
			else if (mpStage->GameEnd() == Stage::RESULTSCENE::DIE)
			{
				StopSoundMem(mAudio);
				mFlow = FLOW::FADE_OUT;
				mNext = NEXT::DIE;

				return GAME_SCENE::DIE;
			}
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

			if(mNext==NEXT::GOAL)
				return GAME_SCENE::RESULT;

			if (mNext == NEXT::DIE)
				return GAME_SCENE::DIE;
			break;
		}
	}

#if defined(_DEBUG)
	if (IsButtonPressed(PAD_INPUT_10) == TRUE)
	{
		StopSoundMem(mAudio);
		return GAME_SCENE::RESULT;
	}
#endif

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void PlayScene::Draw()
{
	mpStage->Draw();
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void PlayScene::Finalize()
{

	mpStage->Finalize();

	delete mpStage;
	mpStage = nullptr;
}

void PlayScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
}
