#include"Enemy.h"
#include"Ghost/ChaseGhost.h"
#include"Ghost/ChaseGhostV2.h"

/*
�@�N���X�F�G�N���X�̊��N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P0/2�@�@�@�@
*/

//================================================
//			�R���X�g���N�^
//================================================
Enemy::Enemy():
	mTextute{}
	, mSprite{}
	,mPos{}
	,mBoadPos{}
	,mVel{}
	,mStageBourd{}
	,mTimer{1}
	,mState{MOVE::NONE}
	, mMoveFlag{ true }
	,mRand{}
	, SPEED{ 1 }
	,mType{TYPE::NONE}
{
	
}

//================================================
//			�X�V
//================================================
void Enemy::Update()
{
	//�����̏�����
	mVel.mX = 0;
	mVel.mY = 0;

	//�v���C���[�̍��W�̎擾
	GetPlayerPos();

	//�ړ�
	Move();

	//�摜�𓮂���=====================================
	mPos.mX += mVel.mX;
	mPos.mY += mVel.mY;

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);
	//================================================
}

//================================================
//			�`��
//================================================
void Enemy::Draw()
{
	//�G�̕`��
	mSprite.Draw();

#if defined(_DEBUG)
	//�f�o�b�N�p========================================================
	DrawFormatString(320, 40, GetColor(255, 0, 0), "%d", mBoadPos.mX);
	DrawFormatString(360, 40, GetColor(255, 0, 0), "%d", mBoadPos.mY);

	Draw2();
	//=====================================================================
#endif
}

//================================================
//			�����_���ړ�
//================================================
void Enemy::MoveRand()
{
	/* �����_���ړ�
	�@�i�s�����ɕ����ꓹ���Q�ȏ゠��Ȃ痐���Ői�ޓ������߂�
	*/

	switch (mState)
	{
		case MOVE::NONE:
		{
			break;
		}
		/// ����������������������������������������������������������������������������������������������������������
		case MOVE::UP:
		{
			//�ړ��t���O�`�F�b�N
			if (mMoveFlag == true)
			{
				//���E�ǂ���ɂ�������������
				if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
				{
					//�����_���ȕ����ɓ���=======================
					mRand = GetRand(2);

					if (mRand == 0)
						mState = MOVE::LEFT;
					else if (mRand == 1)
						mState = MOVE::RIGHT;
					//============================================

					else if (mRand == 2 && StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
					{
						mRand = GetRand(1);

						if (mRand == 0)
							mState = MOVE::LEFT;
						else
							mState = MOVE::RIGHT;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::LEFT;
					else if (mRand == 1 && StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
					{
						mState = MOVE::LEFT;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::RIGHT;
					else if (mRand == 1 && StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
					{
						mState = MOVE::RIGHT;
					}

					mMoveFlag = false;
					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mY -= 1;
				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y;

			mVel.mY = -SPEED;

			MoveMotion();

			break;
		}
		//������������������������������������������������������������������������������������������������������������
		case MOVE::DOWN:
		{
			if (mMoveFlag == true)
			{
				if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
				{
					mRand = GetRand(2);

					if (mRand == 0)
						mState = MOVE::LEFT;
					else if (mRand == 1)
						mState = MOVE::RIGHT;
					else if (mRand == 2 && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
					{
						mRand = GetRand(1);

						if (mRand == 0)
							mState = MOVE::LEFT;
						else
							mState = MOVE::RIGHT;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::LEFT;
					else if (mRand == 1 && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
					{
						mState = MOVE::LEFT;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::RIGHT;
					else if (mRand == 1 && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
					{
						mState = MOVE::RIGHT;
					}

					mMoveFlag = false;
					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mY += 1;

				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y + 64;
			mVel.mY = SPEED;

			MoveMotion();

			break;
		}
		//������������������������������������������������������������������������������������������������������������������
		case MOVE::LEFT:
		{
			if (mMoveFlag == true)
			{
				if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					mRand = GetRand(2);

					if (mRand == 0)
						mState = MOVE::UP;
					else if (mRand == 1)
						mState = MOVE::DOWN;
					else if (mRand == 2 && StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
					{
						mRand = GetRand(1);

						if (mRand == 0)
							mState = MOVE::UP;
						else
							mState = MOVE::DOWN;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::UP;
					else if (mRand == 1 && StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
					{
						mState = MOVE::UP;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::DOWN;
					else if (mRand == 1 && StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
					{
						mState = MOVE::DOWN;
					}

					mMoveFlag = false;
					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mX -= 1;

				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y + 96;
			mVel.mX = -SPEED;

			MoveMotion();

			break;
		}
		//������������������������������������������������������������������������������������������������������������
		case MOVE::RIGHT:
		{
			if (mMoveFlag == true)
			{
				if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true && StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					mRand = GetRand(2);

					if (mRand == 0)
						mState = MOVE::UP;
					else if (mRand == 1)
						mState = MOVE::DOWN;
					else if (mRand == 2 && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
					{
						mRand = GetRand(1);

						if (mRand == 0)
							mState = MOVE::UP;
						else
							mState = MOVE::DOWN;
					}

					mMoveFlag = false;
					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::UP;
					else if (mRand == 1 && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
					{
						mState = MOVE::UP;
					}

					mMoveFlag = false;

					return;
				}
				else if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == true)
				{
					mRand = GetRand(1);

					if (mRand == 0)
						mState = MOVE::DOWN;
					else if (mRand == 1 && StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
					{
						mState = MOVE::DOWN;
					}

					mMoveFlag = false;

					return;
				}
			}

			if (mTimer == 0)
			{
				mBoadPos.mX += 1;

				mMoveFlag = true;
			}

			mSprite.src.y = mSRC_y + 32;

			mVel.mX = SPEED;

			MoveMotion();
			break;
		}
	}
}

//================================================
//			�X�e�[�W���擾
//================================================
void Enemy::SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX])
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
//			�ړ����[�V����
//================================================
void Enemy::MoveMotion()
{
	mTimer++;
	if (mTimer == 8/SPEED)
	{
		mSprite.src.x -= 32;
	}
	if (mTimer == 16 / SPEED || mTimer == 24 / SPEED)
	{
		mSprite.src.x += 32;
	}

	if (mTimer >= 32 / SPEED)
	{
		mSprite.src.x -= 32;
	
		mTimer = 0;
	}
}

//================================================
//			�G�̏����ʒu���
//================================================
void Enemy::SetPos(int x, int y)
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			�G�̈ʒu�擾(�}�b�v��)
//================================================
const Int2 Enemy::Getpos()
{
	return mBoadPos;
}

//================================================
//			�G�̈ʒu�擾�i�X�N���[����j
//================================================
const Int2 Enemy::GetposMicro()
{
	return mPos;
}

//================================================
//			�v���C���[�̍��W�擾
//================================================
void Enemy::GetPlayerPos()
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
//			�X�e�[�W�̓����蔻��
//================================================
bool Enemy::StageCollision(int x, int y)
{
	if (mStageBourd[y][x] == 2||
		mStageBourd[y][x] == -1)
		return false;

	return true;
}

//================================================
//			�v���C���[�Ƃ̓����蔻��
//================================================
bool Enemy::CheckHitPlayer()
{
	switch (mState)
	{
		case Enemy::MOVE::UP:
		{
			if (mStageBourd[mBoadPos.mY - 1][mBoadPos.mX] == 4)
				return false;
			break;
		}
		case Enemy::MOVE::DOWN:
		{
			if (mStageBourd[mBoadPos.mY + 1][mBoadPos.mX] == 4)
				return false;
			break;
		}
		case Enemy::MOVE::LEFT:
		{
			if (mStageBourd[mBoadPos.mY][mBoadPos.mX - 1] == 4)
				return false;
			break;
		}
		case Enemy::MOVE::RIGHT:
		{
			if (mStageBourd[mBoadPos.mY][mBoadPos.mX + 1] == 4)
				return false;
			break;
		}
		case Enemy::MOVE::NONE:
			break;
		default:
			break;
	}
	return true;
}

//================================================
//			�X�e�[�W����������G�̍��W�𓮂���	
//================================================
bool Enemy::StageMove(MOVE move)
{

	switch (move)
	{
		case Enemy::MOVE::UP:
		{
			mPos.mY += 8 * 32;
			break;
		}
		case Enemy::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Enemy::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Enemy::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}


	return false;

}
