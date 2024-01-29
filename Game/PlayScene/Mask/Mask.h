#pragma once
/*
　クラス：マスククラス
  作成者：三浦聖矢
  作成日：１2/30　　　　
*/
#include"../../Utility.h"

class Mask
{
public:
	//マスクの解像度（小さくすると重くなる可能性がある）
	static const int BLACK_SIZE = 12;

private:
	int mTexture;	//画像データ

	//スプライト===============================================
	std::vector<std::vector<SpriteData>> mAlphaSprite1;
	std::vector<std::vector<SpriteData>> mAlphaSprite2;
	std::vector<std::vector<SpriteData>> mAlphaSprite3;
	std::vector<std::vector<SpriteData>> mAlphaSprite4;
	//======================================================

	//透明度
	float mAlpha;

	//座標
	Int2 mPos;
	Int2 mPos2;

	//マスクの大きさ
	float mAlpha_Frequency;
public:
	Mask();		//コンストラクタ
	~Mask();	//デストラクタ

	void Initialize();	//初期化

	void Draw();		//描画

	void SetAlpha(Int2 BasePos, float Alpha_Frequency);		//マスクの設定

	void ResetMask();	//マスクの初期化

	void Finalize();	//終了処理
};