/*
�@�N���X�F���ƌ��̐���	
  �쐬�ҁF�O�Y����
  �쐬���F�P/�P�@�@�@�@
*/

#pragma once
#include"Explanation.h"

class BoxExplanation :public Explanation
{
private:

public:
	BoxExplanation(GameData* pGameData);		//�R���X�g���N�^
	~BoxExplanation()override;					//�f�X�g���N�^

	void Initialize()override;					//������
	void Update()override;						//�X�V
	void Draw()override;						//�`��

	THUTRIAL FinalFlag()override;				//�I���t���O
};