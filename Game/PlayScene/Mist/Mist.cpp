#include "Mist.h"
/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F�P/3�@�@
*/
#include"../../Resource/Resource.h"
#include"../../GameMain.h"

//================================================
//			�R���X�g���N�^
//================================================
Mist::Mist():
	mSprite{}
	,mTexture{}
	,mAlpha{}
{
}

//================================================
//			�f�X�g���N�^
//================================================
Mist::~Mist()
{
}

//================================================
//			������
//================================================
void Mist::Initialize()
{
	//���\�[�X�}�l�[�W���[�擾
	ResourceManager* prm = ResourceManager::GetInstance();

	//�摜�f�[�^�擾
	mTexture = prm->LoadTexture(eTEXTURE::MIST, "mist.png");

	//�摜�̐ݒ�=============================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 1000;
	mSprite.size.y = 419;
	mSprite.scale.x = 2.0f;
	mSprite.scale.y = 2.0f;

	mSprite.pos.x = static_cast<float> (SCREEN_CENTER_X);
	mSprite.pos.y = static_cast<float> (SCREEN_CENTER_Y);
	//=======================================================
}

//================================================
//			�X�V
//================================================
void Mist::Update()
{
	//sin���g���Ĉڊǌo�߂Ŗ��̓����x��ς���
	mAlpha += 0.01f;

	mSprite.alpha = sinf(mAlpha) * sinf(mAlpha) * 0.2f;
}

//================================================
//			�`��
//================================================
const void Mist::Draw()
{
	//�`��
	mSprite.Draw();
}