#pragma once
/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�߂��܂ōs���Ȃ��Ǝ��F�ł��Ȃ��G	
  �쐬�ҁF�O�Y����
  �쐬���F�P�P/�Q�V�@�@�@�@
*/
#include"../Enemy.h"

//�O���錾
class Player;

class Fire :public Enemy
{
private:
	Player* mpPlayer;		//�v���C���[�N���X
public:
	Fire(Player* pPlayer);	//�R���X�g���N�^
	~Fire()override;		//�f�X�g���N�^

	//������
	void Initialize()override;

	//�ړ�
	void Move()override;
	void Draw2()override {};
};