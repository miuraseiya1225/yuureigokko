/*
�@�N���X�F�}�X�N�N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P2/30�@�@�@�@
*/
#include"Mask.h"
#include"../../Resource/Resource.h"

//�C���X�^���X����
//Initialize��Draw�͂����ʂ�
//Update�͂���Ȃ�
//�g���Ƃ��͂܂�ResetMask���ɏ�������SetAlpha(���W�A�}�X�N�͈̔́i�l���������قǍL���Ȃ�j)����������

//================================================
//			�R���X�g���N�^
//================================================
Mask::Mask() :
	mAlpha{ 1.0f }
	, mAlpha_Frequency{ 0.0f }
	, mAlphaSprite1{}
	, mAlphaSprite2{}
	, mAlphaSprite3{}
	, mAlphaSprite4{}
{
}

//================================================
//			�R���X�g���N�^
//================================================
Mask::~Mask()
{
}

//================================================
//			������
//================================================
void Mask::Initialize()
{
	//�摜�A�h���X�擾
	ResourceManager* prm = ResourceManager::GetInstance();
	mTexture = prm->LoadTexture(eTEXTURE::SCREEN_ALPHA, "BlackScreen.png");

	//�}�X�N�^�C���̐ݒ�========================================================
	int s = (SCREEN_CENTER_Y) / BLACK_SIZE;
	mAlphaSprite1.resize(s);

	int h = ((SCREEN_RIGHT) / 2) / BLACK_SIZE;
	for (int i = 0; i < s; i++)
		mAlphaSprite1[i].resize(h);

	//�������=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite1[y][x].SetTexture(mTexture);
			mAlphaSprite1[y][x].src.x = 0;
			mAlphaSprite1[y][x].src.y = 0;
			mAlphaSprite1[y][x].size.x = BLACK_SIZE;
			mAlphaSprite1[y][x].size.y = BLACK_SIZE;

			mAlphaSprite1[y][x].pos.x = 0;
			mAlphaSprite1[y][x].pos.y = 0;
			mAlphaSprite1[y][x].alpha = mAlpha;
		}
	}
	s = (SCREEN_CENTER_Y) / BLACK_SIZE;
	mAlphaSprite2.resize(s);

	h = (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1;
	for (int i = 0; i < s; i++)
		mAlphaSprite2[i].resize(h);

	//�������=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite2[y][x].SetTexture(mTexture);
			mAlphaSprite2[y][x].src.x = 0;
			mAlphaSprite2[y][x].src.y = 0;
			mAlphaSprite2[y][x].size.x = BLACK_SIZE;
			mAlphaSprite2[y][x].size.y = BLACK_SIZE;

			mAlphaSprite2[y][x].pos.x = 0;
			mAlphaSprite2[y][x].pos.y = 0;
			mAlphaSprite2[y][x].alpha = mAlpha;
		}
	}
	s = ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1;
	mAlphaSprite3.resize(s);

	h = (((SCREEN_RIGHT) / 2) / BLACK_SIZE);
	for (int i = 0; i < s; i++)
		mAlphaSprite3[i].resize(h);

	//�������=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite3[y][x].SetTexture(mTexture);
			mAlphaSprite3[y][x].src.x = 0;
			mAlphaSprite3[y][x].src.y = 0;
			mAlphaSprite3[y][x].size.x = BLACK_SIZE;
			mAlphaSprite3[y][x].size.y = BLACK_SIZE;

			mAlphaSprite3[y][x].pos.x = 0;
			mAlphaSprite3[y][x].pos.y = 0;
			mAlphaSprite3[y][x].alpha = mAlpha;
		}
	}
	s = ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1;
	mAlphaSprite4.resize(s);

	h = (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1;
	for (int i = 0; i < s; i++)
		mAlphaSprite4[i].resize(h);

	//�������=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite4[y][x].SetTexture(mTexture);
			mAlphaSprite4[y][x].src.x = 0;
			mAlphaSprite4[y][x].src.y = 0;
			mAlphaSprite4[y][x].size.x = BLACK_SIZE;
			mAlphaSprite4[y][x].size.y = BLACK_SIZE;

			mAlphaSprite4[y][x].pos.x = 0;
			mAlphaSprite4[y][x].pos.y = 0;
			mAlphaSprite4[y][x].alpha = mAlpha;
		}
	}
	//==================================================================================
}


//================================================
//			�`��
//			�O�����̒藝���g���ăv���[���[�ƃ^�C���������̋��������߁A�����x��ς���
//================================================
void Mask::Draw()
{
	//���に��������������������������������������������������������������������
	mPos.mX = -8;
	mPos.mY = -8;

	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		mPos.mX = -8;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < ((SCREEN_RIGHT) / 2) / BLACK_SIZE; x++)
		{
			mPos.mX += BLACK_SIZE;

			if (y + 1 == (SCREEN_CENTER_Y) / BLACK_SIZE)
				mPos2.mX = mPos.mX;

			mAlphaSprite1[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite1[y][x].pos.y = static_cast<float>(mPos.mY);

			if (x != ((SCREEN_RIGHT) / 2) / BLACK_SIZE)
				mAlphaSprite1[y][x].Draw();

		}
	}
	//���な������������������������������������������������������������������������

	//==============================================================================

	//�E�に��������������������������������������������������������������������
	mPos.mX = mPos2.mX;
	mPos.mY = -8;

	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		mPos.mX = mPos2.mX;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			mPos.mX += BLACK_SIZE;

			mAlphaSprite2[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite2[y][x].pos.y = static_cast<float>(mPos.mY);

			mAlphaSprite2[y][x].Draw();
		}
		if (y + 1 == (SCREEN_CENTER_Y) / BLACK_SIZE)
			mPos2.mY = mPos.mY;
	}
	//�E�な������������������������������������������������������������������������

	//=================================================================================

	//��������������������������������������������������������������������������

	mPos.mX = -8;
	mPos.mY = mPos2.mY;

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		mPos.mX = -8;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE); x++)
		{
			mPos.mX += BLACK_SIZE;

			if (y + 1 == (SCREEN_CENTER_Y) / BLACK_SIZE)
				mPos2.mX = mPos.mX;

			mAlphaSprite3[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite3[y][x].pos.y = static_cast<float>(mPos.mY);

			mAlphaSprite3[y][x].Draw();
		}

	}
	//������������������������������������������������������������������������������

	//============================================================================

	//�E������������������������������������������������������������������������
	mPos.mX = mPos2.mX;
	mPos.mY = mPos2.mY;

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		mPos.mX = mPos2.mX;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			mPos.mX += BLACK_SIZE;

			mAlphaSprite4[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite4[y][x].pos.y = static_cast<float>(mPos.mY);

			mAlphaSprite4[y][x].Draw();
		}
	}
	//�E����������������������������������������������������������������������������
}


//==============================================================================
// �����F��_�̍��W�@�}�X�N�̑傫��(�l���������قǑ傫���Ȃ�)
//==============================================================================
void Mask::SetAlpha(Int2 BasePos, float Alpha_Frequency)
{
	if (BasePos.mX == 0 || BasePos.mY == 0)
		return;

	mAlpha_Frequency = Alpha_Frequency;

	mAlpha = 0.0f;
	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		for (int x = 0; x < ((SCREEN_RIGHT) / 2) / BLACK_SIZE; x++)
		{
			//�����̋������v�Z=========================
			int DisX = BasePos.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================
			//����牓���قǉ�ʂ��Â�����
			mAlpha = (mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite1[y][x].alpha = mAlpha + 0.05f;
		}
	}
	//���な������������������������������������������������������������������������

	//==============================================================================

	//�E�に��������������������������������������������������������������������
	mAlpha = 0.0f;

	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			//�����̋������v�Z=========================
			int DisX = BasePos.mX - mPos2.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================

			//����牓���قǉ�ʂ��Â�����
			mAlpha =(mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite2[y][x].alpha = mAlpha + 0.05f;
		}
	}
	//�E�な������������������������������������������������������������������������

	//=================================================================================

	//��������������������������������������������������������������������������
	mAlpha = 0.0f;

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE); x++)
		{
			//�����̋������v�Z=========================
			int DisX = BasePos.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - mPos2.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================

			//����牓���قǉ�ʂ��Â�����
			mAlpha = (mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite3[y][x].alpha = mAlpha + 0.05f;
		}

	}
	//������������������������������������������������������������������������������

	//============================================================================

	//�E������������������������������������������������������������������������
	mAlpha = 0.0f;

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			//�����̋������v�Z=========================
			int DisX = BasePos.mX - mPos2.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - mPos2.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================

			//����牓���قǉ�ʂ��Â�����
			mAlpha =(mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite4[y][x].alpha = mAlpha + 0.05f;
		}
	}
	//�E����������������������������������������������������������������������������
}


//================================================
//			�}�X�N�̏�����
//================================================
void Mask::ResetMask()
{
	mAlpha = 1.0f;
	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < ((SCREEN_RIGHT) / 2) / BLACK_SIZE; x++)
			mAlphaSprite1[y][x].alpha = mAlpha + 0.05f;
	//���な������������������������������������������������������������������������

	//==============================================================================

	//�E�に��������������������������������������������������������������������
	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
			mAlphaSprite2[y][x].alpha = mAlpha + 0.05f;
	//�E�な������������������������������������������������������������������������

	//=================================================================================

	//��������������������������������������������������������������������������

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE); x++)
			mAlphaSprite3[y][x].alpha = mAlpha + 0.05f;
	//������������������������������������������������������������������������������

	//============================================================================

	//�E������������������������������������������������������������������������

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
			mAlphaSprite4[y][x].alpha = mAlpha + 0.05f;

	//�E����������������������������������������������������������������������������
}

//================================================
//			�I������
//================================================
void Mask::Finalize()
{
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < ((SCREEN_RIGHT - 128) / 2) / BLACK_SIZE; x++)
			mAlphaSprite1[y][x].Finalize();
	//���な������������������������������������������������������������������������

	//==============================================================================

	//�E�に��������������������������������������������������������������������
	//��ʂ��Â�����
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < ((SCREEN_RIGHT - 96) / 2) + 1 / BLACK_SIZE; x++)
			mAlphaSprite2[y][x].Finalize();
	//�E�な������������������������������������������������������������������������

	//=================================================================================

	//��������������������������������������������������������������������������

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < (((SCREEN_RIGHT - 96) / 2) / BLACK_SIZE) - 2; x++)
			mAlphaSprite3[y][x].Finalize();
	//������������������������������������������������������������������������������

	//============================================================================

	//�E������������������������������������������������������������������������

	//��ʂ��Â�����
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < ((SCREEN_RIGHT - 96) / 2) + 1 / BLACK_SIZE; x++)
			mAlphaSprite4[y][x].Finalize();

	//�E����������������������������������������������������������������������������
}
