#pragma once
/*
　クラス：プレイヤー
  作成者：三浦聖矢
  作成日：9/16　　
*/
#include"../../Utility.h"

#include"../Stage/Stage.h"

//前方宣言
class Mask;
class Door;
class Doll;

class Player
{
public:
	//向き
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};
private:
	//画像操作
	SpriteData mSprite;

	//画像ハンドル
	int mTexture;

	//音源ハンドル
	int mAudio;

	//速度	
	Int2 mVel;
	int mSpeed;

	//ステージデータ
	int mStageBourd[STAGE_SIZEY][STAGE_SIZEX];

	//描画位置
	Int2 mPos;

	//ステージ上の座標
	Int2 mBoadPos;

	//移動用タイマー	
	int mTimer;

	//向き
	MOVE mState;
	MOVE mState2;

	//鍵の数
	int mKey;

	//全体の鍵の数
	int mKeyTotal;

	//制限時間
	int mTimerLimit;

	//ゴール用座標
	Int2 num;

	//画像切り取り位置
	int mSRC;

	//マスククラス
	Mask* mpMask;

	//ドアクラス
	std::vector<Door*> mpDoor;

	//人形クラス
	std::vector<Doll*> mpDoll;

	//UI用フラグ
	bool mSumKeyFlag;

	//ステージ移動フラグ
	bool mStageMoveFlag;
public:
	Player(Mask* pMask);		//コンストラクタ
	~Player();					//デストラクタ

	void Initialize();			//初期化
	void Update();				//更新
	void Draw();				//描画
	void Move();				//移動
	void MoveMotion();			//移動アニメーション

	bool StageMove(MOVE move);	//ステージが移動したら処理する

	bool CheckButton();			//ボタンが押されたか

	//扉を開ける
	void OpenDoor(int x, int y);

	bool PickDoll();	//人形を拾う

	//ステージ情報取得
	void SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX]);	

	//扉クラスのアドレス取得
	void SetDoor(std::vector<Door*> pDoor, int DoorNum);

	//人形クラスのアドレス
	void SetDoll(std::vector<Doll*> pDoll, int DollNum);

	//初期位置取得
	void SetPos(int x, int y);

	//プレイヤーの座標
	const Int2 Getpos();

	//プレイヤーの画面上の座標
	const Int2 GetposMicro();

	//プレイヤーの向き
	const MOVE GetDirection();

	//制限時間
	void SetTimerLimit(int timer) { mTimerLimit = timer; };
	const int GetTimerLimit() { return mTimerLimit; };

	//ステージの当たり判定
	bool StageCollision(int x,int y);

	//鍵の合計取得
	void SetKeyTotal(int keytotal);

	//全体の鍵の数	
	const int GetKeyTotal();

	//鍵の取得
	void SetKey();
	const int CheckKey();

	//UI用
	void SetSumKeyFlag() { mSumKeyFlag = false; };
	const bool GetSumKeyFlag() { return mSumKeyFlag; };
	
	//ゴールしたか
	bool CheckGoal();

	//終了処理
	const void Finalize();
};