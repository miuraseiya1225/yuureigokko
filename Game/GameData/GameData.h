#pragma once
/*
　クラス：ゲームデータ
  作成者：三浦聖矢
  作成日：１2/15　　　　
*/
#include"../Utility.h"
class GameData
{
public:
	//クリアランク
	enum class RANK :int
	{
		NONE,
		C,
		B,
		A,
		S,

		RANK_NUM,
	};

	//ステージ
	enum class STAGE :int
	{
		THUTRIAL1,
		THUTRIAL2,
		THUTRIAL3,
		SELECT_1,
		SELECT_2,
		SELECT_3,
		SELECT_4,
		SELECT_5,
		FINALSTAGE,

		STAGE_NUM,
	};

	//制限時間
	static const int TIME = 3600;
	static const int FINALSTAGE_TIME = 10800;
private:
	STAGE mSelect;		//ステージ
	int mTimerLimit;	//制限時間
	int mDollNum;		//人形の数

	std::vector<RANK> mRank;
public:
	GameData();		//コンストラクタ
	~GameData();	//デストラクタ

	//ステージのセッター
	void SetStageSelect(STAGE select) { mSelect = select; };

	//ステージのゲッター
	const int GetStageSelect() { return static_cast<int>(mSelect); };

	//制限時間の減少と取得
	int SubTimerLimit() { mTimerLimit--; return mTimerLimit; };

	//制限時間の取得
	const int GetTimerLimit() { return mTimerLimit; };

	//ゲームデータのリセット=====================================
	void GameDataReset() {if(mSelect!=STAGE::FINALSTAGE)
								mTimerLimit = TIME;
							else
								mTimerLimit = FINALSTAGE_TIME;

							mDollNum = 0; };
	//==========================================================

	//人形の増加
	void AddDollNum() { mDollNum++; };

	//人形の数の取得
	const int GetDollNum() { return mDollNum; };

	//ランクデータの読み込み
	bool InputData();

	//ランクデータの書き込み
	bool OutputData();

	//ランクの保存
	void SetRank(STAGE stage, RANK rank);

	//ランクの取得
	void GetRank(RANK* rank, int num) { *rank = mRank[num]; };
};