/*
　クラス：敵の鳴き声
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/8　　　　
*/
#include"EnemyVoice.h"
#include"../../Resource/Resource.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy.h"

//=============================================
//			コンストラクタ
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
//			デストラクタ
//=============================================
EnemyVoice::~EnemyVoice()
{
}

//=============================================
//			初期化
//=============================================
void EnemyVoice::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//音声データの取得
	mAudio = prm->LoadAudio(eAUDIO::NORMAL, "ghost_ah.wav");
	ChangeVolumeSoundMem(255, mAudio);

	//敵の座標取得
	mEnemyPos.resize(mEnemyNum);

	//プレイヤーの座標取得
	mPlayerPos = mpPlayer->GetposMicro();

	//敵の座標取得
	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();
	}
	mRange.resize(mEnemyNum);
}

//=============================================
//			更新
//=============================================
void EnemyVoice::Update()
{
	if (mpPlayer->GetTimerLimit() < 1)
		return;

	//一番近い敵の鳴き声を流す=============================================================-
	//タイプごとに違う
	//距離に応じてボリュームを変える
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
//			敵の距離の計算
//=============================================
bool EnemyVoice::EnemyRange()
{
	//プレイヤーの座標取得
	mPlayerPos = mpPlayer->GetposMicro();

	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();

		//敵の距離を計算=================================
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

	//一番プレイヤーに近い敵を探す===============================================
	for (int i = 0; i < mEnemyNum; i++)
	{
		if (mRange[mRangeLow] > mRange[i])
			mRangeLow = i;
	}
	//=========================================================-

	//敵の索敵距離を指定
	if (mRange[mRangeLow] < 320.0f)
		return true;

	return false;
}