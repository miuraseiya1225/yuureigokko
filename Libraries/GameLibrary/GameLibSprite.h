/*
	�摜��`�悷�邽�߂̍\����
*/

#pragma once

struct SpriteData
{

	// �����o�ϐ�----------------------------------------------------------

	struct float2
	{
		float x;
		float y;
	};

	struct int2
	{
		int x;
		int y;
	};

	// ���W
	float2 pos;

	// �؂���̊J�n�ʒu
	int2 src;

	// �؂���̏I���ʒu
	int2 size;

	// �摜�̒��S�ʒu
	float2 center;

	// �g�嗦
	float2 scale;

	// �p�x�iradian�j
	double rot;

	// �����x
	float alpha;

	// �摜�n���h��
	int textureHandle;

	// �����o�֐�----------------------------------------------------------

	// �R���X�g���N�^
	SpriteData();

	// �f�X�g���N�^
	~SpriteData();

	// �摜�n���h���̐ݒ�
	void SetTexture(int handle);

	// �`��
	void Draw();

	void Finalize();
};