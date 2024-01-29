/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F�P/15�@�@
*/
#include "Door.h"
#include"../../Resource/Resource.h"

//================================================
//			�R���X�g���N�^
//================================================
Door::Door(int x, int y):
	mTexture{}
	,mSprite{}
	,mPos{}
	,mOpenFlag{false}
{
	mBoadPos.mX = x;
	mBoadPos.mY = y;

}

//================================================
//			�f�X�g���N�^
//================================================
Door::~Door()
{
	StopSoundMem(mAudio);
}

//================================================
//			������
//================================================
void Door::Initialize()
{
	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�̎擾
	mTexture = prm->LoadTexture(eTEXTURE::MAP_TILE, "tile.png");

	//�����f�[�^�̎擾
	mAudio = prm->LoadAudio(eAUDIO::OPENDOOR, "OpenDoor.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//�摜�̐ݒ�================================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 64;
	mSprite.src.y = 64;
	mSprite.size.x = 32;
	mSprite.size.y = 32;

	mPos.mX = mBoadPos.mX * 32;
	mPos.mY = mBoadPos.mY * 32;

	mSprite.pos.x =  static_cast<float> (mPos.mX);
	mSprite.pos.y =  static_cast<float> (mPos.mY);
	//==========================================================
}

//================================================
//				�`��
//================================================
void Door::Draw()
{
	mSprite.pos.x = static_cast<float> (mPos.mX);
	mSprite.pos.y = static_cast<float> (mPos.mY);

	mSprite.Draw();
}

//================================================
//			�h�A���J����
//================================================
void Door::OpenDoor()
{
	PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);

	mOpenFlag = true;

	mSprite.src.x = 128;
	mSprite.src.y = 128;
}

//================================================
//			�v���C���[�̍��W�`�F�b�N
//================================================
bool Door::CheckPlayer(int x,int y)
{
	if (x== mBoadPos.mX && y== mBoadPos.mY&&mOpenFlag == false)
		return false;
	return true;
}

//================================================
//			�X�e�[�W�������������������
//================================================
bool Door::StageMove(MOVE move)
{
	switch (move)
	{
		case Door::MOVE::UP:
		{
			mPos.mY += 8 * 32;

			break;
		}
		case Door::MOVE::DOWN:
		{
			mPos.mY -= 8 * 32;
			break;
		}
		case Door::MOVE::LEFT:
		{
			mPos.mX += 27 * 32;
			break;
		}
		case Door::MOVE::RIGHT:
		{
			mPos.mX -= 27 * 32;
			break;
		}
		default:
			break;
	}

	return false;
}
