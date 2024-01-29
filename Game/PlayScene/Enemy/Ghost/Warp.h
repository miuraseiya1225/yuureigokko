#pragma once
/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@���[�v���Ēǂ�������G
  �쐬�ҁF�O�Y����
  �쐬���F�P�Q/�Q�P�@�@�@�@
*/
#include"../Enemy.h"

//�O���錾
class Player;

//�G�N���X�̌p���q�N���X
class Warp :public Enemy
{
public:
	//�u�Ԉړ����鎞�Ԃ̊��o
	static const int TELEPORT_INTERVAL = 256;

	//�v���C���[��ǂ��z�������̈ړ��͈�
	static const int VANISH_RANGE = 1;

	//���X�ɏ����鎞��
	static const int ALFHA_INTERVAL = 120;
private:
	int mMoveTimer;		//�ړ��p�^�C�}�[
	int mAlphaTimer;	//�����x�p�^�C�}�[

	Player* mpPlayer;	//�v���C���[�N���X	
public:
	//�R���X�g���N�^
	Warp(Player* pPlayer);

	//�f�X�g���N�^
	~Warp()override;

	//������
	void Initialize()override;

	//�ړ�
	void Move()override;

	//�u�Ԉړ��p============
	void Vanish();

	bool Vanish2();

	void Teleportation();
	//======================

	void Draw2()override {};

};