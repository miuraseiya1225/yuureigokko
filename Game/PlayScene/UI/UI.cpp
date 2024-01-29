/*
　クラス：ゲームUI
  作成者：三浦聖矢
  作成日：１2/2　　　　
*/
#include"UI.h"

#include"../../Resource/Resource.h"
#include"../Enemy/Enemy.h"
#include"../Player/Player.h"
#include"../Stage/Stage.h"

#include<iostream>

GameUI::GameUI():
	 mpPlayer{}
	,mpEnemy{}
	,mSprite{}
	,mPos{}
	,mTexture{}
	,mEnemyNum{}
	, mPlayerPos{}
	, mTimer{ 91 }
	,mAudio{0}
{
	mpEnemy.resize(Stage::ENEMY_NUM);
}
GameUI::~GameUI()
{
	StopSoundMem(mAudio);
}

//====================================================
//       敵のアドレス　　敵の数
//==================================================
void GameUI::SetpEnemy(Enemy* pEnemy[], int EnemyNum)
{
	mEnemyNum = EnemyNum;
	mpEnemy.resize(mEnemyNum);
	for (int i = 0; i < EnemyNum; i++)
	{
		mpEnemy[i] = pEnemy[i];
	}
}

//====================================================
//       プレイヤークラスアドレス取得
//==================================================
void GameUI::SetpPlayer(Player* pPlayer)
{
	mpPlayer = pPlayer;
}

std::vector<Enemy*> GameUI::GetpEnemy()
{
	return mpEnemy;
}

Player* GameUI::GetpPlayer()
{
	return mpPlayer;
}


//key===========================
void GameUI::KeyUIFlag()
{
	mTimer = 0;
}
void GameUI::Finalize()
{
	//StopSoundMem(mAudio);
}
//===============================-