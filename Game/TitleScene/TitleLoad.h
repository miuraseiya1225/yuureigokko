#pragma once
/*
�@�N���X�F�w�i�̖����X�N���[��
  �쐬�ҁF�O�Y����
  �쐬���F�P/2�@�@�@�@
*/
#include"../Utility.h"

class TitleLoad
{
private:
	SpriteData mSprite[2];	//�X�v���C�g
	int mTexture;			//�摜�f�[�^
	Int2 mPos[2];			//���W
public:
	TitleLoad();			//�R���X�g���N�^
	~TitleLoad();			//�f�X�g���N�^

	void Initialize();		//������
	void Update();			//�X�V
	const void Draw();			//�`��
};