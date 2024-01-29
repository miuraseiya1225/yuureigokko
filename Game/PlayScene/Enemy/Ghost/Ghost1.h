#pragma once
#include"../Enemy.h"

/*
　クラス：敵クラスの派生クラス
　　　　　ランダム移動
  作成者：三浦聖矢
  作成日：１0/2　　　　
*/

//前方宣言
class Player;

class Ghost1 :public Enemy
{
private:
	//乱数用
	int mRand;

	Player* mpPlayer;	//プレイヤークラス
public:
	//コンストラクタ
	Ghost1(Player* pPlayer);

	//デストラクタ
	~Ghost1()override;

	//初期化
	void Initialize()override;

	//移動
	void Move()override;
	void Draw2()override {};

};