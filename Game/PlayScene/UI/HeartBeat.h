#pragma once
/*
　クラス：プレイヤーの心音
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/3　　　　
*/
#include"UI.h"

class HeartBeat :public GameUI
{
private:
	int mBeatTimer;		//心音用

	std::vector<Int2> mEnemyPos;	//敵の座標

	float mRadius;		//半径

	float mBeatInterval;	//心音を鳴らす間隔	

	std::vector<float> mRange;		//距離

	int mRangeLow;		//最小の距離

	float mAlpha;		//透明度
public:
	HeartBeat();		//コンストラクタ
	~HeartBeat();		//デストラクタ

	void Initialize()override;		//初期化

	void Update()override;			//更新	

	void Draw()override;			//描画

	bool EnemyRange();				//敵との距離	
};