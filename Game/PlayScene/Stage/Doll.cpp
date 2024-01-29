/*
　クラス：人形
  作成者：三浦聖矢
  作成日：１/16　　
*/
#include "Doll.h"
#include"../../Resource/Resource.h"
#include"../Player/Player.h"

//================================================
//			コンストラクタ
//================================================
Doll::Doll(int x, int y):mPickFlag{false},mSoundFlag{false},mBoadPos{}
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			デストラクタ
//================================================
Doll::~Doll()
{
	StopSoundMem(mAudio);
}

//================================================
//			初期化
//================================================
void Doll::Initialize()
{
	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データの取得
	mTexture = prm->LoadTexture(eTEXTURE::DOLL, "miseityanningyou.png");

	//音声データの取得
	mAudio = prm->LoadAudio(eAUDIO::GETKEY, "GetKey.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//画像の設定=================================================
	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;

	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	mSprite.rot = sin((2 * DX_PI * GetRand(360) / 360));
	//=============================================================
}

//================================================
//			更新
//================================================
void Doll::Update(Player* pPlayer)
{
	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	//時間切れになったら人形を消す
	if (pPlayer->GetTimerLimit() < 0)
		mPickFlag = true;

	//プレイヤーが人形を拾ったら消す===============
	if (mPickFlag == true)
	{
		mBoadPos.mX = -3;
		mBoadPos.mY = -3;

		if(mSoundFlag==false)
			PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);
		mSoundFlag = true;
	}
	//===============================================

	//三平方の定理を使ってプレイヤーの距離を計算し、その距離に応じて人形の透明度を変化させる==========
	//プレイヤーの位置情報取得
	Int2 PlayerPosMicro = pPlayer->GetposMicro();

	float RangeX = static_cast<float>((mPos.mX)- PlayerPosMicro.mX);
	float RangeY = static_cast<float>((mPos.mY) - PlayerPosMicro.mY);

	if (RangeX <= 0)
		RangeX *= -1;
	if (RangeY <= 0)
		RangeY *= -1;

	float Range = sqrtf((RangeX * RangeX) + (RangeY * RangeY));

	mSprite.alpha = (416.0f - Range) / 416.0f;
	//==============================================================================================
}

//================================================
//			描画
//================================================
const void Doll::Draw()
{
	//人形が消えているなら描画しない
	if (mPickFlag == true)
		return;

	mSprite.Draw();
}

//================================================
//			ステージが移動したら人形も移動する
//================================================
bool Doll::StageMove(MOVE move)
{
	switch (move)
	{
		case Doll::MOVE::UP:
		{
			mPos.mY += 8 *32;

			break;
		}
		case Doll::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Doll::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Doll::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}

	return false;
}
