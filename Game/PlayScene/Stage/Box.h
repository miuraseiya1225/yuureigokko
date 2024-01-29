#pragma once
/*
�@�N���X�F��
  �쐬�ҁF�O�Y����
  �쐬���F9/16�@�@
*/
#include"../../Utility.h"

//�O���錾
class Player;

class Box
{
public:
	//����
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};

private:
	Int2 mBoadPos;	//�X�e�[�W��̍��W
	Int2 mPos;		//�X�N���[����̍��W
	Int2 mPlayerPos;	//�v���C���[�̍��W	

	int mTexture;	//�摜�f�[�^
	SpriteData mSprite;		//�X�v���C�g

	int mStageBourd[STAGE_SIZEY][STAGE_SIZEX];		//�X�e�[�W�f�[�^

	bool mKeyNum;	//���������Ă��邩

	Player* mpPlayer;	//�v���C���[�N���X

	int mAudio;		//�����f�[�^
public:
	Box(Player* pPlayer);	//�R���X�g���N�^
	~Box();		//�f�X�g���N�^

	void Initialize();		//������
	void Update();		//�X�V
	const void Draw();	//�`��

	void SetPos(int x, int y);		//���W�̎擾
	void GetPlayerPos();		//�v���C���[�̍��W�擾

	const Int2 GetPos() { return mBoadPos; };		//���W�̃Q�b�^�[
	void SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX]);		//�X�e�[�W���̎擾

	void OpenBox();		//�����J����

	void DeleteKey();		//���𖳂���

	const bool ChackKey();		//���������Ă��邩

	bool StageMove(MOVE move);		//�X�e�[�W�����������̏���
};