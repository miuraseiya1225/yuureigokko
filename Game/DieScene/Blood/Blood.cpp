/*
　クラス：血
  作成者：三浦聖矢
  作成日：１2/11　　　　
*/
#include"Blood.h"
#include"../../Resource/Resource.h"

//================================================
//		コンストラクタ
//================================================
Blood::Blood():
	mSprite{}
	,mTexture{}
	,mTimer{}
{

}

//================================================
//		デストラクタ
//================================================
Blood::~Blood()
{

}

//================================================
//		初期化
//================================================
void Blood::Initialize()
{
	//リソースマネージャー
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データの読み込み
	mTexture = prm->LoadTexture(eTEXTURE::BLOOD, "Blood.png");

	//音声データの読み込み
	mAudio = prm->LoadAudio(eAUDIO::CREAM, "himei_kyaaaaaaaa.wav");
	ChangeVolumeSoundMem(255, mAudio);

	//音声データの読み込み
	mAudio2 = prm->LoadAudio(eAUDIO::BLOOD, "blood_flow.mp3");
	ChangeVolumeSoundMem(255, mAudio2);

	//音声データの読み込み
	mAudio3 = prm->LoadAudio(eAUDIO::ATTACK, "hit_axe3.mp3");
	ChangeVolumeSoundMem(255, mAudio3);

	//画像データの設定========================================-
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 500;
	mSprite.size.y = 693;
	mSprite.scale.x = 1.5f;
	mSprite.scale.y = 1.5f;
	//====================================================
}

//================================================
//		更新
//================================================
void Blood::Update()
{
	//時間経過で音声を流す======================================
	if (mTimer == 20)
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, true);

	if(mTimer == 80)
		PlaySoundMem(mAudio3, DX_PLAYTYPE_BACK, true);

	if (mTimer == 90)
		PlaySoundMem(mAudio2, DX_PLAYTYPE_BACK, true);
	//=========================================================

	mTimer++;
}

//================================================
//		描画
//================================================
void Blood::Draw()
{
	//時間経過で画像を描画する===============================
	if (mTimer > 90)
	{
		mSprite.pos.x = 400;
		mSprite.pos.y = 300;
		mSprite.Draw();
		mSprite.pos.x = 200;
		mSprite.pos.y = 300;
		mSprite.Draw();
	}
	if (mTimer > 91)
	{
		mSprite.pos.x = 1100;
		mSprite.pos.y = 600;
		mSprite.Draw();
	}
	if (mTimer > 92)
	{
		mSprite.pos.x = 1100;
		mSprite.pos.y = 100;
		mSprite.Draw();
	}
	if (mTimer > 93)
	{
		mSprite.pos.x = 400;
		mSprite.pos.y = 650;
		mSprite.Draw();
		mSprite.pos.x = 200;
		mSprite.pos.y = 550;
		mSprite.Draw();
	}
	if (mTimer > 94)
	{
		mSprite.pos.x = 700;
		mSprite.pos.y = 300;
		mSprite.Draw();
	}
	//===============================================
}

const bool Blood::End()
{
	//一定時間経過で終了
	if (mTimer > 150)
		return true;
	return false;
}