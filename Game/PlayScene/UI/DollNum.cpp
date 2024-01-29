/*
�@�N���X�F�l�`�̐�
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P/17�@�@�@�@
*/
#include "DollNum.h"
#include"../../Resource/Resource.h"

#include"../../GameData/GameData.h"

//=============================================
//			�R���X�g���N�^
//=============================================
DollNum::DollNum(GameData* pGameData):mpGameData{pGameData},mMoldSprite{},mDollNum{}
{
}

//=============================================
//			�f�X�g���N�^
//=============================================
DollNum::~DollNum()
{
}

//=============================================
//			������
//=============================================
void DollNum::Initialize()
{
	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�̎擾
	mTexture = prm->LoadTexture(eTEXTURE::DOLL, "miseityanningyou.png");

	//�摜�̐ݒ�=============================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.scale.x = 1.6f;
	mSprite.scale.y = 1.6f;
	//~=~=======================================

	//�^�̉摜�̎擾
	mTexture = prm->LoadTexture(eTEXTURE::DOLL_MOLD, "kata.png");

	//�^�̉摜�̐ݒ�==============================================
	mMoldSprite.SetTexture(mTexture);
	mMoldSprite.src.x = 0;
	mMoldSprite.src.y = 0;
	mMoldSprite.size.x = 128;
	mMoldSprite.size.y = 64;
	mMoldSprite.pos.x = static_cast<float>(SCREEN_RIGHT - 64);
	mMoldSprite.pos.y = static_cast<float>(160);
	//==========================================================
}

//=============================================
//			�X�V
//=============================================
void DollNum::Update()
{
	//�l�`�̐��̎擾
	mDollNum = mpGameData->GetDollNum();
}

//=============================================
//			�`��
//=============================================
void DollNum::Draw()
{
	mMoldSprite.Draw();

	mPos.mX = SCREEN_RIGHT - 105;
	mPos.mY = 165;
	for (int i = 0; i < mDollNum; i++)
	{
		mSprite.pos.x = static_cast<float>(mPos.mX);
		mSprite.pos.y = static_cast<float>(mPos.mY);
		mSprite.Draw();
		mPos.mX += 43;

	}
}