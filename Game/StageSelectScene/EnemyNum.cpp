/*
�@�N���X�F�G�̐�
  �쐬�ҁF�O�Y����
  �쐬���F�P/13�@�@�@
*/
#include<fstream>
#include<sstream>
#include "EnemyNum.h"
#include"../Resource/Resource.h"

//�`��p
static const int SPACE_NUM = 232;
static const int SPACE_NUM2 = 28;

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
EnemyNum::EnemyNum()
{
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
EnemyNum::~EnemyNum()
{
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void EnemyNum::Initialize()
{
	//���\�[�X�}�l�[�W���[�̃C���X�^���X���擾����
	ResourceManager* Resource = ResourceManager::GetInstance();
	//�摜�����\�[�X�}�l�[�W���[�ɓo�^���ĉ摜�n���h�����擾����
	mTexture = Resource->LoadTexture(eTEXTURE::ENEMY_ALL, "EnemyAll.png");

	//�摜�̐ݒ�===========================================================
	mSprite[0].SetTexture(mTexture);
	mSprite[0].src.x = 256;
	mSprite[0].src.y = 0;
	mSprite[0].size.x = 64;
	mSprite[0].size.y = 64;
	mSprite[0].scale.x = 1.5f;
	mSprite[0].scale.y = 1.5f;

	mSprite[1].SetTexture(mTexture);
	mSprite[1].src.x = 64;
	mSprite[1].src.y = 64;
	mSprite[1].size.x = 64;
	mSprite[1].size.y = 64;
	mSprite[1].scale.x = 1.5f;
	mSprite[1].scale.y = 1.5f;

	mSprite[2].SetTexture(mTexture);
	mSprite[2].src.x = 64;
	mSprite[2].src.y = 128;
	mSprite[2].size.x = 64;
	mSprite[2].size.y = 64;
	mSprite[2].scale.x = 1.5f;
	mSprite[2].scale.y = 1.5f;

	mSprite[3].SetTexture(mTexture);
	mSprite[3].src.x = 64;
	mSprite[3].src.y = 192;
	mSprite[3].size.x = 64;
	mSprite[3].size.y = 64;
	mSprite[3].scale.x = 1.5f;
	mSprite[3].scale.y = 1.5f;

	mSprite[4].SetTexture(mTexture);
	mSprite[4].src.x = 64;
	mSprite[4].src.y = 0;
	mSprite[4].size.x = 64;
	mSprite[4].size.y = 64;
	mSprite[4].scale.x = 1.5f;
	mSprite[4].scale.y = 1.5f;

	mSprite[5].SetTexture(mTexture);
	mSprite[5].src.x = 384;
	mSprite[5].src.y = 0;
	mSprite[5].size.x = 64;
	mSprite[5].size.y = 64;
	mSprite[5].scale.x = 1.5f;
	mSprite[5].scale.y = 1.5f;
	//=============================================================--

	//�X�e�[�W���Ƃ̓G�̐��擾
	for (int i = 0; i < 10; i++)
	{
		LoadCSV(3 + i);
		mEnemyTypeNum[i] = GetEnemyNum();
	}

}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void EnemyNum::Draw(int low, int high)
{
	//�G�̃^�C�v���Ƃɕ����ēG�̐���`��===================================================
	for (int i = low; i < high; i++)
	{
		int numx =(SCREEN_CENTER_X - 450);
		int numy =((SCREEN_CENTER_Y - 300) + i * 120);

		int defaultSize = GetFontSize();

		SetFontSize(80);

		if (mEnemyTypeNum[i].mChasel2Num != 0)
		{
			numx += SPACE_NUM;
			mSprite[2].pos.x = static_cast<float>(numx);
			mSprite[2].pos.y = static_cast<float>(numy + 40);
			mSprite[2].Draw();

			DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[i].mChasel2Num);
		}
		if (mEnemyTypeNum[i].mHandNum != 0)
		{
			numx += SPACE_NUM;
			mSprite[3].pos.x = static_cast<float>(numx);
			mSprite[3].pos.y = static_cast<float>(numy + 40);
			mSprite[3].Draw();

			DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[i].mHandNum);
		}
		if (mEnemyTypeNum[i].mChasel1Num != 0)
		{
			numx += SPACE_NUM;
			mSprite[1].pos.x = static_cast<float>(numx);
			mSprite[1].pos.y = static_cast<float>(numy + 40);
			mSprite[1].Draw();

			DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[i].mChasel1Num);
		}
		if (mEnemyTypeNum[i].mNormalLightNum != 0)
		{
			numx += SPACE_NUM;
			mSprite[4].pos.x = static_cast<float>(numx);
			mSprite[4].pos.y = static_cast<float>(numy + 40);
			mSprite[4].Draw();

			DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[i].mNormalLightNum);
		}
		if (mEnemyTypeNum[i].mNormalNum != 0)
		{
			numx += SPACE_NUM;
			mSprite[0].pos.x = static_cast<float>(numx);
			mSprite[0].pos.y = static_cast<float>(numy + 40);
			mSprite[0].Draw();

			DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[i].mNormalNum);
		}
		SetFontSize(defaultSize);
	}
	//======================================================================================================
}

/*--------------------------------------------------
�ŏI�X�e�[�W�p�̕`��
--------------------------------------------------*/
void EnemyNum::FinalStageDraw()
{
	int numx = (SCREEN_CENTER_X - 700);
	int numy = ((SCREEN_CENTER_Y - 50));

	int defaultSize = GetFontSize();

	SetFontSize(80);

	if (mEnemyTypeNum[5].mChasel2Num != 0)
	{
		numx += SPACE_NUM;
		mSprite[2].pos.x = static_cast<float>(numx);
		mSprite[2].pos.y = static_cast<float>(numy + 40);
		mSprite[2].Draw();

		DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[5].mChasel2Num);
	}
	if (mEnemyTypeNum[5].mHandNum != 0)
	{
		numx += SPACE_NUM;
		mSprite[3].pos.x = static_cast<float>(numx);
		mSprite[3].pos.y = static_cast<float>(numy + 40);
		mSprite[3].Draw();

		DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[5].mHandNum);
	}
	if (mEnemyTypeNum[5].mChasel1Num != 0)
	{
		numx += SPACE_NUM;
		mSprite[1].pos.x = static_cast<float>(numx);
		mSprite[1].pos.y = static_cast<float>(numy + 40);
		mSprite[1].Draw();

		DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[5].mChasel1Num);
	}
	if (mEnemyTypeNum[5].mNormalLightNum != 0)
	{
		numx += SPACE_NUM;
		mSprite[4].pos.x = static_cast<float>(numx);
		mSprite[4].pos.y = static_cast<float>(numy + 40);
		mSprite[4].Draw();

		DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[5].mNormalLightNum);
	}
	if (mEnemyTypeNum[5].mNormalNum != 0)
	{
		numx += SPACE_NUM;
		mSprite[0].pos.x = static_cast<float>(numx);
		mSprite[0].pos.y = static_cast<float>(numy + 40);
		mSprite[0].Draw();

		DrawFormatString(numx + SPACE_NUM2, numy, GetColor(255, 255, 255), "�~%d", mEnemyTypeNum[5].mNormalNum);
	}

	SetFontSize(defaultSize);

}

/*--------------------------------------------------
CSV�t�@�C���̓ǂݍ���
--------------------------------------------------*/
bool EnemyNum::LoadCSV(int src)
{
	std::ifstream ifs("Resources/Stage/Book1.csv");

	//�t�@�C���ǂݍ��݂Ɏ��s���Ă����玸�s�̒l��Ԃ�
	if (ifs.fail())
	{
		return false;
	}

	//�s�̕������ۑ�����ϐ�
	std::string line;

	int nX = 0;
	int nY = 0;

	//�s�̓ǂݍ���
	for (int y = 0; std::getline(ifs, line); y++)
	{
		//stream�ɍs�̕���������
		std::istringstream iss(line);

		//�J���}��؂�̕����󂯎��p
		std::string buf;

		if (y < src * STAGE_SIZEY)
			continue;
		if (y > STAGE_SIZEY + (src * STAGE_SIZEY))
			break;

		mStage.resize(nY + 1);

		//�s�̏����J���}��؂�Ŏ󂯎��
		for (int x = 0; std::getline(iss, buf, ','); x++)
		{
			mStage[nY].resize(nX + 1);
			//������int�ɕϊ�
			int num = stoi(buf);

			//�X�e�[�W�z��Ƀ^�C���ԍ�����
			mStage[nY][nX] = num;
			nX++;
		}
		nX = 0;
		nY++;
	}

	//�t�@�C�������
	ifs.close();

	//����
	return true;
}

/*--------------------------------------------------
�G�̐��擾
--------------------------------------------------*/
EnemyNum::EnemyTypeNum EnemyNum::GetEnemyNum()
{
	EnemyTypeNum mNum;
	int ny = mStage.size();
	for (int y = 0; y < ny; y++)
	{
		int nx = mStage[y].size();
		for (int x = 0; x < nx; x++)
		{
			switch (mStage[y][x])
			{
				case 6:
				{
					mNum.mKey++;
					break;
				}
				case 7:
				{
					mNum.mNormalNum++;
					break;
				}
				case 8:
				{
					mNum.mChasel1Num++;
					break;
				}
				case 9:
				{
					mNum.mChasel2Num++;
					break;
				}
				case 10:
				{
					mNum.mHandNum++;
					break;
				}
				case 11:
				{
					mNum.mNormalLightNum++;
					break;
				}
				default:
					break;
			}
		}
	}
	return mNum;
}
