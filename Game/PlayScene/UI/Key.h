#pragma once
/*
�@�N���X�F���������Ă��邩�ۂ�
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/8�@�@�@�@
*/
#include"UI.h"

class KeyCheck :public GameUI
{
public:
	//���̑傫��
	static const int KEY_SIZE = 25;
private:
	SpriteData mKeySprite;			//���p�X�v���C�g
	SpriteData mKeyBreakSprite;		//���j��p�X�v���C�g
	int mKeyNum;			//���̐�
	int mKeyBreakTimer;		//���̔j��p�^�C�}�[
public:
	KeyCheck(int keynum);		//�R���X�g���N�^

	~KeyCheck()override;		//�f�X�g���N�^

	void Initialize()override;		//������

	void Update()override;			//�X�V

	void Draw()override;		//�`��
};