/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F�P2/11�@�@�@�@
*/
#include"Blood.h"
#include"../../Resource/Resource.h"

//================================================
//		�R���X�g���N�^
//================================================
Blood::Blood():
	mSprite{}
	,mTexture{}
	,mTimer{}
{

}

//================================================
//		�f�X�g���N�^
//================================================
Blood::~Blood()
{

}

//================================================
//		������
//================================================
void Blood::Initialize()
{
	//���\�[�X�}�l�[�W���[
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�̓ǂݍ���
	mTexture = prm->LoadTexture(eTEXTURE::BLOOD, "Blood.png");

	//�����f�[�^�̓ǂݍ���
	mAudio = prm->LoadAudio(eAUDIO::CREAM, "himei_kyaaaaaaaa.wav");
	ChangeVolumeSoundMem(255, mAudio);

	//�����f�[�^�̓ǂݍ���
	mAudio2 = prm->LoadAudio(eAUDIO::BLOOD, "blood_flow.mp3");
	ChangeVolumeSoundMem(255, mAudio2);

	//�����f�[�^�̓ǂݍ���
	mAudio3 = prm->LoadAudio(eAUDIO::ATTACK, "hit_axe3.mp3");
	ChangeVolumeSoundMem(255, mAudio3);

	//�摜�f�[�^�̐ݒ�========================================-
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 500;
	mSprite.size.y = 693;
	mSprite.scale.x = 1.5f;
	mSprite.scale.y = 1.5f;
	//====================================================
}

//================================================
//		�X�V
//================================================
void Blood::Update()
{
	//���Ԍo�߂ŉ����𗬂�======================================
	if (mTimer == 20)
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, true);

	if(mTimer == 80)
		PlaySoundMem(mAudio3, DX_PLAYTYPE_BACK, true);

	if (mTimer == 90)
		PlaySoundMem(mAudio2, DX_PLAYTYPE_BACK, true);
	//=========================================================

	mTimer++;
}

//================================================
//		�`��
//================================================
void Blood::Draw()
{
	//���Ԍo�߂ŉ摜��`�悷��===============================
	if (mTimer > 90)
	{
		mSprite.pos.x = 400;
		mSprite.pos.y = 300;
		mSprite.Draw();
		mSprite.pos.x = 200;
		mSprite.pos.y = 300;
		mSprite.Draw();
	}
	if (mTimer > 91)
	{
		mSprite.pos.x = 1100;
		mSprite.pos.y = 600;
		mSprite.Draw();
	}
	if (mTimer > 92)
	{
		mSprite.pos.x = 1100;
		mSprite.pos.y = 100;
		mSprite.Draw();
	}
	if (mTimer > 93)
	{
		mSprite.pos.x = 400;
		mSprite.pos.y = 650;
		mSprite.Draw();
		mSprite.pos.x = 200;
		mSprite.pos.y = 550;
		mSprite.Draw();
	}
	if (mTimer > 94)
	{
		mSprite.pos.x = 700;
		mSprite.pos.y = 300;
		mSprite.Draw();
	}
	//===============================================
}

const bool Blood::End()
{
	//��莞�Ԍo�߂ŏI��
	if (mTimer > 150)
		return true;
	return false;
}