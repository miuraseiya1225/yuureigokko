#pragma once
/*
　クラス：鍵を持っているか否か
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/8　　　　
*/
#include"UI.h"

class KeyCheck :public GameUI
{
public:
	//鍵の大きさ
	static const int KEY_SIZE = 25;
private:
	SpriteData mKeySprite;			//鍵用スプライト
	SpriteData mKeyBreakSprite;		//鍵破壊用スプライト
	int mKeyNum;			//鍵の数
	int mKeyBreakTimer;		//鍵の破壊用タイマー
public:
	KeyCheck(int keynum);		//コンストラクタ

	~KeyCheck()override;		//デストラクタ

	void Initialize()override;		//初期化

	void Update()override;			//更新

	void Draw()override;		//描画
};