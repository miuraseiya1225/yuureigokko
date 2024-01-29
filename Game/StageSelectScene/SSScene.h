#pragma once
/*
�@�N���X�F�X�e�[�W�I���V�[��
  �쐬�ҁF�O�Y����
  �쐬���F�P2/15�@�@�@
*/
#include "../IScene.h"
#include"../Utility.h"
#include"EnemyNum.h"

//�O���錾
class GameData;

class SelectScene : public IScene
{
public:
	//���
	enum class FLOW :int
	{
		FADE_IN,
		FADE_OUT,
		INITIALIZE,
		MAIN,
		FINALIZE,
	};

	//�X�e�[�W
	enum class STATE :int
	{
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE4,
		STAGE5,
		STAGE_NUM,

		FINALMAP,

	};

	//���
	enum class DISPLAY :int
	{
		ENEMY_NUM,
		RANK,
		FINALMAP,
	};
private:
	int mAudio;		//�����f�[�^
	int mPushAudio;		//�����f�[�^

	int mTexture;		//�摜�f�[�^

	SpriteData mSprite;		//�X�v���C�g

	GameData* mpGameData;		//�Q�[���f�[�^

	EnemyNum* mpEN;				//�G�̐��N���X

	FLOW mFlow;				//���
		
	STATE mState;			//�X�e�[�W�؂�ւ��p

	Color3 mColor[static_cast<int>( STATE::STAGE_NUM)];		//�F

	Int2 mPos;				//���W

	DISPLAY mDisplay;		//��ʂ̕\���ؑ֗p

	bool mFinalStageFlag;	//�ŏI�X�e�[�W�ɒ��߂邩
public:

	// �R���X�g���N�^
	SelectScene(GameData* pGameData);

	// �f�X�g���N�^
	~SelectScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

	//���Z�b�g
	void Reset();
};