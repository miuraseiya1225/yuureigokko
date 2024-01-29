#pragma once
/*
　クラス：背景の無限スクロール
  作成者：三浦聖矢
  作成日：１/2　　　　
*/
#include"../Utility.h"

class TitleLoad
{
private:
	SpriteData mSprite[2];	//スプライト
	int mTexture;			//画像データ
	Int2 mPos[2];			//座標
public:
	TitleLoad();			//コンストラクタ
	~TitleLoad();			//デストラクタ

	void Initialize();		//初期化
	void Update();			//更新
	const void Draw();			//描画
};