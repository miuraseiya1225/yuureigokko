#pragma once
#include"../../Utility.h"

/*
　クラス：敵クラスの基底クラス
  作成者：三浦聖矢
  作成日：１0/2　　　　
*/

class Enemy
{
public:
	enum class TYPE:int
	{
		NONE,

		NORMAL,
		CHASE_LV1,
		CHASE_LV2,
		TELEPORT,
		FIRE,
	};
	//敵が向いている方向
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};

protected:

	//敵の移動速度
	int SPEED;

	//乱数用
	int mRand;

	//画像データ
	int mTextute;

	//スプライト
	SpriteData mSprite;

	//切り取り
	int mSRC_y;

	//座標	
	Int2 mPos;

	//ステージ上の座標
	Int2 mBoadPos;

	//速度
	Int2 mVel;

	//ステージデータ
	int mStageBourd[STAGE_SIZEY][STAGE_SIZEX];

	//タイマー
	int mTimer;

	//方向の状態
	MOVE mState;

	MOVE mState2;

	//移動用フラグ
	bool mMoveFlag;

	//プレイヤーの座標
	Int2 mPlayerPos;

	//敵のタイプ
	TYPE mType;
public:
	//コンストラクタ
	Enemy();

	//デストラクタ
	virtual ~Enemy() = default;

	//初期化(引数に初期位置)
	virtual void Initialize() = 0;

	//更新
	void Update();

	//描画
	void Draw();

	//デバック用
	virtual void Draw2() = 0;
	
	//移動
	virtual void Move() = 0;

	//ランダム移動
	void MoveRand();

	//移動モーション
	void MoveMotion();

	//ステージデータの取得
	void SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX]);

	//座標の取得（返り値）
	void SetPos(int x, int y);
	const Int2 Getpos();
	const Int2 GetposMicro();

	//プレイヤーの座標の取得
	void GetPlayerPos();
	
	//敵のタイプの取得
	const TYPE GetTYPE() { return mType; };

	//壁との当たり判定
	bool StageCollision(int x, int y);

	//プレイヤーとの当たり判定
	bool CheckHitPlayer();

	//ステージ移動に応じて敵も動かす
	bool StageMove(MOVE move);
};