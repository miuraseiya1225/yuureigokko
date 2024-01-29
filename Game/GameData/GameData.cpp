/*
　クラス：ゲームデータ
  作成者：三浦聖矢
  作成日：１2/15　　　　
*/
#include"GameData.h"
#include<fstream>

#include<iostream>

//================================================
//		コンストラクタ
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
//		デストラクタ
//================================================
GameData::~GameData()
{

}

//================================================
//		ランクの保存
//================================================
void GameData::SetRank(STAGE stage, RANK rank)
{
	//ステージごとに保存する========================================
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
//		ランクデータの読み込み
//================================================
bool GameData::InputData()
{
	//外部ファイル参照
	std::ifstream ifs("Resources/Stage/RankData.txt");

	//ファイル読み込みに失敗していたら失敗の値を返す
	if (ifs.fail())
	{
		return false;
	}

	//行の文字列を保存する変数
	std::string line;

	//行の読み込み
	for (int i = 0; std::getline(ifs, line); i++)
	{
		//文字をintに変換
		int num = stoi(line);

		mRank[i] = static_cast<GameData::RANK>(num);
	}

	//ファイルを閉じる
	ifs.close();

	//成功
	return true;
}

//================================================
//		ランクデータの書き込み
//================================================
bool GameData::OutputData()
{
	std::fstream out;

	//外部ファイル参照
	out.open("Resources/Stage/RankData.txt", std::ios::out | std::ios::trunc);

	//ファイル読み込みに失敗していたら失敗の値を返す
	if (out.fail())
	{
		return false;
	}

	//書き込み
	for (int i = 0; i < static_cast<int>( mRank.size()); i++)
		out << static_cast<int>(mRank[i]) << std::endl;
	
	//ファイルを閉じる
	out.close();

	return true;
}
