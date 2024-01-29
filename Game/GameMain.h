//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���S�̂Ɋւ���w�b�_�t�@�C��
//!
//! @date   ���t
//!
//! @author ����Җ�
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

// �萔�̒�` ==============================================================
// <�V�X�e��> ----------------------------------------------------------
#define GAME_TITLE "�H�삲����"        // �Q�[���^�C�g��


// <���> --------------------------------------------------------------
#define SCREEN_WIDTH    (1280)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (704)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)

#define	FADE_TIME 0.5f

//�X�e�[�W�̑傫��
static const int STAGE_SIZEX = 64;
static const int STAGE_SIZEY = 32;

enum class GAME_SCENE : int
{
	NONE,

	TITLE,
	THUTRIAL,
	SELECT,
	PLAY,
	RESULT,
	DIE,
};

class IScene;

class GameData;
// �֐��̐錾 ==============================================================
// <�Q�[��> ------------------------------------------------------------


class GameMain
{
private:

	// �����Ƀ����o�𑝂₷

	// ���̃V�[���ԍ�
	GAME_SCENE mNextScene;

	// �V�[��
	IScene* mpScene;
	
	//�Q�[���f�[�^
	GameData* mpGameData;
public:
	
	// �R���X�g���N�^
	GameMain();

	// �f�X�g���N�^
	~GameMain();

	void InitializeGame();    // �Q�[���̏���������
	void UpdateGame();        // �Q�[���̍X�V����
	void RenderGame();        // �Q�[���̕`�揈��
	void FinalizeGame();      // �Q�[���̏I������

	bool EndFlag();
	// �V�[���֌W����

	// �V�[���̍쐬
	void CreateScene();

	// �V�[���̍폜
	void DeleteScene();
};