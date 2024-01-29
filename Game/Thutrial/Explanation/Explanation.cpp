/*
　クラス：Explanation:説明クラス　基底
  作成者：三浦聖矢
  作成日：１2/2　　　　
*/
#include "Explanation.h"

#include<fstream>
#include<sstream>
#include<iostream>

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
Explanation::Explanation()
	:mMessage{}
	, mpSM{}
	, mSprite{}
	,mMessageNum{}
	,mPlayFlag{false}
	,mCounter{0}
{
	
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
Explanation::~Explanation()
{
}

/*--------------------------------------------------
メッセージ用CSVファイルの読み込み
--------------------------------------------------*/
bool Explanation::LoadCSV(int low, int high)
{
	std::ifstream ifs("Resources/Stage/Text.csv");

	//ファイル読み込みに失敗していたら失敗の値を返す
	if (ifs.fail())
	{
		return false;
	}

	//行の文字列を保存する変数
	std::string line;

	int nY = 0;
	//行の読み込み
	for (int y = 0; std::getline(ifs, line); y++)
	{
		//streamに行の文字を入れる
		std::istringstream iss(line);

		//カンマ区切りの文字受け取り用
		std::string buf;

		if (y < low)
			continue;

		if (y > high)
			break;

		mMessage.resize(nY + 1);

		//行の情報をカンマ区切りで受け取る
		for (int x = 0; std::getline(iss, buf, ','); x++)
		{
			//ステージ配列にタイル番号を代入
			switch (x)
			{
				case 0:
				{
					mMessage[nY].mMessage = buf;
					break;
				}
				case 1:
				{
					int num = stoi(buf);
					mMessage[nY].mPos.mX = num;
					break;
				}
				case 2:
				{
					int num = stoi(buf);
					mMessage[nY].mPos.mY = num;
					break;
				}
				case 3:
				{
					int num = stoi(buf);
					mMessage[nY].mColor.mRed = num;
					break;
				}
				case 4:
				{
					int num = stoi(buf);
					mMessage[nY].mColor.mGreen = num;
					break;
				}
				case 5:
				{
					int num = stoi(buf);
					mMessage[nY].mColor.mBlue = num;
					break;
				}
				case 6:
				{
					int num = stoi(buf);
					mMessage[nY].mSize = num;
					break;
				}
				case 7:
				{
					int num = stoi(buf);
					mMessage[nY].mVel = num;
					break;
				}
				case 8:
				{
					int num = stoi(buf);
					mMessage[nY].mLine = num;
					break;
				}
				case 9:
				{
					int num = stoi(buf);
					mMessage[nY].mType = num;
					break;
				}
				default:
					break;
			}
		}
		nY++;
	}

	//ファイルを閉じる
	ifs.close();

	//成功
	return true;
}

void Explanation::Finalize()
{
	mpStage->Finalize();

	delete mpStage;
	delete mpSM;

	mpStage = nullptr;
	mpSM = nullptr;
}
