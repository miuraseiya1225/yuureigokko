#pragma once
#include "../IScene.h"
#include"Explanation/Explanation.h"

//�O���錾
class GameData;

class ThutrialScene : public IScene
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
	Explanation::THUTRIAL mState;	//�`���[�g���A���p

	GameData* mpGameData;			//�Q�[���f�[�^
	FLOW mFlow;						//���

	Explanation* mpExplanation;		//�����N���X	
public:

	// �R���X�g���N�^
	ThutrialScene(GameData* pGameData);

	// �f�X�g���N�^
	~ThutrialScene();

	// ������
	void Initialize() override;

	// �X�V
	GAME_SCENE Update() override;

	// �`��
	void Draw() override;

	// �I������
	void Finalize() override;

	//���̃V�[��
	void Next();

	//���Z�b�g
	void Reset();
};