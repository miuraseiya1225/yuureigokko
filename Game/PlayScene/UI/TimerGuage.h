#pragma once
/*
�@�N���X�F��������
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/9�@�@�@�@
*/
#include"UI.h"

//�O���錾
class GameData
	;
class TimerGuage :public GameUI
{
private:
	int mTimerLimit;		//��������

	GameData* mpGameData;	//�Q�[���f�[�^
public:
	TimerGuage(GameData* pGameData);	//�R���X�g���N�^
	~TimerGuage()override;			//�f�X�g���N�^

	void Initialize()override;		//������

	void Update()override;		//�X�V

	void Draw()override;		//�`��
};