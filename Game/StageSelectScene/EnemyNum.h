#pragma once
/*
�@�N���X�F�G�̐�
  �쐬�ҁF�O�Y����
  �쐬���F�P/13�@�@�@
*/
#include"../Utility.h"

class EnemyNum
{
public:
	//�G�̃^�C�v���Ƃ̐��̍\����
	struct EnemyTypeNum
	{
		int mNormalNum = 0;
		int mNormalLightNum = 0;
		int mChasel1Num = 0;
		int mChasel2Num = 0;
		int mHandNum = 0;
		int mKey = 0;
	};
private:
	int mTexture;		//�摜�f�[�^

	std::vector<std::vector<int>> mStage;	//�X�e�[�W�f�[�^
	SpriteData mSprite[6];		//�G�̉摜�p

	EnemyTypeNum mEnemyTypeNum[10];		//�G�̐�
public:
	EnemyNum();						//�R���X�g���N�^
	~EnemyNum();					//�f�X�g���N�^
		
	void Initialize();				//������
	void Draw(int low,int high);	//�`��

	void FinalStageDraw();			//�ŏI�X�e�[�W�p�̕`��	

	bool LoadCSV(int src);			//CSV�t�@�C���̓ǂݍ���

	EnemyTypeNum GetEnemyNum();		//�G�̐��擾
};