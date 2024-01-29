#pragma once
/*
　クラス：敵の数
  作成者：三浦聖矢
  作成日：１/13　　　
*/
#include"../Utility.h"

class EnemyNum
{
public:
	//敵のタイプごとの数の構造体
	struct EnemyTypeNum
	{
		int mNormalNum = 0;
		int mNormalLightNum = 0;
		int mChasel1Num = 0;
		int mChasel2Num = 0;
		int mHandNum = 0;
		int mKey = 0;
	};
private:
	int mTexture;		//画像データ

	std::vector<std::vector<int>> mStage;	//ステージデータ
	SpriteData mSprite[6];		//敵の画像用

	EnemyTypeNum mEnemyTypeNum[10];		//敵の数
public:
	EnemyNum();						//コンストラクタ
	~EnemyNum();					//デストラクタ
		
	void Initialize();				//初期化
	void Draw(int low,int high);	//描画

	void FinalStageDraw();			//最終ステージ用の描画	

	bool LoadCSV(int src);			//CSVファイルの読み込み

	EnemyTypeNum GetEnemyNum();		//敵の数取得
};