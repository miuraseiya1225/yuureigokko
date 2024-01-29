#pragma once
/*
　クラス：ゲームUI:基底クラス
  作成者：三浦聖矢
  作成日：１2/2　　　　
*/
#include"../../Utility.h"
#include<vector>
#include<iostream>

//前方宣言
class Player;
class Enemy;
class GameUI

{
protected:
	int mAudio;		//音源データ

	Player* mpPlayer;		//プレーヤークラス

	std::vector<Enemy*> mpEnemy;		//敵クラス

	SpriteData mSprite;		//スプライト

	Int2 mPos;		//座標	

	int mTexture;		//画像データ

	int mEnemyNum;		//敵の数

	Int2 mPlayerPos;	//プレーヤーの座標

	int mTimer;		//タイマー
public:
	GameUI();		//コンストラクタ
	virtual~GameUI()=0;		//デストラクタ

	virtual void Initialize() = 0;		//初期化

	virtual void Update()=0;		//更新
	virtual void Draw()=0;		//描画

	void SetpEnemy(Enemy* pEnemy[],int EnemyNum);		//敵クラスのアドレス取得
	void SetpPlayer(Player* pPlayer);			//プレイヤークラスのアドレス取得

	Player* GetpPlayer();	
	std::vector<Enemy*> GetpEnemy();

	//KEY================================
	void KeyUIFlag();
	//============================

	void Finalize();
};