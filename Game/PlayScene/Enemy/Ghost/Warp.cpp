/*
　クラス：敵クラスの派生クラス
　　　　　ワープして追いかける敵
  作成者：三浦聖矢
  作成日：１２/２１　　　　
*/
#include "Warp.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

//================================================
//			コンストラクタ
//================================================
Warp::Warp(Player* pPlayer)
	:mMoveTimer{}
	,mAlphaTimer{}
	,mpPlayer{pPlayer}
{
	mType = TYPE::TELEPORT;
}

//================================================
//			デストラクタ
//================================================
Warp::~Warp()
{
}

//================================================
//			初期化
//================================================
void Warp::Initialize()
{
	//初期座標の代入
	mBoadPos = Getpos();

	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::HAND, "Hand.png");

	//画像の設定===============================================
	mSRC_y = 0;
	mSprite.SetTexture(mTextute);
	mSprite.src.x = 32;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.alpha = 1.0f;


	mPos.mX = 32 * mBoadPos.mX;
	mPos.mY = 32 * mBoadPos.mY;

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);
	//==========================================================


	mMoveFlag = false;
	mState = MOVE::NONE;

	SPEED = 2;
}

//================================================
//			移動
//================================================
void Warp::Move()
{
	/*プレイヤーの後ろに瞬間移動して追いかけてくる敵
	　一本道限定
	　プレイヤーが一本道を抜けたら消える
	*/
	if (mMoveTimer % TELEPORT_INTERVAL == 0&&mMoveFlag==false)
		Teleportation();

	mMoveTimer++;

	if (mMoveTimer >= TELEPORT_INTERVAL)
		mMoveTimer = 0;


	switch (mState)
	{
		case Enemy::MOVE::UP:
			if (Vanish2() == false)
				return;

			if (mTimer == 0)
				mBoadPos.mY -= 1;

			if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
				mState = MOVE::NONE;

			mSprite.src.y = mSRC_y + 96;

			mVel.mY = -SPEED;

			MoveMotion();

			mMoveTimer = 0;

			if (mPlayerPos.mY - VANISH_RANGE > mBoadPos.mY)
				mState = MOVE::NONE;
			break;
		case Enemy::MOVE::DOWN:
			if (Vanish2() == false)
				return;

			if (mTimer == 0)
				mBoadPos.mY += 1;

			if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
				mState = MOVE::NONE;

			mSprite.src.y = mSRC_y;

			mVel.mY = SPEED;

			MoveMotion();

			mMoveTimer = 0;

			if (mPlayerPos.mY + VANISH_RANGE < mBoadPos.mY)
				mState = MOVE::NONE;
			break;
		case Enemy::MOVE::LEFT:
			if (Vanish2() == false)
				return;

			if (mTimer == 0)
				mBoadPos.mX -= 1;

			if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
				mState = MOVE::NONE;

			mSprite.src.y = mSRC_y + 32;

			mVel.mX = -SPEED;

			MoveMotion();

			mMoveTimer = 0;

			if (mPlayerPos.mX - VANISH_RANGE > mBoadPos.mX)
				mState = MOVE::NONE;
			break;
		case Enemy::MOVE::RIGHT:
			if (Vanish2() == false)
				return;

			if (mTimer == 0)
				mBoadPos.mX += 1;

			if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
				mState = MOVE::NONE;

			mSprite.src.y = mSRC_y + 64;

			mVel.mX = SPEED;

			MoveMotion();

			mMoveTimer = 0;

			if (mPlayerPos.mX + VANISH_RANGE < mBoadPos.mX)
				mState = MOVE::NONE;
			break;
		case Enemy::MOVE::NONE:
			Vanish();

			mMoveFlag = false;
			break;
		default:
			break;
	}
}

//================================================
//			瞬間移動関係
//====================================================================================================
void Warp::Vanish()
{
	mAlphaTimer--;

	mSprite.alpha = (static_cast<float>(mAlphaTimer) / static_cast<float>(ALFHA_INTERVAL));
	
	if (mAlphaTimer != 0)
		return;
	mBoadPos.mX = -1;
	mBoadPos.mY = -1;

	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;

}

bool Warp::Vanish2()
{
	mAlphaTimer++;

	if (mAlphaTimer >= ALFHA_INTERVAL)
		mAlphaTimer = ALFHA_INTERVAL;

	mSprite.alpha = (static_cast<float>(mAlphaTimer) / static_cast<float>(ALFHA_INTERVAL));

	if (mAlphaTimer < ALFHA_INTERVAL)
		return false;
	
	return true;
}

void Warp::Teleportation()
{
	mSprite.alpha = 1.0f;
	mAlphaTimer = 0;
	switch (mpPlayer->GetDirection())
	{
		case Player::MOVE::UP:
		{
			if (StageCollision(mPlayerPos.mX, mPlayerPos.mY + 1) == true &&
				StageCollision(mPlayerPos.mX, mPlayerPos.mY + 2) == true &&
				StageCollision(mPlayerPos.mX, mPlayerPos.mY + 3) == true &&
				StageCollision(mPlayerPos.mX, mPlayerPos.mY + 4) == true)
			{
				mBoadPos.mX = mPlayerPos.mX;
				mBoadPos.mY = mPlayerPos.mY + 4;

				mMoveFlag = true;

				mState = MOVE::UP;
			}
			break;
		}
		case Player::MOVE::DOWN:
		{
			if (StageCollision(mPlayerPos.mX, mPlayerPos.mY - 1) == true &&
				StageCollision(mPlayerPos.mX, mPlayerPos.mY - 2) == true &&
				StageCollision(mPlayerPos.mX, mPlayerPos.mY - 3) == true &&
				StageCollision(mPlayerPos.mX, mPlayerPos.mY - 4) == true)
			{
				mBoadPos.mX = mPlayerPos.mX;
				mBoadPos.mY = mPlayerPos.mY - 4;

				mMoveFlag = true;

				mState = MOVE::DOWN;
			}
			break;
		}
		case Player::MOVE::LEFT:
		{
			if (StageCollision(mPlayerPos.mX + 1, mPlayerPos.mY) == true &&
				StageCollision(mPlayerPos.mX + 2, mPlayerPos.mY) == true &&
				StageCollision(mPlayerPos.mX + 3, mPlayerPos.mY) == true &&
				StageCollision(mPlayerPos.mX + 4, mPlayerPos.mY) == true)
			{
				mBoadPos.mX = mPlayerPos.mX + 4;
				mBoadPos.mY = mPlayerPos.mY;

				mMoveFlag = true;

				mState = MOVE::LEFT;
			}
			break;
		}
		case Player::MOVE::RIGHT:
		{
			if (StageCollision(mPlayerPos.mX - 1, mPlayerPos.mY) == true &&
				StageCollision(mPlayerPos.mX - 2, mPlayerPos.mY) == true &&
				StageCollision(mPlayerPos.mX - 3, mPlayerPos.mY) == true &&
				StageCollision(mPlayerPos.mX - 4, mPlayerPos.mY) == true)
			{
				mBoadPos.mX = mPlayerPos.mX - 4;
				mBoadPos.mY = mPlayerPos.mY;

				mMoveFlag = true;

				mState = MOVE::RIGHT;
			}
			break;
		}
		default:
			break;
	}
	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;

}
//==================================================================================================