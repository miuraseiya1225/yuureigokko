/*
リザルトシーン
*/
#pragma once

#include "../IScene.h"
#include"Score.h"

//前方宣言
class GameData;

class ResultScene : public IScene
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

private:
	int mTexture;		//画像データ

	SpriteData mSprite[2];		//スプライト

	FLOW mFlow;		//状態

	GameData* mpGameData;		//ゲームデータ

	Score* mpScore;		//スコアクラス
public:

	// コンストラクタ
	ResultScene(GameData* pGameData);

	// デストラクタ
	~ResultScene();

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