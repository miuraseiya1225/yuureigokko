#pragma once
/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F�P2/11�@�@�@�@
*/
#include"../../Utility.h"

class Blood
{
private:
	SpriteData mSprite;

	int mTexture;	//�摜�f�[�^
	int mAudio;		//�����f�[�^�P
	int mAudio2;	//�����f�[�^�Q
	int mAudio3;	//�����f�[�^�R

	int mTimer;
public:
	Blood();		//�R���X�g���N�^
	~Blood();		//�f�X�g���N�^

	void Initialize();		//������

	void Update();			//�X�V

	void Draw();			//�`��

	const bool End();				//�I���t���O
};