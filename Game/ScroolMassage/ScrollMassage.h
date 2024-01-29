#pragma once
/*
�@�N���X�F���b�Z�[�W���O�N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P�Q/�Q�P�@�@�@�@
*/
#include"../Utility.h"

class ScrollMassage
{
private:
	std::string  mMassage;		//���b�Z�[�W
	Int2 mPos;					//���W
	int mMassageSize;			//�傫��
	int mMassageVel;			//��������
	int mMassageLine;			//���s
	int mTimer;					//�^�C�}�[
	int mMassageNum;			//���b�Z�[�W�̌�
	int mType;					//�^�C�v
	Color3 mColor;				//�F
public:
	//�R���X�g���N�^
	ScrollMassage();

	//�f�X�g���N�^
	~ScrollMassage();

	//���b�Z�[�W�̏�����
	void SetMessage(const std::string  massage, Int2 pos2, Color3 color3,const int massagesize = 18, const int massageVel = 30, const int massageline = 10,int Type=1);

	//���b�Z�[�W�̕`��
	bool DrawScrollMassage();

	//���b�Z�[�W�S�̂�`�悷��
	void DrawMassageAll();

	//���b�Z�[�W�̐ݒ�����Z�b�g����
	void Reset();
};