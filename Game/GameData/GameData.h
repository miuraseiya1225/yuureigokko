#pragma once
/*
�@�N���X�F�Q�[���f�[�^
  �쐬�ҁF�O�Y����
  �쐬���F�P2/15�@�@�@�@
*/
#include"../Utility.h"
class GameData
{
public:
	//�N���A�����N
	enum class RANK :int
	{
		NONE,
		C,
		B,
		A,
		S,

		RANK_NUM,
	};

	//�X�e�[�W
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

	//��������
	static const int TIME = 3600;
	static const int FINALSTAGE_TIME = 10800;
private:
	STAGE mSelect;		//�X�e�[�W
	int mTimerLimit;	//��������
	int mDollNum;		//�l�`�̐�

	std::vector<RANK> mRank;
public:
	GameData();		//�R���X�g���N�^
	~GameData();	//�f�X�g���N�^

	//�X�e�[�W�̃Z�b�^�[
	void SetStageSelect(STAGE select) { mSelect = select; };

	//�X�e�[�W�̃Q�b�^�[
	const int GetStageSelect() { return static_cast<int>(mSelect); };

	//�������Ԃ̌����Ǝ擾
	int SubTimerLimit() { mTimerLimit--; return mTimerLimit; };

	//�������Ԃ̎擾
	const int GetTimerLimit() { return mTimerLimit; };

	//�Q�[���f�[�^�̃��Z�b�g=====================================
	void GameDataReset() {if(mSelect!=STAGE::FINALSTAGE)
								mTimerLimit = TIME;
							else
								mTimerLimit = FINALSTAGE_TIME;

							mDollNum = 0; };
	//==========================================================

	//�l�`�̑���
	void AddDollNum() { mDollNum++; };

	//�l�`�̐��̎擾
	const int GetDollNum() { return mDollNum; };

	//�����N�f�[�^�̓ǂݍ���
	bool InputData();

	//�����N�f�[�^�̏�������
	bool OutputData();

	//�����N�̕ۑ�
	void SetRank(STAGE stage, RANK rank);

	//�����N�̎擾
	void GetRank(RANK* rank, int num) { *rank = mRank[num]; };
};