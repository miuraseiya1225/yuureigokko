#pragma once
/*
　クラス：敵クラスの派生クラス
　　　　　追いかける敵(Level2)
  作成者：三浦聖矢
  作成日：１2/1　　　　
*/
#include"../Enemy.h"
#include<vector>

//前方宣言
class Player;

//A*関係=================================
enum class STATUS :int
{
	NONE,
	OPEN,
	CLOSED,
};

struct EnemyMove
{
	int mNumber;
	int mCost;
	STATUS mSearchStatus;
	int mParent;
};
//========================================

class ChaseGhostV2 :public Enemy
{
public:
	//方向
	static const int CHECKMATRIX = 4;
	//移動ルート
	static const int ENEMY_MOVE_ROOT = 1000;
private:
	//（どうやって組んだのか覚えてません（笑））
	//A*関係==============================================
	Int2 mCheckMatrix[CHECKMATRIX];
	EnemyMove mEnemyMove[STAGE_SIZEY][STAGE_SIZEX];
	Int2 mEnemyRoot[ENEMY_MOVE_ROOT];
	int mEnemyMoveDraw[ENEMY_MOVE_ROOT];
	bool mSearchFlag;
	bool mEnemyRootFlag;
	Int2 mRootPos;
	int mEnemyRootCount;
	int mSearchTimer;
	MOVE mMoveEnemyRoot[ENEMY_MOVE_ROOT];
	MOVE mMoveEnemyRoot2[ENEMY_MOVE_ROOT];
	//=====================================================
	Player* mpPlayer;
public:
	ChaseGhostV2(Player* pPlayer);		//コンストラクタ
	~ChaseGhostV2()override;			//デストラクタ

	void Initialize()override;		//初期化
	
	void Move()override;		//移動

	//移動モーション
	void MoveMotion2();

	void Draw2()override;

	//A*関係=======================================================
	void SearchExecution();
	void ResetSearch();
	void MapSetDefault();
	void TraceRoot();
	int GetDistance(int FromX, int FromY, int ToX, int ToY);
	int BackTrace(int x, int y);
	int Search();

	void ConvertionRoot();
	//==============================================================
};

