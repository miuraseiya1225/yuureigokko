/*
���S�V�[��
*/
#pragma once

#include "../IScene.h"
#include"Blood/Blood.h"

class DieScene : public IScene
{
public:
	//���============================
	enum class FLOW :int
	{
		FADE_IN,
		FADE_OUT,
		INITIALIZE,
		MAIN,
		FINALIZE,
	};

	//�V�[���̑I��====================
	enum class MODE_SELECT :int
	{
		PLAY,
		TITLE,
		MAX,
	};
private:
	int mPushAudio;		//�����f�[�^

	Blood* mpBlood;		//���N���X�̃����o�|�C���^

	MODE_SELECT mModeSelect;	//�V�[���̑I��

	Color3 mColor3[2];			//�F�\����

	FLOW mFlow;		//���

	SpriteData mSprite;		//�X�v���C�g

	int mTexture;	//�摜�f�[�^
public:

	// �R���X�g���N�^
	DieScene();

	// �f�X�g���N�^
	~DieScene();

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