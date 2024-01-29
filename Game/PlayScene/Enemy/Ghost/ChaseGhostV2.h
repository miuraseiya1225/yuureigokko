#pragma once
/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�ǂ�������G(Level2)
  �쐬�ҁF�O�Y����
  �쐬���F�P2/1�@�@�@�@
*/
#include"../Enemy.h"
#include<vector>

//�O���錾
class Player;

//A*�֌W=================================
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
	//����
	static const int CHECKMATRIX = 4;
	//�ړ����[�g
	static const int ENEMY_MOVE_ROOT = 1000;
private:
	//�i�ǂ�����đg�񂾂̂��o���Ă܂���i�΁j�j
	//A*�֌W==============================================
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
	ChaseGhostV2(Player* pPlayer);		//�R���X�g���N�^
	~ChaseGhostV2()override;			//�f�X�g���N�^

	void Initialize()override;		//������
	
	void Move()override;		//�ړ�

	//�ړ����[�V����
	void MoveMotion2();

	void Draw2()override;

	//A*�֌W=======================================================
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

