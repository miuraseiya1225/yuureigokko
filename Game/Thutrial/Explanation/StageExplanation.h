/*
�@�N���X�F�X�e�[�W�̐���
  �쐬�ҁF�O�Y����
  �쐬���F�P/2�@�@�@�@
*/
#pragma once
#include"Explanation.h"

class StageExplanation :public Explanation
{
private:
public:
	StageExplanation(GameData* pGameData);	//�R���X�g���N�^
	~StageExplanation()override;			//�f�X�g���N�^

	void Initialize()override;				//������
	void Update()override;					//�X�V
	void Draw()override;					//�`��
	THUTRIAL FinalFlag()override;			//�I���t���O

};