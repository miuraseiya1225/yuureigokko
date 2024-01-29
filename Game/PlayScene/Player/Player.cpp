/*
�@�N���X�F�v���C���[
  �쐬�ҁF�O�Y����
  �쐬���F9/16�@�@
*/
#include"Player.h"
#include"../../Resource/Resource.h"
#include"../Mask/Mask.h"
#include"../Stage/Door.h"
#include"../Stage/Doll.h"

//================================================
//			�R���X�g���N�^
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
//				�f�X�g���N�^
//================================================
Player::~Player()
{
	Finalize();
}

//================================================
//			������
//================================================
void Player::Initialize()
{
	//���x�̍X�V	
	mVel.mX = 0;
	mVel.mY = 0;

	//�������W�擾
	mBoadPos = Getpos();

	//�S�̂̌��̐��擾
	mKeyTotal = GetKeyTotal();

	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�e�N�X�`���擾
	mTexture = prm->LoadTexture(eTEXTURE::CHARA, "Player.png");

	//�����擾
	mAudio = prm->LoadAudio(eAUDIO::WALK, "walking_on_floor1.mp3");

	//�摜�̐ݒ�================================================
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
//			�X�V
//================================================
void Player::Update()
{
	//�ړ�
	Move();
 
	//��������
	if (mTimerLimit <= -1)
		mTimerLimit = -1;

	//�}�X�N�̐ݒ�
	mpMask->SetAlpha(mPos, 0.002f);
}

//================================================
//			�`��
//================================================
void Player::Draw()
{
	//�`��
	mSprite.Draw();

#if defined(_DEBUG)
	DrawFormatString(320, 20, GetColor(255, 255, 255), "%d", mBoadPos.mX);
	DrawFormatString(340, 20, GetColor(255, 255, 255), "%d", mBoadPos.mY);
#endif
}

//================================================
//			�ړ�
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
				//�h�A���J����
				OpenDoor(mBoadPos.mX, mBoadPos.mY - 1);

				mSprite.src.y = mSRC + 120;

				//�����蔻��
				if (StageCollision(mBoadPos.mX, mBoadPos.mY - 1) == false)
					return;

				//����
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//�X�e�[�W��̍��W
				mBoadPos.mY -= 1;

				//����
				mState = MOVE::UP;
				mState2 = MOVE::UP;
				break;
			}
			if (IsButtonDown(PAD_INPUT_DOWN) == TRUE)
			{
				//�h�A���J����
				OpenDoor(mBoadPos.mX, mBoadPos.mY + 1);

				mSprite.src.y = mSRC;

				//�����蔻��
				if (StageCollision(mBoadPos.mX, mBoadPos.mY + 1) == false)
					return;

				//����
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//�X�e�[�W��̍��W
				mBoadPos.mY += 1;

				//����
				mState = MOVE::DOWN;
				mState2 = MOVE::DOWN;
				break;
			}
			if (IsButtonDown(PAD_INPUT_LEFT) == TRUE)
			{
				//�h�A���J����
				OpenDoor(mBoadPos.mX - 1, mBoadPos.mY);

				mSprite.src.y = mSRC + 40;

				//�����蔻��
				if (StageCollision(mBoadPos.mX - 1, mBoadPos.mY) == false)
					return;

				//����
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//�X�e�[�W��̍��W
				mBoadPos.mX -= 1;

				//����
				mState = MOVE::LEFT;
				mState2 = MOVE::LEFT;
				break;
			}
			if (IsButtonDown(PAD_INPUT_RIGHT) == TRUE)
			{
				//�h�A���J����
				OpenDoor(mBoadPos.mX + 1, mBoadPos.mY);

				mSprite.src.y = mSRC + 80;

				//�����蔻��
				if (StageCollision(mBoadPos.mX + 1, mBoadPos.mY) == false)
					return;

				//����
				PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

				//�X�e�[�W��̍��W
				mBoadPos.mX += 1;

				//����
				mState = MOVE::RIGHT;
				mState2 = MOVE::RIGHT;
				break;
			}
			break;
		}
		case MOVE::UP:
		{
			mVel.mY = -mSpeed;

			//�ړ����[�V����
			MoveMotion();

			break;
		}
		case MOVE::DOWN:
		{
			mVel.mY = mSpeed;

			//�ړ����[�V����
			MoveMotion();

			break;
		}
		case MOVE::LEFT:
		{
			mVel.mX = -mSpeed;

			//�ړ����[�V����
			MoveMotion();

			break;
		}
		case MOVE::RIGHT:
		{
			mVel.mX = mSpeed;

			//�ړ����[�V����
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
//			�ړ����[�V����
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
//			�X�e�[�W���ړ�������v���C���[������
//================================================
bool Player::StageMove(MOVE move)
{
	//�����ŕς���
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
//			�{�^����������Ă��邩
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
//			�h�A���J����
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
//			�l�`���E��
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
//			�����̎擾
//================================================
const Player::MOVE Player::GetDirection()
{
	return mState2;
}

//================================================
//			�X�e�[�W���擾
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
//			�h�A�N���X�̎擾
//================================================
void Player::SetDoor(std::vector<Door*> pDoor, int DoorNum)
{
	mpDoor.resize(DoorNum);
	mpDoor = pDoor;
}

//================================================
//			�l�`�N���X�̎擾
//================================================
void Player::SetDoll(std::vector<Doll*> pDoll, int DollNum)
{
	mpDoll.resize(DollNum);
	mpDoll = pDoll;
}

//================================================
//			�����ʒu�̎擾
//================================================
void Player::SetPos(int x, int y)
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			���W�̎擾
//================================================
const Int2 Player::Getpos()
{
	return mBoadPos;
}

//================================================
//			���W�̎擾
//================================================
const Int2 Player::GetposMicro()
{
	return mPos;
}

//================================================
//				�X�e�[�W�̓����蔻��
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
//			�S�̂̌��̐�
//================================================
void Player::SetKeyTotal(int keytotal)
{
	mKeyTotal = keytotal;
}

//================================================
//			�S�̂̌��̐��̎擾
//================================================
const int Player::GetKeyTotal()
{
	return mKeyTotal;
}

//================================================
//			���𑝂₷
//================================================
void Player::SetKey() 
{
	mKey++;
}

//================================================
//			���̐��擾
//================================================
const int Player::CheckKey()
{
	return mKey;
}

//================================================
//			�I������
//================================================
const void Player::Finalize()
{
	StopSoundMem(mAudio);
}

//================================================
//			�S�[���̔���
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