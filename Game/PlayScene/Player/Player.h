#pragma once
/*
�@�N���X�F�v���C���[
  �쐬�ҁF�O�Y����
  �쐬���F9/16�@�@
*/
#include"../../Utility.h"

#include"../Stage/Stage.h"

//�O���錾
class Mask;
class Door;
class Doll;

class Player
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
	//�摜����
	SpriteData mSprite;

	//�摜�n���h��
	int mTexture;

	//�����n���h��
	int mAudio;

	//���x	
	Int2 mVel;
	int mSpeed;

	//�X�e�[�W�f�[�^
	int mStageBourd[STAGE_SIZEY][STAGE_SIZEX];

	//�`��ʒu
	Int2 mPos;

	//�X�e�[�W��̍��W
	Int2 mBoadPos;

	//�ړ��p�^�C�}�[	
	int mTimer;

	//����
	MOVE mState;
	MOVE mState2;

	//���̐�
	int mKey;

	//�S�̂̌��̐�
	int mKeyTotal;

	//��������
	int mTimerLimit;

	//�S�[���p���W
	Int2 num;

	//�摜�؂���ʒu
	int mSRC;

	//�}�X�N�N���X
	Mask* mpMask;

	//�h�A�N���X
	std::vector<Door*> mpDoor;

	//�l�`�N���X
	std::vector<Doll*> mpDoll;

	//UI�p�t���O
	bool mSumKeyFlag;

	//�X�e�[�W�ړ��t���O
	bool mStageMoveFlag;
public:
	Player(Mask* pMask);		//�R���X�g���N�^
	~Player();					//�f�X�g���N�^

	void Initialize();			//������
	void Update();				//�X�V
	void Draw();				//�`��
	void Move();				//�ړ�
	void MoveMotion();			//�ړ��A�j���[�V����

	bool StageMove(MOVE move);	//�X�e�[�W���ړ������珈������

	bool CheckButton();			//�{�^���������ꂽ��

	//�����J����
	void OpenDoor(int x, int y);

	bool PickDoll();	//�l�`���E��

	//�X�e�[�W���擾
	void SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX]);	

	//���N���X�̃A�h���X�擾
	void SetDoor(std::vector<Door*> pDoor, int DoorNum);

	//�l�`�N���X�̃A�h���X
	void SetDoll(std::vector<Doll*> pDoll, int DollNum);

	//�����ʒu�擾
	void SetPos(int x, int y);

	//�v���C���[�̍��W
	const Int2 Getpos();

	//�v���C���[�̉�ʏ�̍��W
	const Int2 GetposMicro();

	//�v���C���[�̌���
	const MOVE GetDirection();

	//��������
	void SetTimerLimit(int timer) { mTimerLimit = timer; };
	const int GetTimerLimit() { return mTimerLimit; };

	//�X�e�[�W�̓����蔻��
	bool StageCollision(int x,int y);

	//���̍��v�擾
	void SetKeyTotal(int keytotal);

	//�S�̂̌��̐�	
	const int GetKeyTotal();

	//���̎擾
	void SetKey();
	const int CheckKey();

	//UI�p
	void SetSumKeyFlag() { mSumKeyFlag = false; };
	const bool GetSumKeyFlag() { return mSumKeyFlag; };
	
	//�S�[��������
	bool CheckGoal();

	//�I������
	const void Finalize();
};