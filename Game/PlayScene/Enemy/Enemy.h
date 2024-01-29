#pragma once
#include"../../Utility.h"

/*
�@�N���X�F�G�N���X�̊��N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P0/2�@�@�@�@
*/

class Enemy
{
public:
	enum class TYPE:int
	{
		NONE,

		NORMAL,
		CHASE_LV1,
		CHASE_LV2,
		TELEPORT,
		FIRE,
	};
	//�G�������Ă������
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};

protected:

	//�G�̈ړ����x
	int SPEED;

	//�����p
	int mRand;

	//�摜�f�[�^
	int mTextute;

	//�X�v���C�g
	SpriteData mSprite;

	//�؂���
	int mSRC_y;

	//���W	
	Int2 mPos;

	//�X�e�[�W��̍��W
	Int2 mBoadPos;

	//���x
	Int2 mVel;

	//�X�e�[�W�f�[�^
	int mStageBourd[STAGE_SIZEY][STAGE_SIZEX];

	//�^�C�}�[
	int mTimer;

	//�����̏��
	MOVE mState;

	MOVE mState2;

	//�ړ��p�t���O
	bool mMoveFlag;

	//�v���C���[�̍��W
	Int2 mPlayerPos;

	//�G�̃^�C�v
	TYPE mType;
public:
	//�R���X�g���N�^
	Enemy();

	//�f�X�g���N�^
	virtual ~Enemy() = default;

	//������(�����ɏ����ʒu)
	virtual void Initialize() = 0;

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�f�o�b�N�p
	virtual void Draw2() = 0;
	
	//�ړ�
	virtual void Move() = 0;

	//�����_���ړ�
	void MoveRand();

	//�ړ����[�V����
	void MoveMotion();

	//�X�e�[�W�f�[�^�̎擾
	void SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX]);

	//���W�̎擾�i�Ԃ�l�j
	void SetPos(int x, int y);
	const Int2 Getpos();
	const Int2 GetposMicro();

	//�v���C���[�̍��W�̎擾
	void GetPlayerPos();
	
	//�G�̃^�C�v�̎擾
	const TYPE GetTYPE() { return mType; };

	//�ǂƂ̓����蔻��
	bool StageCollision(int x, int y);

	//�v���C���[�Ƃ̓����蔻��
	bool CheckHitPlayer();

	//�X�e�[�W�ړ��ɉ����ēG��������
	bool StageMove(MOVE move);
};