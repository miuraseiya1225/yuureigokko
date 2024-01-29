#include "Mist.h"
/*
　クラス：霧
  作成者：三浦聖矢
  作成日：１/3　　
*/
#include"../../Resource/Resource.h"
#include"../../GameMain.h"

//================================================
//			コンストラクタ
//================================================
Mist::Mist():
	mSprite{}
	,mTexture{}
	,mAlpha{}
{
}

//================================================
//			デストラクタ
//================================================
Mist::~Mist()
{
}

//================================================
//			初期化
//================================================
void Mist::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データ取得
	mTexture = prm->LoadTexture(eTEXTURE::MIST, "mist.png");

	//画像の設定=============================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 1000;
	mSprite.size.y = 419;
	mSprite.scale.x = 2.0f;
	mSprite.scale.y = 2.0f;

	mSprite.pos.x = static_cast<float> (SCREEN_CENTER_X);
	mSprite.pos.y = static_cast<float> (SCREEN_CENTER_Y);
	//=======================================================
}

//================================================
//			更新
//================================================
void Mist::Update()
{
	//sinを使って移管経過で霧の透明度を変える
	mAlpha += 0.01f;

	mSprite.alpha = sinf(mAlpha) * sinf(mAlpha) * 0.2f;
}

//================================================
//			描画
//================================================
const void Mist::Draw()
{
	//描画
	mSprite.Draw();
}