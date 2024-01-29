/*
�@�N���X�F���������Ă��邩�ۂ�
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/8�@�@�@�@
*/
#include"Key.h"
#include"../Player/Player.h"

#include"../../Resource/Resource.h"

#include<iostream>
#include"../../GameMain.h"

//=============================================
//			�R���X�g���N�^
//=============================================
KeyCheck::KeyCheck(int keynum): mKeySprite{},mKeyBreakTimer{25},mKeyBreakSprite{}
{
	mKeyNum = keynum;
}

//=============================================
//			�f�X�g���N�^
//=============================================
KeyCheck::~KeyCheck()
{

}

//=============================================
//			������
//=============================================
void KeyCheck::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�擾
	mTexture = prm->LoadTexture(eTEXTURE::BOX, "box.png");

	//�摜�̐ݒ�==========================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 64;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.scale.x = 4.0f;
	mSprite.scale.y = 4.0f;

	mSprite.pos.x = SCREEN_RIGHT - 64;
	mSprite.pos.y = 64;
	//===================================================

	//���摜�̐ݒ�	==============================================
	mKeySprite.SetTexture(mTexture);
	mKeySprite.src.x = 96;
	mKeySprite.src.y = 0;
	mKeySprite.size.x = 32;
	mKeySprite.size.y = 32;
	mKeySprite.scale.x = 1.0f;
	mKeySprite.scale.y = 1.0f;
	//=========================================================

	//���j��摜�̐ݒ�==============================================
	mKeyBreakSprite.SetTexture(mTexture);
	mKeyBreakSprite.src.x = 256;
	mKeyBreakSprite.src.y = 0;
	mKeyBreakSprite.size.x = 32;
	mKeyBreakSprite.size.y = 32;
	mKeyBreakSprite.scale.x = 1.0f;
	mKeyBreakSprite.scale.y = 1.0f;
	mKeyBreakSprite.pos.x = static_cast<float>(mPlayerPos.mX);
	mKeyBreakSprite.pos.y = static_cast<float>(mPlayerPos.mY - 30);
	//==============================================================

	//�����擾
	mAudio = prm->LoadAudio(eAUDIO::GETKEY, "GetKey.mp3");
	ChangeVolumeSoundMem(255, mAudio);

	//�v���C���[�N���X�̎擾
	mpPlayer = GetpPlayer();

	//�v���C���[�̍��W�擾
	mPlayerPos = mpPlayer->GetposMicro();
}

//=============================================
//			�X�V
//=============================================
void KeyCheck::Update()
{
	//�v���C���[�̍��W�擾
	mPlayerPos = mpPlayer->GetposMicro();

	if(mTimer<90)
		mTimer++;

	if (mTimer == 0)
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK);

	//�v���[���[�������J������A�j���[�V�����𗬂�
	if (mpPlayer->GetSumKeyFlag() == true)
	{
		mKeyBreakTimer = 0;
		mpPlayer->SetSumKeyFlag();
	}

	if (mKeyBreakTimer < 25)
		mKeyBreakTimer++;
	else
	{
		mKeyBreakSprite.src.x = 64;
		mKeyBreakSprite.src.y = 0;
	}

	mKeyBreakSprite.pos.x = static_cast<float>(mPlayerPos.mX);
	mKeyBreakSprite.pos.y = static_cast<float>(mPlayerPos.mY - 30);
}

void KeyCheck::Draw()
{
	//�w�i
	DrawBox(SCREEN_RIGHT - 128, 0, SCREEN_RIGHT, 128, GetColor(255, 255, 255), true);

	//��
	mSprite.Draw();

	//���̌�============================================================
	int defaultSize = GetFontSize();

	SetFontSize(KEY_SIZE);

	DrawFormatString(SCREEN_RIGHT - 100, 100, GetColor(0, 0, 0), "�~%2d/%2d", mpPlayer->CheckKey(),mKeyNum);

	SetFontSize(defaultSize);
	//===================================================================

	//�������������̂t�h========================
	if (mTimer < 90)
	{
		mKeySprite.pos.x = static_cast<float>(mPlayerPos.mX);
		mKeySprite.pos.y = static_cast<float>(mPlayerPos.mY - 30);
		mKeySprite.scale.x = sin(mTimer / 10.0f);
		mKeySprite.Draw();
	}
	//===========================================

	//�����J�������̂t�h==============================
	if (mKeyBreakTimer == 0)
	{
		mKeyBreakSprite.src.x = 64;
		mKeyBreakSprite.src.y = 0;
	}
	if (mKeyBreakTimer == 8)
	{
		mKeyBreakSprite.src.x = 128;
		mKeyBreakSprite.src.y = 0;
	}
	if (mKeyBreakTimer == 16)
	{
		mKeyBreakSprite.src.x = 160;
		mKeyBreakSprite.src.y = 0;
	}
	if (mKeyBreakTimer == 24)
	{
		mKeyBreakSprite.src.x = 192;
		mKeyBreakSprite.src.y = 0;
	}
	if(mKeyBreakTimer<25)
		mKeyBreakSprite.Draw();
	//===========================================
}