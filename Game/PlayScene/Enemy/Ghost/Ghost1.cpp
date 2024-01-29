/*
　クラス：敵クラスの派生クラス
　　　　　ランダム移動
  作成者：三浦聖矢
  作成日：１0/2　　　　
*/
#include"Ghost1.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

//================================================
//			コンストラクタ
//================================================
Ghost1::Ghost1(Player* pPlayer):
	mRand{}
	,mpPlayer{pPlayer}
{
	mType = TYPE::NORMAL;
}

//================================================
//			デストラクタ
//================================================
Ghost1::~Ghost1()
{

}

//================================================
//			初期化
//================================================
void Ghost1::Initialize()
{
	//初期座標の代入
	mBoadPos = Getpos();

	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::NORMAL, "Makkuro.png");

	//画像の設定==========================================
	mSRC_y = 0;

	mSprite.SetTexture(mTextute);
	mSprite.src.x = 32;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;

	mPos.mX = 32 * mBoadPos.mX;
	mPos.mY = 32 * mBoadPos.mY;

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);
	//======================================================

	//向き
	mState = MOVE::RIGHT;
}

//================================================
//			移動
//================================================
void Ghost1::Move()
{
	//ランダム移動
	MoveRand();

	//三平方の定理を使ってプレイヤーの距離を計算し、その距離に応じて敵の透明度を変化させる==========
	//プレイヤーの位置情報取得
	Int2 PlayerPosMicro = mpPlayer->GetposMicro();

	float RangeX = static_cast<float>(mPos.mX - PlayerPosMicro.mX);
	float RangeY = static_cast<float>(mPos.mY - PlayerPosMicro.mY);

	if (RangeX <= 0)
		RangeX *= -1;
	if (RangeY <= 0)
		RangeY *= -1;

	float Range = sqrtf((RangeX * RangeX) + (RangeY * RangeY));

	mSprite.alpha = (640.0f - Range) / 640.0f;
	//======================================================================================
}
