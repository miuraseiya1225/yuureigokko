#pragma once
/*
�@�N���X�F�G�N���X�̔h���N���X
�@�@�@�@�@�ǂ�������G(Level1)
  �쐬�ҁF�O�Y����
  �쐬���F�P�P/�Q�V�@�@�@�@
*/
#include"../Enemy.h"

//�O���錾
class Player;

class ChaseGhost :public Enemy
{
private:
	Player* mpPlayer;	//�v���C���[�N���X
public:
	//�R���X�g���N�^
	ChaseGhost(Player* pPlayer);

	//�f�X�g���N�^
	~ChaseGhost()override;

	void Initialize()override;

	//�ړ�
	void Move()override;
	void Draw2()override {};

	//�ړ����[�V����
	void MoveMotion2();
};