/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F�P/15�@�@
*/
#pragma once
#include"../../Utility.h"

class Door
{
public:
	//����
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};
private:
	//�X�v���C�g
	SpriteData mSprite;

	//�摜�f�[�^
	int mTexture;

	//���W
	Int2 mPos;
	Int2 mBoadPos;

	//�����J���Ă��邩
	bool mOpenFlag;

	//�����f�[�^
	int mAudio;
public:
	Door(int x, int y);		//�R���X�g���N�^
	~Door();		//�f�X�g���N�^

	//������
	void Initialize();

	//�`��
	void Draw();

	//�h�A���J����
	void OpenDoor();

	//�h�A���J���Ă��邩
	bool CheckDoor() { return mOpenFlag; };

	//�v���C���[�̍��W�`�F�b�N
	bool CheckPlayer(int x, int y);

	//�X�e�[�W�����������̏���
	bool StageMove(MOVE move);
};