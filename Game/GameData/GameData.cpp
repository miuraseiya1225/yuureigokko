/*
�@�N���X�F�Q�[���f�[�^
  �쐬�ҁF�O�Y����
  �쐬���F�P2/15�@�@�@�@
*/
#include"GameData.h"
#include<fstream>

#include<iostream>

//================================================
//		�R���X�g���N�^
//================================================
GameData::GameData():
	mSelect{GameData::STAGE::SELECT_2}
	,mTimerLimit{TIME}
	,mDollNum{}
{
	mRank.resize(static_cast<int> (GameData::STAGE::STAGE_NUM) - 3);

	for (int i = 0; i < static_cast<int>(mRank.size()); i++)
	{
		mRank[i] = GameData::RANK::NONE;
	}
}

//================================================
//		�f�X�g���N�^
//================================================
GameData::~GameData()
{

}

//================================================
//		�����N�̕ۑ�
//================================================
void GameData::SetRank(STAGE stage, RANK rank)
{
	//�X�e�[�W���Ƃɕۑ�����========================================
	switch (stage)
	{
		case GameData::STAGE::SELECT_1:
		{
			if (static_cast<int>(rank) > static_cast<int>(mRank[0]))
				mRank[0] = rank;
				break;
		}
		case GameData::STAGE::SELECT_2:
		{
			if (static_cast<int>(rank) > static_cast<int>(mRank[1]))
				mRank[1] = rank;
			break;
		}
		case GameData::STAGE::SELECT_3:
		{
			if (static_cast<int>(rank) > static_cast<int>(mRank[2]))
				mRank[2] = rank;
			break;
		}
		case GameData::STAGE::SELECT_4:
		{
			if (static_cast<int>(rank) > static_cast<int>(mRank[3]))
				mRank[3] = rank;
			break;
		}
		case GameData::STAGE::SELECT_5:
		{
			if (static_cast<int>(rank) > static_cast<int>(mRank[4]))
				mRank[4] = rank;
			break;
		}
		case GameData::STAGE::FINALSTAGE:
		{
			if (static_cast<int>(rank) > static_cast<int>(mRank[5]))
				mRank[5] = rank;
			break;
		}
		default:
			break;
	}
	//==================================================================-
}

//================================================
//		�����N�f�[�^�̓ǂݍ���
//================================================
bool GameData::InputData()
{
	//�O���t�@�C���Q��
	std::ifstream ifs("Resources/Stage/RankData.txt");

	//�t�@�C���ǂݍ��݂Ɏ��s���Ă����玸�s�̒l��Ԃ�
	if (ifs.fail())
	{
		return false;
	}

	//�s�̕������ۑ�����ϐ�
	std::string line;

	//�s�̓ǂݍ���
	for (int i = 0; std::getline(ifs, line); i++)
	{
		//������int�ɕϊ�
		int num = stoi(line);

		mRank[i] = static_cast<GameData::RANK>(num);
	}

	//�t�@�C�������
	ifs.close();

	//����
	return true;
}

//================================================
//		�����N�f�[�^�̏�������
//================================================
bool GameData::OutputData()
{
	std::fstream out;

	//�O���t�@�C���Q��
	out.open("Resources/Stage/RankData.txt", std::ios::out | std::ios::trunc);

	//�t�@�C���ǂݍ��݂Ɏ��s���Ă����玸�s�̒l��Ԃ�
	if (out.fail())
	{
		return false;
	}

	//��������
	for (int i = 0; i < static_cast<int>( mRank.size()); i++)
		out << static_cast<int>(mRank[i]) << std::endl;
	
	//�t�@�C�������
	out.close();

	return true;
}
