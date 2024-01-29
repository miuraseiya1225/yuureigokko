/*
�@�N���X�F�w�i�̖����X�N���[��
  �쐬�ҁF�O�Y����
  �쐬���F�P/2�@�@�@�@
*/
#include "TitleLoad.h"
#include"../GameMain.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
TitleLoad::TitleLoad():mSprite{},mTexture{},mPos{}
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
TitleLoad::~TitleLoad()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void TitleLoad::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* Resource = ResourceManager::GetInstance();

	//�摜�f�[�^�̎擾
	mTexture = Resource->LoadTexture(eTEXTURE::TITLE_LOAD, "TitleLoad.png");

	//�摜�̐ݒ�===============================================================
	mSprite[0].SetTexture(mTexture);
	mSprite[0].src.x = 0;
	mSprite[0].src.y = 0;
	mSprite[0].size.x = 320;
	mSprite[0].size.y = 96;
	mSprite[0].scale.x = 5.0f;
	mSprite[0].scale.y = 5.0f;
	mSprite[0].pos.x = SCREEN_CENTER_X + 200;
	mSprite[0].pos.y = SCREEN_CENTER_Y - 100;

	mSprite[1].SetTexture(mTexture);
	mSprite[1].src.x = 0;
	mSprite[1].src.y = 0;
	mSprite[1].size.x = 320;
	mSprite[1].size.y = 96;
	mSprite[1].scale.x = 5.0f;
	mSprite[1].scale.y = 5.0f;
	mSprite[0].pos.x = SCREEN_CENTER_X + 200 + 320;
	mSprite[0].pos.y = SCREEN_CENTER_Y - 100;
	//=======================================================================-
}

/*--------------------------------------------------
�X�V
--------------------------------------------------*/
void TitleLoad::Update()
{
	
	for (int i = 0; i < 2; i++)
	{
		if (mPos[i].mX <= SCREEN_CENTER_X + 200 - 320)
			mPos[i].mX = SCREEN_CENTER_X + 200 + 320;
		mPos[i].mX -= 2;
		mSprite[i].pos.x = static_cast<float>(mPos[i].mX);
	}
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
const void TitleLoad::Draw()
{
	for(int i=0;i<2;i++)
		mSprite[i].Draw();
}
