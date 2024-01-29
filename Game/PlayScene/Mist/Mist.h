/*
　クラス：霧
  作成者：三浦聖矢
  作成日：１/3　　
*/
#pragma once
#include"../../Utility.h"

class Mist
{
private:
	SpriteData mSprite;		//スプライト
	int mTexture;		//画像データ
	float mAlpha;		//透明度
public:
	Mist();		//コンストラクタ
	~Mist();	//デストラクタ

	void Initialize();	//初期化
	void Update();		//更新
	const void Draw();		//描画
};