/*
�@�N���X�F�v���C���[
  �쐬�ҁF�O�Y����
  �쐬���F9/16�@�@
*/

#include"Box.h"

#include"../../Resource/Resource.h"
#include"../Player/Player.h"

//================================================
//			�R���X�g���N�^
//================================================
Box::Box(Player* pPlayer):
	mBoadPos{}
,mPos{}
,mSprite{}
,mPlayerPos{}
,mKeyNum{true}
,mpPlayer{pPlayer}
{

}

//================================================
//				�f�X�g���N�^
//================================================
Box::~Box()
{
	StopSoundMem(mAudio);
}

//================================================
//			������
//================================================
void Box::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�擾
	mTexture = prm->LoadTexture(eTEXTURE::BOX, "box.png");

	//�����f�[�^�擾
	mAudio = prm->LoadAudio(eAUDIO::OPENBOX, "OpenBox.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//�摜�̐ݒ�==========================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;

	mBoadPos = GetPos();

	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;
	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);
	//===============================================
}

//================================================
//			�X�V
//================================================
void Box::Update()
{
	//�v���C���[�̍��W�擾
	GetPlayerPos();

	mSprite.pos.x = static_cast<float>(mPos.mX);
	mSprite.pos.y = static_cast<float>(mPos.mY);

	//�O�����̒藝���g���ăv���C���[�̋������v�Z���A���̋����ɉ����Ĕ��̓����x��ω�������==========
	//�v���C���[�̈ʒu���擾
	Int2 PlayerPosMicro = mpPlayer->GetposMicro();

	float RangeX = static_cast<float>(mPos.mX - PlayerPosMicro.mX);
	float RangeY = static_cast<float>(mPos.mY - PlayerPosMicro.mY);

	if (RangeX <= 0)
		RangeX *= -1;
	if (RangeY <= 0)
		RangeY *= -1;

	float Range = sqrtf((RangeX * RangeX) + (RangeY * RangeY));

	mSprite.alpha = (320.0f - Range) / 320.0f;
	//============================================================================================-
}

//================================================
//			�`��
//================================================
const void Box::Draw()
{
	//�`��
	mSprite.Draw();
}

//================================================
//			���W�̎擾
//================================================
void Box::SetPos(int x, int y)
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;
}

//================================================
//			�X�e�[�W�f�[�^�̎擾
//================================================
void Box::SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX])
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
//			�v���C���[�̍��W�擾
//================================================
void Box::GetPlayerPos()
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
//			�����J����
//================================================
void Box::OpenBox()
{
	if (mBoadPos.mX == mPlayerPos.mX &&
		mBoadPos.mY == mPlayerPos.mY)
	{
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);
		mSprite.src.x = 32;
	}
}

//================================================
//			���𖳂���
//================================================
void Box::DeleteKey()
{
	mKeyNum = false;
}

//================================================
//			�������邩�ǂ���
//================================================
const bool Box::ChackKey()
{
	if (mBoadPos.mX != mPlayerPos.mX ||
		mBoadPos.mY != mPlayerPos.mY)
	{
		return false;
	}
	if (mKeyNum == true)
		return true;
	return false;
}

//================================================
//			�X�e�[�W���ړ������甠��������
//================================================
bool Box::StageMove(MOVE move)
{
	switch (move)
	{
		case Box::MOVE::UP:
		{
			mPos.mY += 8 * 32;
			break;
		}
		case Box::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Box::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Box::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}


	return false;
}
