/*
　クラス：背景の無限スクロール
  作成者：三浦聖矢
  作成日：１/2　　　　
*/
#include "TitleLoad.h"
#include"../GameMain.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
TitleLoad::TitleLoad():mSprite{},mTexture{},mPos{}
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
TitleLoad::~TitleLoad()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void TitleLoad::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* Resource = ResourceManager::GetInstance();

	//画像データの取得
	mTexture = Resource->LoadTexture(eTEXTURE::TITLE_LOAD, "TitleLoad.png");

	//画像の設定===============================================================
	mSprite[0].SetTexture(mTexture);
	mSprite[0].src.x = 0;
	mSprite[0].src.y = 0;
	mSprite[0].size.x = 320;
	mSprite[0].size.y = 96;
	mSprite[0].scale.x = 5.0f;
	mSprite[0].scale.y = 5.0f;
	mSprite[0].pos.x = SCREEN_CENTER_X + 200;
	mSprite[0].pos.y = SCREEN_CENTER_Y - 100;

	mSprite[1].SetTexture(mTexture);
	mSprite[1].src.x = 0;
	mSprite[1].src.y = 0;
	mSprite[1].size.x = 320;
	mSprite[1].size.y = 96;
	mSprite[1].scale.x = 5.0f;
	mSprite[1].scale.y = 5.0f;
	mSprite[0].pos.x = SCREEN_CENTER_X + 200 + 320;
	mSprite[0].pos.y = SCREEN_CENTER_Y - 100;
	//=======================================================================-
}

/*--------------------------------------------------
更新
--------------------------------------------------*/
void TitleLoad::Update()
{
	
	for (int i = 0; i < 2; i++)
	{
		if (mPos[i].mX <= SCREEN_CENTER_X + 200 - 320)
			mPos[i].mX = SCREEN_CENTER_X + 200 + 320;
		mPos[i].mX -= 2;
		mSprite[i].pos.x = static_cast<float>(mPos[i].mX);
	}
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
const void TitleLoad::Draw()
{
	for(int i=0;i<2;i++)
		mSprite[i].Draw();
}
