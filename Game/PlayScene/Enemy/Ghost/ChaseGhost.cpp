/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�ǂ�������G(Level1)
  �쐬�ҁF�O�Y����
  �쐬���F�P�P/�Q�V�@�@�@�@
*/
#include"ChaseGhost.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

//================================================
//		�R���X�g���N�^
//================================================
ChaseGhost::ChaseGhost(Player* pPlayer):mpPlayer{pPlayer}
{
	mType = TYPE::CHASE_LV1;
}

//================================================
//		�f�X�g���N�^
//================================================
ChaseGhost::~ChaseGhost()
{

}

//================================================
//		������
//================================================
void ChaseGhost::Initialize()
{
	//�������W�̑��
	mBoadPos = Getpos();

	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::CHASEV1, "Chase1.png");

	//�摜�f�[�^�̐ݒ�=======================================
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

	//��������
	mState = MOVE::RIGHT;
}

//================================================
//		�ړ�
//================================================
void ChaseGhost::Move()
{
	/*  �ŒZ�����ł͂Ȃ����v���C���[��ǂ�������
	 
		���O���F�}�b�v��ɍs���~�܂肪�Ȃ����Œǂ�������v���O������g��ł���

		����
		�܂��i��ł�������ɕ����ꓹ���Q�ȏ゠������}�b�v��̃v���C���[�Ƃ̋������݂Ă��̕����ɐi��
		�c�����Ɖ������Ō��Ă���
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
		//������������������������������������������������������������������������������������������������������������
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
		//������������������������������������������������������������������������������������������������������������������
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
		//������������������������������������������������������������������������������������������������������������
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
	//===========================================================================================
}

//================================================
//		�ړ����[�V����
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