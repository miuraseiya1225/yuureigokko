#pragma once
/*
　クラス：敵クラスの派生クラス
　　　　　近くまで行かないと視認できない敵	
  作成者：三浦聖矢
  作成日：１１/２７　　　　
*/
#include"../Enemy.h"

//前方宣言
class Player;

class Fire :public Enemy
{
private:
	Player* mpPlayer;		//プレイヤークラス
public:
	Fire(Player* pPlayer);	//コンストラクタ
	~Fire()override;		//デストラクタ

	//初期化
	void Initialize()override;

	//移動
	void Move()override;
	void Draw2()override {};
};