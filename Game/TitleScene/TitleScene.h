/*
�^�C�g���V�[��
*/
#pragma once

#include "../IScene.h"
#include"../PlayScene/Mask/Mask.h"
#include"TitleLoad.h"
#include"../PlayScene/Mist/Mist.h"
#include"../Utility.h"

class TitleScene : public IScene
{
public:
	//�V�[��
	enum class STATE :int
	{
		START,
		OPTION,
		EXPLANATION,
		END,
	};
	//���
	enum class FLOW :int
	{
		FADE_IN,
		FADE_OUT,
		INITIALIZE,
		MAIN,
		FINALIZE,
	};

private:
	int mAudio;		//�����f�[�^
	int mPushAudio;		//�����f�[�^

	FLOW mFlow;		//���

	int mTexture;	//�摜�f�[�^

	SpriteData mSprite[3];	//�X�v���C�g

	float mAlpha;		//�����x

	STATE mState;		//�V�[��

	Int2 mPos[2];		//���W
		
	Color3 mColor3[3];	//�F

	int mTimer;			//�^�C�}�[
	
	Mask* mpMask;		//�}�X�N�N���X

	TitleLoad* mpTL;	//�w�i���[�v�N���X

	Mist* mpMist;		//���N���X
public:

	// �R���X�g���N�^
	TitleScene();

	// �f�X�g���N�^
	~TitleScene();

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

	//�L�����̃A�j���[�V����
	void CharaMotion();
};