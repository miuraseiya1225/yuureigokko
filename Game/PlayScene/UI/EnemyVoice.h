#pragma once
/*
　クラス：敵の鳴き声
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/8　　　　
*/
#include"UI.h"

//前方宣言
class Enemy;
class Player;

class EnemyVoice :public GameUI
{
private:
	int mVoiceTimer;		//鳴き声用
	std::vector<Int2> mEnemyPos;	//敵の座標
	std::vector<float> mRange;		//距離
	int mRangeLow;					//最小の距離
public:
	//コンストラクタ
	EnemyVoice(Enemy* pEnemy[],int EnemyNum, Player* pPlayer);

	//デストラクタ
	~EnemyVoice()override;

	void Initialize()override;		//初期化
	void Update()override;			//更新
	void Draw()override;			//描画

	//敵の距離を計算する
	bool EnemyRange();
};