/*
　クラス：敵クラスの派生クラス
　　　　　追いかける敵(Level1)
  作成者：三浦聖矢
  作成日：１１/２７　　　　
*/
#include"ChaseGhost.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

//================================================
//		コンストラクタ
//================================================
ChaseGhost::ChaseGhost(Player* pPlayer):mpPlayer{pPlayer}
{
	mType = TYPE::CHASE_LV1;
}

//================================================
//		デストラクタ
//================================================
ChaseGhost::~ChaseGhost()
{

}

//================================================
//		初期化
//================================================
void ChaseGhost::Initialize()
{
	//初期座標の代入
	mBoadPos = Getpos();

	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::CHASEV1, "Chase1.png");

	//画像データの設定=======================================
	mSRC_y = 0;
	mSprite.SetTexture(mTextute);
	mSprite.src.x = 48; 
	mSprite.src.y = 0;
	mSprite.size.x = 48;
	mSprite.size.y = 64;
	mSprite.scale.x = 0.5f;
	mSprite.scale.y = 0.5f;

	mPos.mX = 32 * mBoadPos.mX;
	mPos.mY = 32 * mBoadPos.mY;

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	//====================================================

	//初期向き
	mState = MOVE::RIGHT;
}

//================================================
//		移動
//================================================
void ChaseGhost::Move()
{
	/*  最短距離ではないがプレイヤーを追いかける
	 
		事前情報：マップ上に行き止まりがない程で追いかけるプログラムを組んでいる

		理屈
		まず進んでいる方向に分かれ道が２つ以上あったらマップ上のプレイヤーとの距離をみてその方向に進む
		縦方向と横方向で見ている
	*/
	
	switch (mState)
	{
		case MOVE::NONE:
		{
			break;
		}
		/// ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
		case MOVE::UP:
		{
			//移動フラグチェック
			if (mMoveFlag == true)
			{
				if (mMoveFlag == true)
				{
					if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
					{
						if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
						{
							if (mPlayerPos.mX > mBoadPos.mX) mState = MOVE::RIGHT;
							else if (mPlayerPos.mX < mBoadPos.mX) mState = MOVE::LEFT;
							else if (mPlayerPos.mX == mBoadPos.mX)
							{
								mRand = GetRand(1);

								if (mRand == 0)
									mState = MOVE::RIGHT;
								else
									mState = MOVE::LEFT;
							}
						}

						else if (mPlayerPos.mX > mBoadPos.mX) mState = MOVE::RIGHT;
						else if (mPlayerPos.mX < mBoadPos.mX) mState = MOVE::LEFT;

						mMoveFlag = false;
						return;
					}
					else if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true)
					{
						if (mPlayerPos.mX < mBoadPos.mX) mState = MOVE::LEFT;

						if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false) mState = MOVE::LEFT;

						mMoveFlag = false;

						return;
					}
					else if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
					{
						if (mPlayerPos.mX > mBoadPos.mX) mState = MOVE::RIGHT;

						if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false) mState = MOVE::RIGHT;

						mMoveFlag = false;

						return;
					}
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mY -= 1;
				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y + 192;

			mVel.mY = -SPEED;

			MoveMotion2();

			break;
		}
		//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
		case MOVE::DOWN:
		{
			if (mMoveFlag == true)
			{
				if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
				{
					if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
					{
						if (mPlayerPos.mX > mBoadPos.mX) mState = MOVE::RIGHT;
						else if (mPlayerPos.mX < mBoadPos.mX) mState = MOVE::LEFT;
						else if (mPlayerPos.mX == mBoadPos.mX)
						{
							mRand = GetRand(1);

							if (mRand == 0)
								mState = MOVE::RIGHT;
							else
								mState = MOVE::LEFT;
						}
					}

					else if (mPlayerPos.mX > mBoadPos.mX) mState = MOVE::RIGHT;
					else if (mPlayerPos.mX < mBoadPos.mX) mState = MOVE::LEFT;

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true)
				{
					if (mPlayerPos.mX < mBoadPos.mX) mState = MOVE::LEFT;

					if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false) mState = MOVE::LEFT;

					mMoveFlag = false;

					return;
				}
				else if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
				{
					if (mPlayerPos.mX > mBoadPos.mX) mState = MOVE::RIGHT;

					if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false) mState = MOVE::RIGHT;

					mMoveFlag = false;

					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mY += 1;

				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y;
			mVel.mY = SPEED;

			MoveMotion2();

			break;
		}
		//←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←←
		case MOVE::LEFT:
		{
			if (mMoveFlag == true)
			{
				if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
					{
						if (mPlayerPos.mY > mBoadPos.mY) mState = MOVE::DOWN;
						else if (mPlayerPos.mY < mBoadPos.mY) mState = MOVE::UP;
						else if (mPlayerPos.mY == mBoadPos.mY)
						{
							mRand = GetRand(1);

							if (mRand == 0)
								mState = MOVE::DOWN;
							else
								mState = MOVE::UP;
						}
					}

					else if (mPlayerPos.mY > mBoadPos.mY) mState = MOVE::DOWN;
					else if (mPlayerPos.mY < mBoadPos.mY) mState = MOVE::UP;

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true)
				{
					if (mPlayerPos.mY < mBoadPos.mY) mState = MOVE::UP;

					if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false) mState = MOVE::UP;

					mMoveFlag = false;

					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					if (mPlayerPos.mY > mBoadPos.mY) mState = MOVE::DOWN;

					if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false) mState = MOVE::DOWN;

					mMoveFlag = false;

					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mX -= 1;

				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y + 64;
			mVel.mX = -SPEED;

			MoveMotion2();

			break;
		}
		//→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		case MOVE::RIGHT:
		{
			if (mMoveFlag == true)
			{
				if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
					{
						     if (mPlayerPos.mY > mBoadPos.mY) mState = MOVE::DOWN;
						else if (mPlayerPos.mY < mBoadPos.mY) mState = MOVE::UP;
						else if (mPlayerPos.mY == mBoadPos.mY)
						{
							 mRand = GetRand(1);

							 if(mRand==0)
								 mState = MOVE::DOWN;
							 else
								 mState = MOVE::UP;
						}
					}

					else if (mPlayerPos.mY > mBoadPos.mY) mState = MOVE::DOWN;
					else if (mPlayerPos.mY < mBoadPos.mY) mState = MOVE::UP;
					
					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true)
				{
					if (mPlayerPos.mY < mBoadPos.mY) mState = MOVE::UP;

					if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false) mState = MOVE::UP;

					mMoveFlag = false;

					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					if (mPlayerPos.mY > mBoadPos.mY) mState = MOVE::DOWN;

					if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false) mState = MOVE::DOWN;

					mMoveFlag = false;

					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mX += 1;

				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y + 128;

			mVel.mX = SPEED;

			MoveMotion2();
			break;
		}
	}

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

	mSprite.alpha = (448.0f - Range) / 448.0f;
	//===========================================================================================
}

//================================================
//		移動モーション
//================================================
void ChaseGhost::MoveMotion2()
{
	//
	mTimer++;
	if (mTimer == 8 / SPEED)
	{
		mSprite.src.x -= 48;
	}
	if (mTimer == 16 / SPEED || mTimer == 24 / SPEED)
	{
		mSprite.src.x += 48;
	}

	if (mTimer >= 32 / SPEED)
	{
		mSprite.src.x -= 48;

		mTimer = 0;
	}
}