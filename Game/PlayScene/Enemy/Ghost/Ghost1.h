#pragma once
#include"../Enemy.h"

/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�����_���ړ�
  �쐬�ҁF�O�Y����
  �쐬���F�P0/2�@�@�@�@
*/

//�O���錾
class Player;

class Ghost1 :public Enemy
{
private:
	//�����p
	int mRand;

	Player* mpPlayer;	//�v���C���[�N���X
public:
	//�R���X�g���N�^
	Ghost1(Player* pPlayer);

	//�f�X�g���N�^
	~Ghost1()override;

	//������
	void Initialize()override;

	//�ړ�
	void Move()override;
	void Draw2()override {};

};