/*
�@�N���X�F�v���C���[�̐S��
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/8�@�@�@�@
*/
#include"HeartBeat.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy.h"
#include"../../Resource/Resource.h"

//=============================================
//			�R���X�g���N�^
//=============================================
HeartBeat::HeartBeat():
	mBeatTimer{}
	,mRadius{0.0f}
{

}

//=============================================
//			�f�X�g���N�^
//=============================================
HeartBeat::~HeartBeat()
{

}

//=============================================
//			������
//=============================================
void HeartBeat::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�擾
	mTexture = prm->LoadTexture(eTEXTURE::RED_SCREEN, "RedScreen.png");

	//�����f�[�^�̎擾
	mAudio = prm->LoadAudio(eAUDIO::HEART, "HeartBeat2.mp4");
	ChangeVolumeSoundMem(255, mAudio);

	//�Ԃ����==========================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 640;
	mSprite.size.y = 480;
	mSprite.scale.x = 4.0f;
	mSprite.scale.y = 4.0f;
	mSprite.pos.x = 320;
	mSprite.pos.y = 240;
	mSprite.alpha = 0.3f;
	//====================================

	//�v���C���[�̃A�h���X�擾
	mpPlayer = GetpPlayer();

	//�G�̃A�h���X�擾
	mpEnemy = GetpEnemy();

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
void HeartBeat::Update()
{
	if (mpPlayer->GetTimerLimit() < 1)
		return;

	//�v���C���[�̃A�h���X�擾
	mPlayerPos = mpPlayer->GetposMicro();
	
	//�G�̍��W�擾
	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();
	}

	//�G���߂��ɂ��Ȃ�������Ԃ�===============================-
	if (EnemyRange() == false)
	{
		mRadius = 0.0f;
		mAlpha = 0.0f;
		StopSoundMem(mAudio);
		return;
	}

	//�G���߂��قǐԂ�����
	mAlpha = (256.0f - mRange[mRangeLow]) / 512.0f;

	//��莞�Ԍo�����特�����~�߂�
	if (mRadius > 96)
	{
		mRadius = 0;
		StopSoundMem(mAudio);
	}


	if (mRadius == 0)
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

	//�G���߂��قǐS���𑁂�����
	mBeatInterval = (256.0f - mRange[mRangeLow]) / 32.0f;

	if (mBeatInterval < 0)
		mBeatInterval = 0;

	mRadius += mBeatInterval;
}

//=============================================
//			�`��
//=============================================
void HeartBeat::Draw()
{
	//�G���߂��ɂ��Ȃ�������Ԃ�===============================-
	if (EnemyRange() == false)
		return;

	mSprite.Draw();

	//�S���̕`��================================================================
	DrawCircle(mPlayerPos.mX, mPlayerPos.mY, 2, GetColor(255, 0, 0), true);

	for (int i = 0; i < 5; i++)
	{
		DrawCircle(mPlayerPos.mX, mPlayerPos.mY, static_cast<int>(mRadius) + i, GetColor(64, 0, 0), false);
	}
	//============================================================================--

	mSprite.alpha = mAlpha;
}

//=============================================
//			�G�Ƃ̋���
//=============================================
bool HeartBeat::EnemyRange()
{
	for (int i = 0; i < mEnemyNum; i++)
	{
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
	if (mRange[mRangeLow] < 256.0f)
		return true;

	return false;
}

