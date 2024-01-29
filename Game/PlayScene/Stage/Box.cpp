/*
　クラス：プレイヤー
  作成者：三浦聖矢
  作成日：9/16　　
*/

#include"Box.h"

#include"../../Resource/Resource.h"
#include"../Player/Player.h"

//================================================
//			コンストラクタ
//================================================
Box::Box(Player* pPlayer):
	mBoadPos{}
,mPos{}
,mSprite{}
,mPlayerPos{}
,mKeyNum{true}
,mpPlayer{pPlayer}
{

}

//================================================
//				デストラクタ
//================================================
Box::~Box()
{
	StopSoundMem(mAudio);
}

//================================================
//			初期化
//================================================
void Box::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データ取得
	mTexture = prm->LoadTexture(eTEXTURE::BOX, "box.png");

	//音声データ取得
	mAudio = prm->LoadAudio(eAUDIO::OPENBOX, "OpenBox.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//画像の設定==========================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;

	mBoadPos = GetPos();

	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;
	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);
	//===============================================
}

//================================================
//			更新
//================================================
void Box::Update()
{
	//プレイヤーの座標取得
	GetPlayerPos();

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	//三平方の定理を使ってプレイヤーの距離を計算し、その距離に応じて箱の透明度を変化させる==========
	//プレイヤーの位置情報取得
	Int2 PlayerPosMicro = mpPlayer->GetposMicro();

	float RangeX = static_cast<float>(mPos.mX - PlayerPosMicro.mX);
	float RangeY = static_cast<float>(mPos.mY - PlayerPosMicro.mY);

	if (RangeX <= 0)
		RangeX *= -1;
	if (RangeY <= 0)
		RangeY *= -1;

	float Range = sqrtf((RangeX * RangeX) + (RangeY * RangeY));

	mSprite.alpha = (320.0f - Range) / 320.0f;
	//============================================================================================-
}

//================================================
//			描画
//================================================
const void Box::Draw()
{
	//描画
	mSprite.Draw();
}

//================================================
//			座標の取得
//================================================
void Box::SetPos(int x, int y)
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			ステージデータの取得
//================================================
void Box::SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX])
{
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			mStageBourd[y][x] = stage[y][x];
		}
	}
}

//================================================
//			プレイヤーの座標取得
//================================================
void Box::GetPlayerPos()
{
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			if (mStageBourd[y][x] == 4)
			{
				mPlayerPos.mX = x;
				mPlayerPos.mY = y;
			}
		}
	}
}

//================================================
//			箱を開ける
//================================================
void Box::OpenBox()
{
	if (mBoadPos.mX == mPlayerPos.mX &&
		mBoadPos.mY == mPlayerPos.mY)
	{
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);
		mSprite.src.x = 32;
	}
}

//================================================
//			鍵を無くす
//================================================
void Box::DeleteKey()
{
	mKeyNum = false;
}

//================================================
//			鍵があるかどうか
//================================================
const bool Box::ChackKey()
{
	if (mBoadPos.mX != mPlayerPos.mX ||
		mBoadPos.mY != mPlayerPos.mY)
	{
		return false;
	}
	if (mKeyNum == true)
		return true;
	return false;
}

//================================================
//			ステージが移動したら箱も動かす
//================================================
bool Box::StageMove(MOVE move)
{
	switch (move)
	{
		case Box::MOVE::UP:
		{
			mPos.mY += 8 * 32;
			break;
		}
		case Box::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Box::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Box::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}


	return false;
}
