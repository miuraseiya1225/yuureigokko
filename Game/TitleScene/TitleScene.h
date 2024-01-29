/*
タイトルシーン
*/
#pragma once

#include "../IScene.h"
#include"../PlayScene/Mask/Mask.h"
#include"TitleLoad.h"
#include"../PlayScene/Mist/Mist.h"
#include"../Utility.h"

class TitleScene : public IScene
{
public:
	//シーン
	enum class STATE :int
	{
		START,
		OPTION,
		EXPLANATION,
		END,
	};
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
	int mAudio;		//音源データ
	int mPushAudio;		//音源データ

	FLOW mFlow;		//状態

	int mTexture;	//画像データ

	SpriteData mSprite[3];	//スプライト

	float mAlpha;		//透明度

	STATE mState;		//シーン

	Int2 mPos[2];		//座標
		
	Color3 mColor3[3];	//色

	int mTimer;			//タイマー
	
	Mask* mpMask;		//マスククラス

	TitleLoad* mpTL;	//背景ループクラス

	Mist* mpMist;		//霧クラス
public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	~TitleScene();

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

	//キャラのアニメーション
	void CharaMotion();
};