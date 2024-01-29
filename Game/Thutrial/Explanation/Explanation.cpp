/*
�@�N���X�FExplanation:�����N���X�@���
  �쐬�ҁF�O�Y����
  �쐬���F�P2/2�@�@�@�@
*/
#include "Explanation.h"

#include<fstream>
#include<sstream>
#include<iostream>

/*--------------------------------------------------
�R���X�g���N�^
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
�f�X�g���N�^
--------------------------------------------------*/
Explanation::~Explanation()
{
}

/*--------------------------------------------------
���b�Z�[�W�pCSV�t�@�C���̓ǂݍ���
--------------------------------------------------*/
bool Explanation::LoadCSV(int low, int high)
{
	std::ifstream ifs("Resources/Stage/Text.csv");

	//�t�@�C���ǂݍ��݂Ɏ��s���Ă����玸�s�̒l��Ԃ�
	if (ifs.fail())
	{
		return false;
	}

	//�s�̕������ۑ�����ϐ�
	std::string line;

	int nY = 0;
	//�s�̓ǂݍ���
	for (int y = 0; std::getline(ifs, line); y++)
	{
		//stream�ɍs�̕���������
		std::istringstream iss(line);

		//�J���}��؂�̕����󂯎��p
		std::string buf;

		if (y < low)
			continue;

		if (y > high)
			break;

		mMessage.resize(nY + 1);

		//�s�̏����J���}��؂�Ŏ󂯎��
		for (int x = 0; std::getline(iss, buf, ','); x++)
		{
			//�X�e�[�W�z��Ƀ^�C���ԍ�����
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

	//�t�@�C�������
	ifs.close();

	//����
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
