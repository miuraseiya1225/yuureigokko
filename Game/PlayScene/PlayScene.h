/*
プレイシーン
*/
#pragma once

#include "../IScene.h"

#include"Stage/Stage.h"

//前方宣言
class GameData;

class PlayScene : public IScene
{
public:
	//状態
	enum class FLOW :int
	{
		FADE_IN,
		FADE_OUT,
		INITIALIZE,
		MAIN,
		FINALIZE,
	};

	//次のシーン
	enum class NEXT :int
	{
		TIMEOVER,
		DIE,
		GOAL,
	};
private:
	FLOW mFlow;		//状態
	NEXT mNext;		//次のシーン
	Stage* mpStage;		//ステージクラス

	GameData* mpGameData;		//ゲームデータ

	int mAudio;		//音源データ
public:

	// コンストラクタ
	PlayScene(GameData* pGameData);

	// デストラクタ
	~PlayScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

	//リセット
	void Reset();
};