#pragma once
/*
�@�N���X�F�v���C���[�̐S��
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/3�@�@�@�@
*/
#include"UI.h"

class HeartBeat :public GameUI
{
private:
	int mBeatTimer;		//�S���p

	std::vector<Int2> mEnemyPos;	//�G�̍��W

	float mRadius;		//���a

	float mBeatInterval;	//�S����炷�Ԋu	

	std::vector<float> mRange;		//����

	int mRangeLow;		//�ŏ��̋���

	float mAlpha;		//�����x
public:
	HeartBeat();		//�R���X�g���N�^
	~HeartBeat();		//�f�X�g���N�^

	void Initialize()override;		//������

	void Update()override;			//�X�V	

	void Draw()override;			//�`��

	bool EnemyRange();				//�G�Ƃ̋���	
};