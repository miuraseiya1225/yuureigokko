#pragma once
/*
�@�N���X�F�}�X�N�N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/30�@�@�@�@
*/
#include"../../Utility.h"

class Mask
{
public:
	//�}�X�N�̉𑜓x�i����������Əd���Ȃ�\��������j
	static const int BLACK_SIZE = 12;

private:
	int mTexture;	//�摜�f�[�^

	//�X�v���C�g===============================================
	std::vector<std::vector<SpriteData>> mAlphaSprite1;
	std::vector<std::vector<SpriteData>> mAlphaSprite2;
	std::vector<std::vector<SpriteData>> mAlphaSprite3;
	std::vector<std::vector<SpriteData>> mAlphaSprite4;
	//======================================================

	//�����x
	float mAlpha;

	//���W
	Int2 mPos;
	Int2 mPos2;

	//�}�X�N�̑傫��
	float mAlpha_Frequency;
public:
	Mask();		//�R���X�g���N�^
	~Mask();	//�f�X�g���N�^

	void Initialize();	//������

	void Draw();		//�`��

	void SetAlpha(Int2 BasePos, float Alpha_Frequency);		//�}�X�N�̐ݒ�

	void ResetMask();	//�}�X�N�̏�����

	void Finalize();	//�I������
};