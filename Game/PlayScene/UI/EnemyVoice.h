#pragma once
/*
�@�N���X�F�G�̖���
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/8�@�@�@�@
*/
#include"UI.h"

//�O���錾
class Enemy;
class Player;

class EnemyVoice :public GameUI
{
private:
	int mVoiceTimer;		//�����p
	std::vector<Int2> mEnemyPos;	//�G�̍��W
	std::vector<float> mRange;		//����
	int mRangeLow;					//�ŏ��̋���
public:
	//�R���X�g���N�^
	EnemyVoice(Enemy* pEnemy[],int EnemyNum, Player* pPlayer);

	//�f�X�g���N�^
	~EnemyVoice()override;

	void Initialize()override;		//������
	void Update()override;			//�X�V
	void Draw()override;			//�`��

	//�G�̋������v�Z����
	bool EnemyRange();
};