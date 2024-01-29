/*
　クラス：プレイヤー
  作成者：三浦聖矢
  作成日：9/16　　
*/
#include"Player.h"
#include"../../Resource/Resource.h"
#include"../Mask/Mask.h"
#include"../Stage/Door.h"
#include"../Stage/Doll.h"

//================================================
//			コンストラクタ
//================================================
Player::Player(Mask* pMask):
mSprite{}
,mPos{}
,mBoadPos{}
,mTexture{}
,mVel{}
,mStageBourd{}
,mTimer{}
,mState{}
,mKey{0}
,mKeyTotal{}
,mAudio{}
,mState2{MOVE::NONE}
,mpMask{pMask}
,mTimerLimit{}
,mpDoor{}
,mSumKeyFlag{false}
,mpDoll{}
,mStageMoveFlag{false}
{

}

//================================================
//				デストラクタ
//================================================
Player::~Player()
{
	Finalize();
}

//================================================
//			初期化
//================================================
void Player::Initialize()
{
	//速度の更新	
	mVel.mX = 0;
	mVel.mY = 0;

	//初期座標取得
	mBoadPos = Getpos();

	//全体の鍵の数取得
	mKeyTotal = GetKeyTotal();

	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//テクスチャ取得
	mTexture = prm->LoadTexture(eTEXTURE::CHARA, "Player.png");

	//音源取得
	mAudio = prm->LoadAudio(eAUDIO::WALK, "walking_on_floor1.mp3");

	//画像の設定================================================
	mSRC = 0;
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 40;
	mSprite.src.y = 0;
	mSprite.size.x = 40;
	mSprite.size.y = 40;
	mSprite.scale.x = 0.8f;
	mSprite.scale.y = 0.8f;

	mPos.mX =mBoadPos.mX * 32;
	mPos.mY =mBoadPos.mY * 32;

	mSprite.pos.x = static_cast<float> (mPos.mX);
	mSprite.pos.y = static_cast<float> (mPos.mY);
	//===========================================================

	mState = Player::MOVE::NONE;
}

//================================================
//			更新
//================================================
void Player::Update()
{
	//移動
	Move();
 
	//制限時間
	if (mTimerLimit <= -1)
		mTimerLimit = -1;

	//マスクの設定
	mpMask->SetAlpha(mPos, 0.002f);
}

//================================================
//			描画
//================================================
void Player::Draw()
{
	//描画
	mSprite.Draw();

#if defined(_DEBUG)
	DrawFormatString(320, 20, GetColor(255, 255, 255), "%d", mBoadPos.mX);
	DrawFormatString(340, 20, GetColor(255, 255, 255), "%d", mBoadPos.mY);
#endif
}

//================================================
//			移動
//================================================
void Player::Move()
{
	
	mVel.mX = 0;
	mVel.mY = 0;

	
	mSpeed = 2;

	switch (mState)
	{
		case MOVE::NONE:
		{
			if (IsButtonDown(PAD_INPUT_UP) == TRUE)
			{
				//ドアを開ける
				OpenDoor(mBoadPos.mX, mBoadPos.mY - 1);

				mSprite.src.y = mSRC + 120;

				//当たり判定
				if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
					return;

				//足音
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//ステージ上の座標
				mBoadPos.mY -= 1;

				//向き
				mState = MOVE::UP;
				mState2 = MOVE::UP;
				break;
			}
			if (IsButtonDown(PAD_INPUT_DOWN) == TRUE)
			{
				//ドアを開ける
				OpenDoor(mBoadPos.mX, mBoadPos.mY + 1);

				mSprite.src.y = mSRC;

				//当たり判定
				if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
					return;

				//足音
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//ステージ上の座標
				mBoadPos.mY += 1;

				//向き
				mState = MOVE::DOWN;
				mState2 = MOVE::DOWN;
				break;
			}
			if (IsButtonDown(PAD_INPUT_LEFT) == TRUE)
			{
				//ドアを開ける
				OpenDoor(mBoadPos.mX - 1, mBoadPos.mY);

				mSprite.src.y = mSRC + 40;

				//当たり判定
				if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
					return;

				//足音
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//ステージ上の座標
				mBoadPos.mX -= 1;

				//向き
				mState = MOVE::LEFT;
				mState2 = MOVE::LEFT;
				break;
			}
			if (IsButtonDown(PAD_INPUT_RIGHT) == TRUE)
			{
				//ドアを開ける
				OpenDoor(mBoadPos.mX + 1, mBoadPos.mY);

				mSprite.src.y = mSRC + 80;

				//当たり判定
				if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
					return;

				//足音
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//ステージ上の座標
				mBoadPos.mX += 1;

				//向き
				mState = MOVE::RIGHT;
				mState2 = MOVE::RIGHT;
				break;
			}
			break;
		}
		case MOVE::UP:
		{
			mVel.mY = -mSpeed;

			//移動モーション
			MoveMotion();

			break;
		}
		case MOVE::DOWN:
		{
			mVel.mY = mSpeed;

			//移動モーション
			MoveMotion();

			break;
		}
		case MOVE::LEFT:
		{
			mVel.mX = -mSpeed;

			//移動モーション
			MoveMotion();

			break;
		}
		case MOVE::RIGHT:
		{
			mVel.mX = mSpeed;

			//移動モーション
			MoveMotion();
			break;
		}
	}
	

	mStageBourd[mBoadPos.mY][mBoadPos.mX] = 4;

	mPos.mX += mVel.mX;
	mPos.mY += mVel.mY;

	mSprite.pos.x = static_cast<float> (mPos.mX);
	mSprite.pos.y = static_cast<float> (mPos.mY);
}

//================================================
//			移動モーション
//================================================
void Player::MoveMotion()
{
	mTimer++;
	if (mTimer == 10 / mSpeed)
	{
		mSprite.src.x -= 40;
	}
	if (mTimer == 20 / mSpeed)
	{
		mSprite.src.x += 80;
	}

	if (mTimer >= 32 / mSpeed)
	{
		StopSoundMem(mAudio);

		mSprite.src.x = 40;
		mState = MOVE::NONE;
		mTimer = 0;
	}
}

//================================================
//			ステージが移動したらプレイヤーも動く
//================================================
bool Player::StageMove(MOVE move)
{
	//向きで変える
	switch (move)
	{
		case Player::MOVE::UP:
		{
			mPos.mY += 7 * 32;
			mBoadPos.mY -= 1;
			break;
		}
		case Player::MOVE::DOWN:
		{
			mPos.mY -= 7 * 32;
			mBoadPos.mY += 1;
			break;
		}
		case Player::MOVE::LEFT:
		{
			mPos.mX += 26 * 32;
			mBoadPos.mX -= 1;
			break;
		}
		case Player::MOVE::RIGHT:
		{
			mPos.mX -= 26 * 32;
			mBoadPos.mX += 1;
			break;
		}
		default:
			break;
	}
		
	
	return false;
}

//================================================
//			ボタンが押されているか
//================================================
bool Player::CheckButton()
{
	if (IsButtonDown(PAD_INPUT_UP) ||
		IsButtonDown(PAD_INPUT_DOWN) ||
		IsButtonDown(PAD_INPUT_LEFT) ||
		IsButtonDown(PAD_INPUT_RIGHT))
		return true;
	return false;
}

//================================================
//			ドアを開ける
//================================================
void Player::OpenDoor(int x,int y)
{
	for (int i = 0; i < static_cast<int> (mpDoor.size()); i++)
	{
		if (mpDoor[i]->CheckPlayer(x, y) == false&&IsButtonPressed(PAD_INPUT_2)&&mKey>0&&mpDoor[i]!=nullptr)
		{
			mKey--;
			mpDoor[i]->OpenDoor();
			mSumKeyFlag = true;
		}
	}
}

//================================================
//			人形を拾う
//================================================
bool Player::PickDoll()
{
	for (int i = 0; i < static_cast<int>(mpDoll.size()); i++)
	{
		Int2 DollPos = mpDoll[i]->GetPos();
		if (DollPos.mX == mBoadPos.mX && DollPos.mY == mBoadPos.mY && IsButtonPressed(PAD_INPUT_1))
		{
			mpDoll[i]->Pick();

			return true;
		}
	}
	return false;
}

//================================================
//			向きの取得
//================================================
const Player::MOVE Player::GetDirection()
{
	return mState2;
}

//================================================
//			ステージ情報取得
//================================================
void Player::SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX])
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
//			ドアクラスの取得
//================================================
void Player::SetDoor(std::vector<Door*> pDoor, int DoorNum)
{
	mpDoor.resize(DoorNum);
	mpDoor = pDoor;
}

//================================================
//			人形クラスの取得
//================================================
void Player::SetDoll(std::vector<Doll*> pDoll, int DollNum)
{
	mpDoll.resize(DollNum);
	mpDoll = pDoll;
}

//================================================
//			初期位置の取得
//================================================
void Player::SetPos(int x, int y)
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			座標の取得
//================================================
const Int2 Player::Getpos()
{
	return mBoadPos;
}

//================================================
//			座標の取得
//================================================
const Int2 Player::GetposMicro()
{
	return mPos;
}

//================================================
//				ステージの当たり判定
//================================================
bool Player::StageCollision(int x,int y)
{
	for (int i = 0; i < static_cast<int> (mpDoor.size()); i++)
	{
		if (mpDoor[i] == nullptr)
			continue;
		if (mpDoor[i]->CheckPlayer(x,y) == false)
			return false;
	}

	if (mStageBourd[y][x] == 2 ||
		mStageBourd[y][x] == -1 && mTimerLimit > 0)
		return false;
	else
		return true;
	return true;
}

//================================================
//			全体の鍵の数
//================================================
void Player::SetKeyTotal(int keytotal)
{
	mKeyTotal = keytotal;
}

//================================================
//			全体の鍵の数の取得
//================================================
const int Player::GetKeyTotal()
{
	return mKeyTotal;
}

//================================================
//			鍵を増やす
//================================================
void Player::SetKey() 
{
	mKey++;
}

//================================================
//			鍵の数取得
//================================================
const int Player::CheckKey()
{
	return mKey;
}

//================================================
//			終了処理
//================================================
const void Player::Finalize()
{
	StopSoundMem(mAudio);
}

//================================================
//			ゴールの判定
//================================================
bool Player::CheckGoal()
{
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			if (mStageBourd[y][x] == 5)
			{
				num.mX = x;
				num.mY = y;
			}
		}
	}
	if (num.mX == mBoadPos.mX && num.mY == mBoadPos.mY)
		return true;

	return false;
}