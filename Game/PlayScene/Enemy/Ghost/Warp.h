#pragma once
/*
　クラス：敵クラスの派生クラス
　　　　　ワープして追いかける敵
  作成者：三浦聖矢
  作成日：１２/２１　　　　
*/
#include"../Enemy.h"

//前方宣言
class Player;

//敵クラスの継承子クラス
class Warp :public Enemy
{
public:
	//瞬間移動する時間の感覚
	static const int TELEPORT_INTERVAL = 256;

	//プレイヤーを追い越した時の移動範囲
	static const int VANISH_RANGE = 1;

	//徐々に消える時間
	static const int ALFHA_INTERVAL = 120;
private:
	int mMoveTimer;		//移動用タイマー
	int mAlphaTimer;	//透明度用タイマー

	Player* mpPlayer;	//プレイヤークラス	
public:
	//コンストラクタ
	Warp(Player* pPlayer);

	//デストラクタ
	~Warp()override;

	//初期化
	void Initialize()override;

	//移動
	void Move()override;

	//瞬間移動用============
	void Vanish();

	bool Vanish2();

	void Teleportation();
	//======================

	void Draw2()override {};

};