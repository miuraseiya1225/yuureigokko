#include "Fire.h"
#include"../../../Resource/Resource.h"
#include"../../Player/Player.h"

/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�߂��܂ōs���Ȃ��Ǝ��F�ł��Ȃ��G
  �쐬�ҁF�O�Y����
  �쐬���F�P�P/�Q�V�@�@�@�@
*/

//================================================
//			�R���X�g���N�^
//================================================
Fire::Fire(Player* pPlayer):mpPlayer{pPlayer}
{
	mType = TYPE::FIRE;

}

//================================================
//			�f�X�g���N�^
//================================================
Fire::~Fire()
{
}

//================================================
//			������
//================================================
void Fire::Initialize()
{
	//�������W�̑��
	mBoadPos = Getpos();

	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();
	mTextute = prm->LoadTexture(eTEXTURE::NORMALLIGHT, "NormalGhostAll.png");

	//�摜�̐ݒ�=================================
	mSRC_y = 0;

	mSprite.SetTexture(mTextute);
	mSprite.src.x = 32;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;

	mPos.mX = 32 * mBoadPos.mX;
	mPos.mY = 32 * mBoadPos.mY;

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);
	//========================================

	//����
	mState = MOVE::RIGHT;
}

//================================================
//			�ړ�
//================================================
void Fire::Move()
{
	//�����_���ړ�
	MoveRand();
	
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

	mSprite.alpha = (192.0f - Range) / 192.0f;
	//================================================================================
}