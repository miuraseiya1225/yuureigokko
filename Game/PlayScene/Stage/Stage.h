#pragma once
/*
�@�N���X�F�X�e�[�W
  �쐬�ҁF�O�Y����
  �쐬���F9/16�@�@
*/

#include<string>

#include"../../Utility.h"
#include"../../GameMain.h"

#include"../Player/Player.h"
#include"../Enemy/Enemy.h"
#include"Box.h"
#include"../UI/UI.h"
#include"../Mask/Mask.h"
#include"../Mist/Mist.h"
#include"Door.h"
#include"Doll.h"

//�O���錾
class GameData;

class Stage
{
public:
	//�G��z�u�ł���ő吔
	static const int ENEMY_NUM = 32;

	//����z�u�ł���ő吔
	static const int BOX_NUM = 32;

	//UI�̐�
	static const int UI_NUM = 5;

	//�V�[��
	enum class RESULTSCENE :int
	{
		GOAL,
		DIE,
		TIMEOVER,
		THUTRIAL,
		THUTRIAL2,
		THUTRIAL3,

		NONE,
	};

	//�X�e�[�W�؂�ւ��p
	enum class MODE :int
	{
		PLAY,
		THUTRIAL,
		THUTRIAL2,
		THUTRIAL3,
	};
private:
	//�X�e�[�W�؂�ւ��p
	int mSelectNum;

	//���[�h
	MODE mMode;

	//�V�[���̐؂�ւ��p
	RESULTSCENE mRS;

	//�b�r�u�X�e�[�W�f�[�^�̕ۑ��p�z��
	int mStage[STAGE_SIZEY][STAGE_SIZEX];

	//�X�e�[�W�f�[�^�X�V�p�z��
	int mStageDefault[STAGE_SIZEY][STAGE_SIZEX];

	//�摜�p����\����
	SpriteData mSprite[STAGE_SIZEY][STAGE_SIZEX];

	//�摜�n���h��
	int mTexture;

	//�`����W	
	Float2 mPos;
	Int2 mPos2;

	//���̈ʒu
	Int2 mBoxPos;

	//�v���[���[�̈ʒu
	Int2 mPlayerPos;

	//�v���C���[�N���X�̃|�C���^
	Player* mpPlayer;

	//�G�N���X�̃|�C���^
	Enemy* mpEnemy[ENEMY_NUM];

	//���̃|�C���^
	Box* mpBox[BOX_NUM];

	//�h�A�N���X
	std::vector<Door*> mpDoor;

	//UI�N���X
	GameUI* mpUI[UI_NUM];

	//�}�X�N�N���X
	Mask* mpMask;

	//�X�e�[�W��̓G�̐�
	int mEnemyCounter;

	//�X�e�[�W��̔��̐�
	int mBoxCounter;

	//���̐�
	int mKey;

	//���N���X
	Mist* mpMist;

	//�Q�[���f�[�^�N���X
	GameData* mpGameData;

	//�l�`�N���X
	std::vector<Doll*> mpDoll;

	//�l�`�̐�
	int mDollCounter;

	//�X�e�[�W�̈ړ��t���O
	bool mMoveFlag;

	//�X�e�[�W�̈ړ����W
	Int2 mMovePos;
public:
	Stage(int SelectNum,MODE mode, GameData* pGameData);		//�R���X�g���N�^
	~Stage();		//�f�X�g���N�^

	bool LoadCSV();	//�X�e�[�W�f�[�^�̓ǂݍ���
	void Initialize();	//������
	void Update();		//�X�V
	void Draw();		//�`��

	//�X�e�[�W�̈ړ�
	void MoveStage();

	//�Q�[���̏I���t���O
	RESULTSCENE GameEnd();

	//���̐��̊m�F
	bool KeyCheckFlag();

	//���Ԃ̎擾
	void SetTimerLimit(int num);

	void Finalize();	//�I������
};