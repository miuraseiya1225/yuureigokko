/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F�P/3�@�@
*/
#pragma once
#include"../../Utility.h"

class Mist
{
private:
	SpriteData mSprite;		//�X�v���C�g
	int mTexture;		//�摜�f�[�^
	float mAlpha;		//�����x
public:
	Mist();		//�R���X�g���N�^
	~Mist();	//�f�X�g���N�^

	void Initialize();	//������
	void Update();		//�X�V
	const void Draw();		//�`��
};