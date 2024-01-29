/*
�@�N���X�F�l�`
  �쐬�ҁF�O�Y����
  �쐬���F�P/16�@�@
*/
#pragma once
#include"../../Utility.h"

//�O���錾
class Player;

class Doll
{
public:
	//����
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};
private:
	SpriteData mSprite;		//�X�v���C�g
	int mTexture;		//�摜�f�[�^
	Int2 mPos;		//���W
	Int2 mBoadPos;		//�X�e�[�W��̍��W
	bool mPickFlag;		//�l�`���E������

	bool mSoundFlag;	//���ʉ���炵����
	int mAudio;		//�����f�[�^
public:
	Doll(int x, int y);		//�R���X�g���N�^
	~Doll();		//�f�X�g���N�^

	void Initialize();		//������
	void Update(Player* pPlayer);		//�X�V
	const void Draw();	//�`��

	//���W�̎擾
	const Int2 GetPos() { return mBoadPos; };

	//�l�`���E��
	void Pick() { mPickFlag = true; };

	//�X�e�[�W�����������̏���
	bool StageMove(MOVE move);
};