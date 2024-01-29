#pragma once
/*
　クラス：敵クラスの派生クラス
　　　　　追いかける敵(Level1)
  作成者：三浦聖矢
  作成日：１１/２７　　　　
*/
#include"../Enemy.h"

//前方宣言
class Player;

class ChaseGhost :public Enemy
{
private:
	Player* mpPlayer;	//プレイヤークラス
public:
	//コンストラクタ
	ChaseGhost(Player* pPlayer);

	//デストラクタ
	~ChaseGhost()override;

	void Initialize()override;

	//移動
	void Move()override;
	void Draw2()override {};

	//移動モーション
	void MoveMotion2();
};