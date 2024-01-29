#pragma once
/*
　クラス：ステージ選択シーン
  作成者：三浦聖矢
  作成日：１2/15　　　
*/
#include "../IScene.h"
#include"../Utility.h"
#include"EnemyNum.h"

//前方宣言
class GameData;

class SelectScene : public IScene
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

	//ステージ
	enum class STATE :int
	{
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		STAGE5,
		STAGE_NUM,

		FINALMAP,

	};

	//画面
	enum class DISPLAY :int
	{
		ENEMY_NUM,
		RANK,
		FINALMAP,
	};
private:
	int mAudio;		//音源データ
	int mPushAudio;		//音源データ

	int mTexture;		//画像データ

	SpriteData mSprite;		//スプライト

	GameData* mpGameData;		//ゲームデータ

	EnemyNum* mpEN;				//敵の数クラス

	FLOW mFlow;				//状態
		
	STATE mState;			//ステージ切り替え用

	Color3 mColor[static_cast<int>( STATE::STAGE_NUM)];		//色

	Int2 mPos;				//座標

	DISPLAY mDisplay;		//画面の表示切替用

	bool mFinalStageFlag;	//最終ステージに挑めるか
public:

	// コンストラクタ
	SelectScene(GameData* pGameData);

	// デストラクタ
	~SelectScene();

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