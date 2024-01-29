/*
�@�N���X�F�l�`
  �쐬�ҁF�O�Y����
  �쐬���F�P/16�@�@
*/
#include "Doll.h"
#include"../../Resource/Resource.h"
#include"../Player/Player.h"

//================================================
//			�R���X�g���N�^
//================================================
Doll::Doll(int x, int y):mPickFlag{false},mSoundFlag{false},mBoadPos{}
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			�f�X�g���N�^
//================================================
Doll::~Doll()
{
	StopSoundMem(mAudio);
}

//================================================
//			������
//================================================
void Doll::Initialize()
{
	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�̎擾
	mTexture = prm->LoadTexture(eTEXTURE::DOLL, "miseityanningyou.png");

	//�����f�[�^�̎擾
	mAudio = prm->LoadAudio(eAUDIO::GETKEY, "GetKey.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//�摜�̐ݒ�=================================================
	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;

	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	mSprite.rot = sin((2 * DX_PI * GetRand(360) / 360));
	//=============================================================
}

//================================================
//			�X�V
//================================================
void Doll::Update(Player* pPlayer)
{
	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	//���Ԑ؂�ɂȂ�����l�`������
	if (pPlayer->GetTimerLimit() < 0)
		mPickFlag = true;

	//�v���C���[���l�`���E���������===============
	if (mPickFlag == true)
	{
		mBoadPos.mX = -3;
		mBoadPos.mY = -3;

		if(mSoundFlag==false)
			PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);
		mSoundFlag = true;
	}
	//===============================================

	//�O�����̒藝���g���ăv���C���[�̋������v�Z���A���̋����ɉ����Đl�`�̓����x��ω�������==========
	//�v���C���[�̈ʒu���擾
	Int2 PlayerPosMicro = pPlayer->GetposMicro();

	float RangeX = static_cast<float>((mPos.mX)- PlayerPosMicro.mX);
	float RangeY = static_cast<float>((mPos.mY) - PlayerPosMicro.mY);

	if (RangeX <= 0)
		RangeX *= -1;
	if (RangeY <= 0)
		RangeY *= -1;

	float Range = sqrtf((RangeX * RangeX) + (RangeY * RangeY));

	mSprite.alpha = (416.0f - Range) / 416.0f;
	//==============================================================================================
}

//================================================
//			�`��
//================================================
const void Doll::Draw()
{
	//�l�`�������Ă���Ȃ�`�悵�Ȃ�
	if (mPickFlag == true)
		return;

	mSprite.Draw();
}

//================================================
//			�X�e�[�W���ړ�������l�`���ړ�����
//================================================
bool Doll::StageMove(MOVE move)
{
	switch (move)
	{
		case Doll::MOVE::UP:
		{
			mPos.mY += 8 *32;

			break;
		}
		case Doll::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Doll::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Doll::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}

	return false;
}
