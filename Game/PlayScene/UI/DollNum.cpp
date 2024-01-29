/*
　クラス：人形の数
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１/17　　　　
*/
#include "DollNum.h"
#include"../../Resource/Resource.h"

#include"../../GameData/GameData.h"

//=============================================
//			コンストラクタ
//=============================================
DollNum::DollNum(GameData* pGameData):mpGameData{pGameData},mMoldSprite{},mDollNum{}
{
}

//=============================================
//			デストラクタ
//=============================================
DollNum::~DollNum()
{
}

//=============================================
//			初期化
//=============================================
void DollNum::Initialize()
{
	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データの取得
	mTexture = prm->LoadTexture(eTEXTURE::DOLL, "miseityanningyou.png");

	//画像の設定=============================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.scale.x = 1.6f;
	mSprite.scale.y = 1.6f;
	//~=~=======================================

	//型の画像の取得
	mTexture = prm->LoadTexture(eTEXTURE::DOLL_MOLD, "kata.png");

	//型の画像の設定==============================================
	mMoldSprite.SetTexture(mTexture);
	mMoldSprite.src.x = 0;
	mMoldSprite.src.y = 0;
	mMoldSprite.size.x = 128;
	mMoldSprite.size.y = 64;
	mMoldSprite.pos.x = static_cast<float>(SCREEN_RIGHT - 64);
	mMoldSprite.pos.y = static_cast<float>(160);
	//==========================================================
}

//=============================================
//			更新
//=============================================
void DollNum::Update()
{
	//人形の数の取得
	mDollNum = mpGameData->GetDollNum();
}

//=============================================
//			描画
//=============================================
void DollNum::Draw()
{
	mMoldSprite.Draw();

	mPos.mX = SCREEN_RIGHT - 105;
	mPos.mY = 165;
	for (int i = 0; i < mDollNum; i++)
	{
		mSprite.pos.x = static_cast<float>(mPos.mX);
		mSprite.pos.y = static_cast<float>(mPos.mY);
		mSprite.Draw();
		mPos.mX += 43;

	}
}