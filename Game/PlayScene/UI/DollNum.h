#pragma once
/*
�@�N���X�F�l�`�̐�
		�@�Q�[��UI:�h���N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P/17�@�@�@�@
*/
#include"UI.h"

//�O���錾
class GameData;

class DollNum :public GameUI
{
private:
	GameData* mpGameData;		//�Q�[���f�[�^�N���X
	SpriteData mMoldSprite;		//�l�`�̌^�p�̃X�v���C�g

	int mDollNum;		//�l�`�̐�
public:
	DollNum(GameData* pGameData);		//�R���X�g���N�^
	~DollNum()override;		//�f�X�g���N�^

	void Initialize()override;		//������
	void Update()override;			//�X�V
	void Draw()override;			//�`��
};