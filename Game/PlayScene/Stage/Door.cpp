/*
　クラス：扉
  作成者：三浦聖矢
  作成日：１/15　　
*/
#include "Door.h"
#include"../../Resource/Resource.h"

//================================================
//			コンストラクタ
//================================================
Door::Door(int x, int y):
	mTexture{}
	,mSprite{}
	,mPos{}
	,mOpenFlag{false}
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;

}

//================================================
//			デストラクタ
//================================================
Door::~Door()
{
	StopSoundMem(mAudio);
}

//================================================
//			初期化
//================================================
void Door::Initialize()
{
	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データの取得
	mTexture = prm->LoadTexture(eTEXTURE::MAP_TILE, "tile.png");

	//音声データの取得
	mAudio = prm->LoadAudio(eAUDIO::OPENDOOR, "OpenDoor.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//画像の設定================================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 64;
	mSprite.src.y = 64;
	mSprite.size.x = 32;
	mSprite.size.y = 32;

	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;

	mSprite.pos.x =  static_cast<float> (mPos.mX);
	mSprite.pos.y =  static_cast<float> (mPos.mY);
	//==========================================================
}

//================================================
//				描画
//================================================
void Door::Draw()
{
	mSprite.pos.x = static_cast<float> (mPos.mX);
	mSprite.pos.y = static_cast<float> (mPos.mY);

	mSprite.Draw();
}

//================================================
//			ドアを開ける
//================================================
void Door::OpenDoor()
{
	PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);

	mOpenFlag = true;

	mSprite.src.x = 128;
	mSprite.src.y = 128;
}

//================================================
//			プレイヤーの座標チェック
//================================================
bool Door::CheckPlayer(int x,int y)
{
	if (x== mBoadPos.mX && y== mBoadPos.mY&&mOpenFlag == false)
		return false;
	return true;
}

//================================================
//			ステージが動いたら扉も動かす
//================================================
bool Door::StageMove(MOVE move)
{
	switch (move)
	{
		case Door::MOVE::UP:
		{
			mPos.mY += 8 * 32;

			break;
		}
		case Door::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Door::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Door::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}

	return false;
}
