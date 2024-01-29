#pragma once
/*
�@�N���X�FExplanation:�����N���X�@���
  �쐬�ҁF�O�Y����
  �쐬���F�P2/2�@�@�@�@
*/
#include"../../Utility.h"
#include"../../PlayScene/Stage/Stage.h"
#include"../../ScroolMassage/ScrollMassage.h"

//�O���錾
class GameData;

//���b�Z�[�W�\����
struct Message
{
	std::string mMessage;		//���b�Z�[�W	
	Int2 mPos;					//���W
	Color3 mColor;				//�F
	int mSize;					//�傫��
	int mVel;					//�������x
	int mLine;					//���s
	int mType;					//�^�C�v
};

class Explanation
{
public:
	//�`���[�g���A��
	enum class THUTRIAL :int
	{
		BOX,
		ENEMY,
		STAGE,

		NONE,
	};
protected:
	std::vector<Message> mMessage;		//���b�Z�[�W�\����

	int mMessageNum;					//���b�Z�[�W�̐�

	ScrollMassage* mpSM;				//�X�N���[�����b�Z�[�W�N���X

	SpriteData mSprite;					//�X�v���C�g

	Stage* mpStage;						//�X�e�[�W�N���X

	bool mPlayFlag;						//�v���C�ł��邩

	int mCounter;						//�J�E���^�[

	GameData* mpGameData;				//�Q�[���f�[�^
public:
	Explanation();					//�R���X�g���N�^
	virtual ~Explanation();			//�f�X�g���N�^

	bool LoadCSV(int low,int high);	//���b�Z�[�W�pCSV�t�@�C���̓ǂݍ���
	virtual void Initialize()=0;		//������
	virtual void Update()=0;			//�X�V
	virtual void Draw()=0;			//�`��

	virtual THUTRIAL FinalFlag()=0;	//�I���t���O

	void Finalize();				//�I������
};