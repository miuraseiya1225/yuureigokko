/*
　クラス：メッセージログクラス
  作成者：三浦聖矢
  作成日：１２/２１　　　　
*/
#include "ScrollMassage.h"

/*--------------------------------------------------
コンストラクタ
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
デストラクタ
--------------------------------------------------*/
ScrollMassage::~ScrollMassage()
{
}

//Initializeで
//============================================================================================================
//    引数：メッセージ　、　描画位置　、　メッセージのサイズ　、　メッセージを流す速さ	、　改行する文字数 ，　Type(0：アルファベット　１：日本語)←１でいい
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
メッセージを流す
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
全体を描画する
--------------------------------------------------*/
void ScrollMassage::DrawMassageAll()
{
	mMassageNum = mMassage.size();
}

/*--------------------------------------------------
リセット
--------------------------------------------------*/
void ScrollMassage::Reset()
{
	mTimer = 0;
	mMassageNum = 0;
}

