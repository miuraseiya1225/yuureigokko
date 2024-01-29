#pragma once
/*
　クラス：血
  作成者：三浦聖矢
  作成日：１2/11　　　　
*/
#include"../../Utility.h"

class Blood
{
private:
	SpriteData mSprite;

	int mTexture;	//画像データ
	int mAudio;		//音声データ１
	int mAudio2;	//音声データ２
	int mAudio3;	//音声データ３

	int mTimer;
public:
	Blood();		//コンストラクタ
	~Blood();		//デストラクタ

	void Initialize();		//初期化

	void Update();			//更新

	void Draw();			//描画

	const bool End();				//終了フラグ
};