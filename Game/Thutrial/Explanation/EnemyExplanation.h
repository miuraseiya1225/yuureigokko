/*
�@�N���X�F�G�̐���
  �쐬�ҁF�O�Y����
  �쐬���F�P/�P�@�@�@�@
*/
#pragma once
#include"Explanation.h"

class EnemyExplanation :public Explanation
{
private:
public:
	EnemyExplanation(GameData* pGameData);		//�R���X�g���N�^
	~EnemyExplanation()override;				//�f�X�g���N�^

	void Initialize()override;					//������
	void Update()override;						//�X�V
	void Draw()override;						//�`��
	THUTRIAL FinalFlag()override;				//�I���t���O

};