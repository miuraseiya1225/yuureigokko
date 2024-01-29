/*
死亡シーン
*/
#pragma once

#include "../IScene.h"
#include"Blood/Blood.h"

class DieScene : public IScene
{
public:
	//状態============================
	enum class FLOW :int
	{
		FADE_IN,
		FADE_OUT,
		INITIALIZE,
		MAIN,
		FINALIZE,
	};

	//シーンの選択====================
	enum class MODE_SELECT :int
	{
		PLAY,
		TITLE,
		MAX,
	};
private:
	int mPushAudio;		//音源データ

	Blood* mpBlood;		//血クラスのメンバポインタ

	MODE_SELECT mModeSelect;	//シーンの選択

	Color3 mColor3[2];			//色構造体

	FLOW mFlow;		//状態

	SpriteData mSprite;		//スプライト

	int mTexture;	//画像データ
public:

	// コンストラクタ
	DieScene();

	// デストラクタ
	~DieScene();

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