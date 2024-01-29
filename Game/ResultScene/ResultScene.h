/*
���U���g�V�[��
*/
#pragma once

#include "../IScene.h"
#include"Score.h"

//�O���錾
class GameData;

class ResultScene : public IScene
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

private:
	int mTexture;		//�摜�f�[�^

	SpriteData mSprite[2];		//�X�v���C�g

	FLOW mFlow;		//���

	GameData* mpGameData;		//�Q�[���f�[�^

	Score* mpScore;		//�X�R�A�N���X
public:

	// �R���X�g���N�^
	ResultScene(GameData* pGameData);

	// �f�X�g���N�^
	~ResultScene();

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