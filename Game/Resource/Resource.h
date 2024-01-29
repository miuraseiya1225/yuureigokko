/*
���\�[�X�̊Ǘ��N���X
*/
#pragma once

#include<string>

//�e�N�X�`���̎��
enum class eTEXTURE :int
{
	MAP_TILE,
	CHARA,
	NORMAL,
	NORMALLIGHT,
	CHASEV1,
	CHASEV2,
	HAND,
	ENEMY_ALL,
	BOX,
	SCREEN_ALPHA,
	RED_SCREEN,
	BLOOD,
	MIST,
	DOLL,
	DOLL_MOLD,
	TITLE,
	TITLE_LOAD,
	SELECT_BACK,
	RESULT_LOGO,
	RESULT_BACK,
	GAMEOVER_LOGO,

	MAX,
};

//�����̎��
enum class eAUDIO :int
{
	TITLE,
	DOLL_PULL,
	SCORE,
	WALK,
	HEART,
	CREAM,
	BLOOD,
	ATTACK,
	NORMAL,
	BLACK,
	CHASEV1,
	CHASEV2,
	HAND,
	ROOM,
	GETKEY,
	OPENDOOR,
	OPENBOX,
	MAX,
};

class ResourceManager
{
public:
	
	//�ǂ�����ł��A�N�Z�X�ł���悤�ɂ��邽�߂̏���
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;

		return &instance;
	}

private:

	//�e�N�X�`���̔z��
	int mTextures[static_cast<int>(eTEXTURE::MAX)];

	//�����̔z��
	int mAudio[static_cast<int>(eAUDIO::MAX)];
public:
	//�R���X�g���N�^
	ResourceManager();

	//�f�X�g���N�^
	~ResourceManager();

	//�e�N�X�`��=====================================
	//�e�N�X�`���̓ǂݍ���
	int LoadTexture(eTEXTURE textureId, std::string path);

	//�e�N�X�`���̎擾
	int GetTexture(eTEXTURE textureId);

	//�摜�̍폜
	void DeleteTexture(eTEXTURE textureId);

	//�S�摜�̍폜
	void DeleteTextureALL();
	//==================================================

	//����==============================================
	//�����̓ǂݍ���
	int LoadAudio(eAUDIO audioId, std::string path);

	//�����̎擾
	int GetAudio(eAUDIO audioId);

	//�����̍폜
	void DeleteAudio(eAUDIO audioId);

	//�����̍폜
	void DeleteAudioALL();
	//==================================================
};