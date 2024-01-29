#include "GameLibSprite.h"
/*
	�摜��`�悷�邽�߂̍\����
*/

/*---------------------------------------------------
�R���X�g���N�^
---------------------------------------------------*/
SpriteData::SpriteData()
	: pos{ 0.0f, 0.0f }
	, src{ 0, 0 }
	, size{ 0, 0 }
	, center{ 0.5f, 0.5f }
	, scale{ 1.0f, 1.0f }
	, rot(0.0)
	, alpha(1.0f)
	, textureHandle(0)
{
}

/*---------------------------------------------------
�f�X�g���N�^
---------------------------------------------------*/
SpriteData::~SpriteData()
{
}

/*---------------------------------------------------
�摜�̓ǂݍ���
����	�F	const char* filename(�摜�̃t�@�C���p�X)
---------------------------------------------------*/
void SpriteData::SetTexture(int handle)
{
	textureHandle = handle;

	// �摜�T�C�Y�̎擾
	int sizeX = 0;
	int sizeY = 0;
	GetGraphSize(textureHandle, &sizeX, &sizeY);

	size.x = sizeX;
	size.y = sizeY;
}

/*---------------------------------------------------
�摜�̕`��
---------------------------------------------------*/
void SpriteData::Draw()
{
	// �����ʒu�̐ݒ�
	float cx = size.x * center.x;
	float cy = size.y * center.y;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha * 255.0f));

	DrawRectRotaGraph3F(
		pos.x, pos.y,
		src.x, src.y,
		size.x, size.y,
		cx, cy,
		(double)scale.x, (double)scale.y,
		rot,
		textureHandle,
		TRUE
	);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SpriteData::Finalize()
{
	DeleteGraph(textureHandle);
}
