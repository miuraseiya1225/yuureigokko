#pragma once
/*
�@�N���X�F�Q�[��UI:���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/2�@�@�@�@
*/
#include"../../Utility.h"
#include<vector>
#include<iostream>

//�O���錾
class Player;
class Enemy;
class GameUI

{
protected:
	int mAudio;		//�����f�[�^

	Player* mpPlayer;		//�v���[���[�N���X

	std::vector<Enemy*> mpEnemy;		//�G�N���X

	SpriteData mSprite;		//�X�v���C�g

	Int2 mPos;		//���W	

	int mTexture;		//�摜�f�[�^

	int mEnemyNum;		//�G�̐�

	Int2 mPlayerPos;	//�v���[���[�̍��W

	int mTimer;		//�^�C�}�[
public:
	GameUI();		//�R���X�g���N�^
	virtual~GameUI()=0;		//�f�X�g���N�^

	virtual void Initialize() = 0;		//������

	virtual void Update()=0;		//�X�V
	virtual void Draw()=0;		//�`��

	void SetpEnemy(Enemy* pEnemy[],int EnemyNum);		//�G�N���X�̃A�h���X�擾
	void SetpPlayer(Player* pPlayer);			//�v���C���[�N���X�̃A�h���X�擾

	Player* GetpPlayer();	
	std::vector<Enemy*> GetpEnemy();

	//KEY================================
	void KeyUIFlag();
	//============================

	void Finalize();
};