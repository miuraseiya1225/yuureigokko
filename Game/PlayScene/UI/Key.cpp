/*
　クラス：鍵を持っているか否か
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/8　　　　
*/
#include"Key.h"
#include"../Player/Player.h"

#include"../../Resource/Resource.h"

#include<iostream>
#include"../../GameMain.h"

//=============================================
//			コンストラクタ
//=============================================
KeyCheck::KeyCheck(int keynum): mKeySprite{},mKeyBreakTimer{25},mKeyBreakSprite{}
{
	mKeyNum = keynum;
}

//=============================================
//			デストラクタ
//=============================================
KeyCheck::~KeyCheck()
{

}

//=============================================
//			初期化
//=============================================
void KeyCheck::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データ取得
	mTexture = prm->LoadTexture(eTEXTURE::BOX, "box.png");

	//画像の設定==========================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 64;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.scale.x = 4.0f;
	mSprite.scale.y = 4.0f;

	mSprite.pos.x = SCREEN_RIGHT - 64;
	mSprite.pos.y = 64;
	//===================================================

	//鍵画像の設定	==============================================
	mKeySprite.SetTexture(mTexture);
	mKeySprite.src.x = 96;
	mKeySprite.src.y = 0;
	mKeySprite.size.x = 32;
	mKeySprite.size.y = 32;
	mKeySprite.scale.x = 1.0f;
	mKeySprite.scale.y = 1.0f;
	//=========================================================

	//鍵破壊画像の設定==============================================
	mKeyBreakSprite.SetTexture(mTexture);
	mKeyBreakSprite.src.x = 256;
	mKeyBreakSprite.src.y = 0;
	mKeyBreakSprite.size.x = 32;
	mKeyBreakSprite.size.y = 32;
	mKeyBreakSprite.scale.x = 1.0f;
	mKeyBreakSprite.scale.y = 1.0f;
	mKeyBreakSprite.pos.x = static_cast<float>(mPlayerPos.mX);
	mKeyBreakSprite.pos.y = static_cast<float>(mPlayerPos.mY - 30);
	//==============================================================

	//音源取得
	mAudio = prm->LoadAudio(eAUDIO::GETKEY, "GetKey.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//プレイヤークラスの取得
	mpPlayer = GetpPlayer();

	//プレイヤーの座標取得
	mPlayerPos = mpPlayer->GetposMicro();
}

//=============================================
//			更新
//=============================================
void KeyCheck::Update()
{
	//プレイヤーの座標取得
	mPlayerPos = mpPlayer->GetposMicro();

	if(mTimer<90)
		mTimer++;

	if (mTimer == 0)
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);

	//プレーヤーが扉を開けたらアニメーションを流す
	if (mpPlayer->GetSumKeyFlag() == true)
	{
		mKeyBreakTimer = 0;
		mpPlayer->SetSumKeyFlag();
	}

	if (mKeyBreakTimer < 25)
		mKeyBreakTimer++;
	else
	{
		mKeyBreakSprite.src.x = 64;
		mKeyBreakSprite.src.y = 0;
	}

	mKeyBreakSprite.pos.x = static_cast<float>(mPlayerPos.mX);
	mKeyBreakSprite.pos.y = static_cast<float>(mPlayerPos.mY - 30);
}

void KeyCheck::Draw()
{
	//背景
	DrawBox(SCREEN_RIGHT - 128, 0, SCREEN_RIGHT, 128, GetColor(255, 255, 255), true);

	//鍵
	mSprite.Draw();

	//鍵の個数============================================================
	int defaultSize = GetFontSize();

	SetFontSize(KEY_SIZE);

	DrawFormatString(SCREEN_RIGHT - 100, 100, GetColor(0, 0, 0), "×%2d/%2d", mpPlayer->CheckKey(),mKeyNum);

	SetFontSize(defaultSize);
	//===================================================================

	//鍵を見つけた時のＵＩ========================
	if (mTimer < 90)
	{
		mKeySprite.pos.x = static_cast<float>(mPlayerPos.mX);
		mKeySprite.pos.y = static_cast<float>(mPlayerPos.mY - 30);
		mKeySprite.scale.x = sin(mTimer / 10.0f);
		mKeySprite.Draw();
	}
	//===========================================

	//扉を開けた時のＵＩ==============================
	if (mKeyBreakTimer == 0)
	{
		mKeyBreakSprite.src.x = 64;
		mKeyBreakSprite.src.y = 0;
	}
	if (mKeyBreakTimer == 8)
	{
		mKeyBreakSprite.src.x = 128;
		mKeyBreakSprite.src.y = 0;
	}
	if (mKeyBreakTimer == 16)
	{
		mKeyBreakSprite.src.x = 160;
		mKeyBreakSprite.src.y = 0;
	}
	if (mKeyBreakTimer == 24)
	{
		mKeyBreakSprite.src.x = 192;
		mKeyBreakSprite.src.y = 0;
	}
	if(mKeyBreakTimer<25)
		mKeyBreakSprite.Draw();
	//===========================================
}