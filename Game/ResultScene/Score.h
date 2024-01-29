/*
�@�N���X�F�Q�[���̃X�R�A
  �쐬�ҁF�O�Y����
  �쐬���F�P/14�@�@�@
*/
#pragma once

//�O���錾
class GameData;

class Score
{	
private:
	int mDollAudio;			//�����f�[�^
	int mScoreAudio;			//�����f�[�^

	SpriteData mSprite;		//�X�v���C�g

	int mTexture;		//�摜�f�[�^

	int mTimer;		//�^�C�}�[

	bool mFlag;		//�t���O

	GameData* mpGameData;		//�Q�[���f�[�^

	bool mNextFlag;		//�^�C�g���ɖ߂��t���O
public:
	Score(GameData* pGameData);		//�R���X�g���N�^
	~Score();			//�f�X�g���N�^

	void Initialize();		//������
	void Update();			//�X�V
	void Draw();			//�`��

	const bool NextFlag() { return mNextFlag; };		//�^�C�g���V�[���ɖ߂�邩
};