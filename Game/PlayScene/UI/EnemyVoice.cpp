/*
�@�N���X�F�G�̖���
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/8�@�@�@�@
*/
#include"EnemyVoice.h"
#include"../../Resource/Resource.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy.h"

//=============================================
//			�R���X�g���N�^
//=============================================
EnemyVoice::EnemyVoice(Enemy* pEnemy[], int EnemyNum, Player* pPlayer)
{
	mpPlayer = pPlayer;
	mEnemyNum = EnemyNum;
	mpEnemy.resize(mEnemyNum);
	for (int i = 0; i < EnemyNum; i++)
	{
		mpEnemy[i] = pEnemy[i];
	}
}

//=============================================
//			�f�X�g���N�^
//=============================================
EnemyVoice::~EnemyVoice()
{
}

//=============================================
//			������
//=============================================
void EnemyVoice::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�����f�[�^�̎擾
	mAudio = prm->LoadAudio(eAUDIO::NORMAL, "ghost_ah.wav");
	ChangeVolumeSoundMem(255, mAudio);

	//�G�̍��W�擾
	mEnemyPos.resize(mEnemyNum);

	//�v���C���[�̍��W�擾
	mPlayerPos = mpPlayer->GetposMicro();

	//�G�̍��W�擾
	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();
	}
	mRange.resize(mEnemyNum);
}

//=============================================
//			�X�V
//=============================================
void EnemyVoice::Update()
{
	if (mpPlayer->GetTimerLimit() < 1)
		return;

	//��ԋ߂��G�̖����𗬂�=============================================================-
	//�^�C�v���ƂɈႤ
	//�����ɉ����ă{�����[����ς���
	if (EnemyRange() == true)
	{
		switch (mpEnemy[mRangeLow]->GetTYPE())
		{
			case Enemy::TYPE::NORMAL:
			{
				ResourceManager* prm = ResourceManager::GetInstance();
				mAudio = prm->LoadAudio(eAUDIO::BLACK, "iki.wav");
				ChangeVolumeSoundMem(255 - static_cast<int>(mRange[mRangeLow] / 3.0f), mAudio);

				break;
			}
			case Enemy::TYPE::CHASE_LV1:
			{
				ResourceManager* prm = ResourceManager::GetInstance();
				mAudio = prm->LoadAudio(eAUDIO::CHASEV1, "5ihihi.wav");
				ChangeVolumeSoundMem(255 - static_cast<int>(mRange[mRangeLow] / 3.0f), mAudio);
				break;
			}
			case Enemy::TYPE::CHASE_LV2:
			{
				ResourceManager* prm = ResourceManager::GetInstance();
				mAudio = prm->LoadAudio(eAUDIO::CHASEV2, "nigasanai.wav");
				ChangeVolumeSoundMem(255 - static_cast<int>(mRange[mRangeLow] / 3.0f), mAudio);
				break;
			}
			case Enemy::TYPE::TELEPORT:
			{
				ResourceManager* prm = ResourceManager::GetInstance();
				mAudio = prm->LoadAudio(eAUDIO::HAND, "15rei_warai.wav");
				ChangeVolumeSoundMem(255 - static_cast<int>(mRange[mRangeLow] / 3.0f), mAudio);
				break;
			}
			case Enemy::TYPE::FIRE:
			{
				ResourceManager* prm = ResourceManager::GetInstance();
				mAudio = prm->LoadAudio(eAUDIO::NORMAL, "ghost_ah.wav");
				ChangeVolumeSoundMem(255 - static_cast<int>(mRange[mRangeLow] / 3.0f), mAudio);
				break;
			}
			default:
				break;
		}
		mVoiceTimer++;
	}
	else
	{
		mVoiceTimer = 256;

		StopSoundMem(mAudio);
	}
	//==================================================================================
	if (mAudio == 0)
		return;

	if (mVoiceTimer > 256)
	{
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);
		mVoiceTimer = 0;
	}
}

void EnemyVoice::Draw()
{
}

//=============================================
//			�G�̋����̌v�Z
//=============================================
bool EnemyVoice::EnemyRange()
{
	//�v���C���[�̍��W�擾
	mPlayerPos = mpPlayer->GetposMicro();

	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();

		//�G�̋������v�Z=================================
		float RangeX = static_cast<float>(mPlayerPos.mX - mEnemyPos[i].mX);
		float RangeY = static_cast<float>(mPlayerPos.mY - mEnemyPos[i].mY);

		if (RangeX < 0)
			RangeX *= -1;
		if (RangeY < 0)
			RangeY *= -1;

		mRange[i] = (RangeX * RangeX) + (RangeY * RangeY);

		mRange[i] = static_cast<float> (sqrt(mRange[i]));

		//==============================================
	}

	mRangeLow = 0;

	//��ԃv���C���[�ɋ߂��G��T��===============================================
	for (int i = 0; i < mEnemyNum; i++)
	{
		if (mRange[mRangeLow] > mRange[i])
			mRangeLow = i;
	}
	//=========================================================-

	//�G�̍��G�������w��
	if (mRange[mRangeLow] < 320.0f)
		return true;

	return false;
}