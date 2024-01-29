/*
　クラス：敵クラスの派生クラス
　　　　　追いかける敵(Level2)
  作成者：三浦聖矢
  作成日：１2/1　　　　
*/
#include"ChaseGhostV2.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

#include<map>
#include<tchar.h>


//================================================
//			コンストラクタ
//================================================
ChaseGhostV2::ChaseGhostV2(Player* pPlayer)
: mSearchTimer{}
,mpPlayer{pPlayer}
, mEnemyRoot{}
, mEnemyMoveDraw{}
, mSearchFlag{ true }
, mEnemyRootFlag{ true }
, mRootPos{}
, mEnemyRootCount{}
{
	mType = TYPE::CHASE_LV2;

	mCheckMatrix[0].mX = 0;  mCheckMatrix[0].mY = 1;
	mCheckMatrix[1].mX = -1; mCheckMatrix[1].mY = 0;
	mCheckMatrix[2].mX = 0;  mCheckMatrix[2].mY = -1;
	mCheckMatrix[3].mX = 1;  mCheckMatrix[3].mY = 0;

}


//================================================
//		デストラクタ
//================================================
ChaseGhostV2::~ChaseGhostV2()
{
	
}


//================================================
//		初期化
//================================================
void ChaseGhostV2::Initialize()
{
	//初期座標の代入
	mBoadPos = Getpos();

	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::CHASEV2, "Chase2.png");

	//画像の設定============================
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
	//======================================


	mState = MOVE::NONE;
	//経路リセット
	ResetSearch();

	MapSetDefault();
	mMoveFlag = true;
}


//================================================
//		移動(A*)
//一応Ａ＊でプレイヤーを追いかけるプログラムを組みましたが、適当なサイトでパクッて使ったので僕の力ではほとんど組んでいません
//しかし一応理屈は理解しています
//A*難しいです
//================================================
void ChaseGhostV2::Move()
{
	MapSetDefault();
	
	for (int i = 0; i < 64; i++)
		SearchExecution();

	ConvertionRoot();

	if (mMoveFlag==true)
	{
		mState = mMoveEnemyRoot[0];
		mMoveFlag = false;
	}

	if (mMoveFlag == true)
		return;

	switch (mState)
	{
		case Enemy::MOVE::UP:
		{
			if (mTimer== 0)
			{
				mBoadPos.mY -= 1;
				ResetSearch();

				mMoveFlag = true;
			}
			
			mSprite.src.y = mSRC_y + 192;
			mVel.mY = -SPEED;

			MoveMotion2();
			
			break;
		}
		case Enemy::MOVE::DOWN:
		{
			if (mTimer == 0)
			{
				mBoadPos.mY += 1;
				ResetSearch();

				mMoveFlag = true;

			}
			mSprite.src.y = mSRC_y;
			mVel.mY = SPEED;

			MoveMotion2();

			break;
		}
		case Enemy::MOVE::LEFT:
		{
			if (mTimer == 0)
			{
				mBoadPos.mX -= 1;
				ResetSearch();

				mMoveFlag = true;

			}

			mSprite.src.y = mSRC_y + 64;
			mVel.mX = -SPEED;

			MoveMotion2();

			break;
		}
		case Enemy::MOVE::RIGHT:
		{
			if (mTimer == 0)
			{
				mBoadPos.mX += 1;
				ResetSearch();

				mMoveFlag = true;
			}
			
			mSprite.src.y = mSRC_y + 128;
			mVel.mX = SPEED;

			MoveMotion2();
			
			break;
		}
		
		default:
			break;
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
	//=========================================================================================
}


//================================================
//		移動モーション
//================================================
void ChaseGhostV2::MoveMotion2()
{
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


//================================================
//		デバック用
//================================================
void ChaseGhostV2::Draw2()
{
#if defined(_DEBUG)
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			if (mEnemyMove[y][x].mSearchStatus == STATUS::OPEN)
				DrawBox(32 * x - 16, 32 * y - 16, 32 * x + 16, 32 * y + 16, GetColor(0, 255, 0), false);
			if (mEnemyMove[y][x].mSearchStatus == STATUS::CLOSED)
				DrawBox(32 * x - 16, 32 * y - 16, 32 * x + 16, 32 * y + 16, GetColor(0, 0, 255), false);
		}
	}
#endif
}

//===================================================
//		A*処理
//===================================================
//↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
void ChaseGhostV2::SearchExecution()
{
	//特定の条件下処理
	if (mSearchFlag == true)
	{
		//敵の今の座標からスタート
		mEnemyMove[mBoadPos.mY][mBoadPos.mX].mSearchStatus = STATUS::OPEN;

		//経路探索実行
		Search();

		//プレイヤーの座標を記憶(ゴール)
		mRootPos.mX = mPlayerPos.mX;
		mRootPos.mY = mPlayerPos.mY;

		//サーチ終了
		mSearchFlag = false;
	}

	//サーチした経路を敵が移動するためにゴールからスタートまでの座標を1マスずつ記憶
	if (mEnemyRootFlag == true)
	{
		TraceRoot();
	}

}

void ChaseGhostV2::ResetSearch()
{
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			mEnemyMove[y][x].mCost = 0;
			mEnemyMove[y][x].mParent = -1;
			mEnemyMove[y][x].mSearchStatus = STATUS::NONE;
		}
	}

	//敵の移動ルートリセット
	for (int i = 0; i < ENEMY_MOVE_ROOT; i++)
	{
		mEnemyRoot[i].mX = 0;
		mEnemyRoot[i].mY = 0;
		mEnemyMoveDraw[i] = 0;
	}

	mSearchFlag = true;
	mEnemyRootFlag = true;
	mRootPos.mX = 0;
	mRootPos.mY = 0;
	mEnemyRootCount = 0;
}

void ChaseGhostV2::MapSetDefault()
{
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			mEnemyMove[y][x].mNumber = mStageBourd[y][x];
		}
	}
}

void ChaseGhostV2::TraceRoot()
{
	//ゴールを記憶
	if (mEnemyRootCount == 0)
	{
		//座標記憶
		mEnemyRoot[mEnemyRootCount].mX = mRootPos.mX;
		mEnemyRoot[mEnemyRootCount].mY = mRootPos.mY;

		//描画状態を記憶
		mEnemyMoveDraw[mEnemyRootCount] = mEnemyMove[mRootPos.mY][mRootPos.mX].mParent;

		//次の配列番号にする
		mEnemyRootCount++;
	}

	//座標からスタートまで1マスずつ戻る
	Int2* nParent_way = &mCheckMatrix[mEnemyMove[mRootPos.mY][mRootPos.mX].mParent];

	//座標を代入して実際に移動
	mRootPos.mX += nParent_way->mX;
	mRootPos.mY += nParent_way->mY;

	//記憶
	mEnemyRoot[mEnemyRootCount].mX = mRootPos.mX;
	mEnemyRoot[mEnemyRootCount].mY = mRootPos.mY;

	//描画状態記憶
	mEnemyMoveDraw[mEnemyRootCount] = mEnemyMove[mRootPos.mY][mRootPos.mX].mParent;

	//スタートの座標まで、戻ったら終了
	if (mRootPos.mX == mBoadPos.mX && mRootPos.mY == mBoadPos.mY)
	{
		mEnemyRootFlag = false;
	}
	else
	{
		//次の配列番号にする
		mEnemyRootCount++;
	}
}

int ChaseGhostV2::GetDistance(int FromX, int FromY, int ToX, int ToY)
{
	int x = FromX - ToX;
	int y = FromY - ToY;

	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;
	return x + y;
}

int ChaseGhostV2::BackTrace(int x, int y)
{
	if (x == mBoadPos.mX && y == mBoadPos.mY)
		return 1;

	int ParentWay = mEnemyMove[y][x].mParent;

	return BackTrace(x + mCheckMatrix[ParentWay].mX, y + mCheckMatrix[ParentWay].mY) + 1;
}

int ChaseGhostV2::Search()
{
	int nCost_min = 9999;
	int nBackCost = 0;
	int nCx = 0;
	int nCy = 0;

	EnemyMove* nN = NULL;
	
	//コストが最小のオープンノードを探す
	for (int y = 0; y < STAGE_SIZEY; y++)
	{
		for (int x = 0; x < STAGE_SIZEX; x++)
		{
			if (mEnemyMove[y][x].mSearchStatus != STATUS::OPEN)
			{
				continue;
			}
			if (GetDistance(x, y, (mPlayerPos.mX), (mPlayerPos.mY)) > nCost_min)
			{
				continue;
			}

			nCost_min = GetDistance(x, y, (mPlayerPos.mX), (mPlayerPos.mY));
			nN = &mEnemyMove[y][x];

			nCx = x;
			nCy = y;
		}
	}

	//オープンノードがなければ終了(ゴールが見つからない)ほぼ機能しない
	if (nN ==  nullptr)
	{
		return -9;
	}

	//ノードをクローズする
	nN->mSearchStatus = STATUS::CLOSED;

	nBackCost = BackTrace(nCx, nCy);

	for (int i = 0; i < CHECKMATRIX; i++)
	{
		int nCheck_X = nCx + mCheckMatrix[i].mX;
		int nCheck_Y = nCy + mCheckMatrix[i].mY;

		if (nCheck_X < 0 || nCheck_Y < 0)
		{
			continue;
		}
		if (nCheck_X >= STAGE_SIZEX || nCheck_Y >= STAGE_SIZEY)
		{
			continue;
		}

		//マップの壁,オブジェクトをよける
		if (mEnemyMove[nCheck_Y][nCheck_X].mNumber == 2 
			)
		{
			continue;
		}

		int nEstimate_cost = nBackCost + GetDistance(
			nCheck_X, nCheck_Y, (mPlayerPos.mX),
			(mPlayerPos.mY)
		) + 1;

		EnemyMove* nCell = &mEnemyMove[nCheck_Y][nCheck_X];

		if (mEnemyMove[nCheck_Y][nCheck_X].mSearchStatus == STATUS::NONE)
		{
			nCell->mParent = (i + 2) % 4;
			nCell->mSearchStatus = STATUS::OPEN;
		}
		else if (nEstimate_cost < nCell->mCost)
		{
			nCell->mParent = (i + 2) % 4;
			nCell->mCost = nEstimate_cost;
			nCell->mSearchStatus = STATUS::OPEN;
		}

	}

	//見つかったら探索終了
	if (nCx == (mPlayerPos.mX) && nCy == (mPlayerPos.mY))
	{
		return -1;
	}

	//再帰
	return Search();
}

void ChaseGhostV2::ConvertionRoot()
{

	for (int i = 0; i <= mEnemyRootCount; i++)
	{
		if (mEnemyMoveDraw[i] == 0)
			mMoveEnemyRoot2[i] = Enemy::MOVE::UP;
		if (mEnemyMoveDraw[i] == 1)
			mMoveEnemyRoot2[i] = Enemy::MOVE::RIGHT;
		if (mEnemyMoveDraw[i] == 2)
			mMoveEnemyRoot2[i] = Enemy::MOVE::DOWN;
		if (mEnemyMoveDraw[i] == 3)
			mMoveEnemyRoot2[i] = Enemy::MOVE::LEFT;
	}
	for (int i = 0; i <= mEnemyRootCount; i++)
	{
		mMoveEnemyRoot[i] = mMoveEnemyRoot2[mEnemyRootCount - 1 - i];
	}
}
