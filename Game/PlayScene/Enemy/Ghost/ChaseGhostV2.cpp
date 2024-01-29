/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�ǂ�������G(Level2)
  �쐬�ҁF�O�Y����
  �쐬���F�P2/1�@�@�@�@
*/
#include"ChaseGhostV2.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

#include<map>
#include<tchar.h>


//================================================
//			�R���X�g���N�^
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
//		�f�X�g���N�^
//================================================
ChaseGhostV2::~ChaseGhostV2()
{
	
}


//================================================
//		������
//================================================
void ChaseGhostV2::Initialize()
{
	//�������W�̑��
	mBoadPos = Getpos();

	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::CHASEV2, "Chase2.png");

	//�摜�̐ݒ�============================
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
	//�o�H���Z�b�g
	ResetSearch();

	MapSetDefault();
	mMoveFlag = true;
}


//================================================
//		�ړ�(A*)
//�ꉞ�`���Ńv���C���[��ǂ�������v���O������g�݂܂������A�K���ȃT�C�g�Ńp�N�b�Ďg�����̂Ŗl�̗͂ł͂قƂ�Ǒg��ł��܂���
//�������ꉞ�����͗������Ă��܂�
//A*����ł�
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

	//�O�����̒藝���g���ăv���C���[�̋������v�Z���A���̋����ɉ����ēG�̓����x��ω�������==========
	//�v���C���[�̈ʒu���擾
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
//		�ړ����[�V����
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
//		�f�o�b�N�p
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
//		A*����
//===================================================
//����������������������������������������������������������
void ChaseGhostV2::SearchExecution()
{
	//����̏���������
	if (mSearchFlag == true)
	{
		//�G�̍��̍��W����X�^�[�g
		mEnemyMove[mBoadPos.mY][mBoadPos.mX].mSearchStatus = STATUS::OPEN;

		//�o�H�T�����s
		Search();

		//�v���C���[�̍��W���L��(�S�[��)
		mRootPos.mX = mPlayerPos.mX;
		mRootPos.mY = mPlayerPos.mY;

		//�T�[�`�I��
		mSearchFlag = false;
	}

	//�T�[�`�����o�H��G���ړ����邽�߂ɃS�[������X�^�[�g�܂ł̍��W��1�}�X���L��
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

	//�G�̈ړ����[�g���Z�b�g
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
	//�S�[�����L��
	if (mEnemyRootCount == 0)
	{
		//���W�L��
		mEnemyRoot[mEnemyRootCount].mX = mRootPos.mX;
		mEnemyRoot[mEnemyRootCount].mY = mRootPos.mY;

		//�`���Ԃ��L��
		mEnemyMoveDraw[mEnemyRootCount] = mEnemyMove[mRootPos.mY][mRootPos.mX].mParent;

		//���̔z��ԍ��ɂ���
		mEnemyRootCount++;
	}

	//���W����X�^�[�g�܂�1�}�X���߂�
	Int2* nParent_way = &mCheckMatrix[mEnemyMove[mRootPos.mY][mRootPos.mX].mParent];

	//���W�������Ď��ۂɈړ�
	mRootPos.mX += nParent_way->mX;
	mRootPos.mY += nParent_way->mY;

	//�L��
	mEnemyRoot[mEnemyRootCount].mX = mRootPos.mX;
	mEnemyRoot[mEnemyRootCount].mY = mRootPos.mY;

	//�`���ԋL��
	mEnemyMoveDraw[mEnemyRootCount] = mEnemyMove[mRootPos.mY][mRootPos.mX].mParent;

	//�X�^�[�g�̍��W�܂ŁA�߂�����I��
	if (mRootPos.mX == mBoadPos.mX && mRootPos.mY == mBoadPos.mY)
	{
		mEnemyRootFlag = false;
	}
	else
	{
		//���̔z��ԍ��ɂ���
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
	
	//�R�X�g���ŏ��̃I�[�v���m�[�h��T��
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

	//�I�[�v���m�[�h���Ȃ���ΏI��(�S�[����������Ȃ�)�قڋ@�\���Ȃ�
	if (nN ==  nullptr)
	{
		return -9;
	}

	//�m�[�h���N���[�Y����
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

		//�}�b�v�̕�,�I�u�W�F�N�g���悯��
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

	//����������T���I��
	if (nCx == (mPlayerPos.mX) && nCy == (mPlayerPos.mY))
	{
		return -1;
	}

	//�ċA
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
