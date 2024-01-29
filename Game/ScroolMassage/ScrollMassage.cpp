/*
�@�N���X�F���b�Z�[�W���O�N���X
  �쐬�ҁF�O�Y����
  �쐬���F�P�Q/�Q�P�@�@�@�@
*/
#include "ScrollMassage.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
ScrollMassage::ScrollMassage()
	:mMassage{}
	,mPos{}
	,mColor{}
	,mMassageSize{}
	,mMassageVel{}
	,mMassageLine{}
	,mTimer{0}
	,mMassageNum{}
	,mType{0}
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
ScrollMassage::~ScrollMassage()
{
}

//Initialize��
//============================================================================================================
//    �����F���b�Z�[�W�@�A�@�`��ʒu�@�A�@���b�Z�[�W�̃T�C�Y�@�A�@���b�Z�[�W�𗬂�����	�A�@���s���镶���� �C�@Type(0�F�A���t�@�x�b�g�@�P�F���{��)���P�ł���
//============================================================================================================
void ScrollMassage::SetMessage(const std::string massage, Int2 pos2, Color3 color3,const int massagesize, const int massageVel, const int massageline, int Type)
{
	mMassage = massage;
	mPos = pos2;
	mColor = color3;
	mMassageSize = massagesize;
	mMassageVel = massageVel;
	mMassageLine = massageline;
	mType = Type;
}

/*--------------------------------------------------
���b�Z�[�W�𗬂�
--------------------------------------------------*/
bool ScrollMassage::DrawScrollMassage()
{
	
	int posx = mPos.mX;
	int posy = mPos.mY;
	
	int defaultSize = GetFontSize();

	SetFontSize(mMassageSize);

	for (int i = 0; i < mMassageNum; i++)
	{
		if (mType == 0)
		{
			DrawFormatString(posx, posy, GetColor(mColor.mRed, mColor.mGreen, mColor.mBlue), "%c", mMassage[i]);
			posx += mMassageSize / 2;
		}

		if (mType == 1)
		{
			if (i % 2 == 0)
			{
				DrawFormatString(posx, posy, GetColor(mColor.mRed, mColor.mGreen, mColor.mBlue), "%c%c", mMassage[i], mMassage[i + 1]);
				posx += mMassageSize;
			}
		}

		if (i % mMassageLine == 0 && i > 0)
		{
			posx = mPos.mX;
			posy += mMassageSize;
		}
	}
	
	SetFontSize(defaultSize);

	++mTimer %= mMassageVel;

	if (mTimer == 0)
		mMassageNum++;

	int size = mMassage.size();
	if (mMassageNum >=size)
	{
		mMassageNum = mMassage.size();
		return true;
	}
	return false;
}

/*--------------------------------------------------
�S�̂�`�悷��
--------------------------------------------------*/
void ScrollMassage::DrawMassageAll()
{
	mMassageNum = mMassage.size();
}

/*--------------------------------------------------
���Z�b�g
--------------------------------------------------*/
void ScrollMassage::Reset()
{
	mTimer = 0;
	mMassageNum = 0;
}

