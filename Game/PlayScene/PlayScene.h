/*
�v���C�V�[��
*/
#pragma once

#include "../IScene.h"

#include"Stage/Stage.h"

//�O���錾
class GameData;

class PlayScene : public IScene
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

	//���̃V�[��
	enum class NEXT :int
	{
		TIMEOVER,
		DIE,
		GOAL,
	};
private:
	FLOW mFlow;		//���
	NEXT mNext;		//���̃V�[��
	Stage* mpStage;		//�X�e�[�W�N���X

	GameData* mpGameData;		//�Q�[���f�[�^

	int mAudio;		//�����f�[�^
public:

	// �R���X�g���N�^
	PlayScene(GameData* pGameData);

	// �f�X�g���N�^
	~PlayScene();

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