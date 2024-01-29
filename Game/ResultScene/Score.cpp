/*
�@�N���X�F�Q�[���̃X�R�A
  �쐬�ҁF�O�Y����
  �쐬���F�P/14�@�@�@
*/
#include"../GameData/GameData.h"
#include "Score.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
�R���X�g���N�^
--------------------------------------------------*/
Score::Score(GameData* pGameData):
 mTimer{}
, mFlag{ false }
,mNextFlag{false}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
�f�X�g���N�^
--------------------------------------------------*/
Score::~Score()
{
	StopSoundMem(mDollAudio);
	StopSoundMem(mScoreAudio);
}

/*--------------------------------------------------
������
--------------------------------------------------*/
void Score::Initialize()
{
	//�摜�f�[�^
	ResourceManager* prm = ResourceManager::GetInstance();

	//�����擾
	mDollAudio = prm->LoadAudio(eAUDIO::DOLL_PULL, "Doll.mp3");
	mScoreAudio = prm->LoadAudio(eAUDIO::SCORE, "Push.mp3");

	//�摜�f�[�^�擾
	mTexture = prm->LoadTexture(eTEXTURE::DOLL, "miseityanningyou.png");

	//�摜�̐ݒ�=================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 32;
	mSprite.size.y = 32;
	mSprite.scale.x = 4.0f;
	mSprite.scale.y = 4.0f;
	//==========================================
}

/*--------------------------------------------------
�X�V
--------------------------------------------------*/
void Score::Update()
{
	if (mTimer >= 60)
		mFlag = true;
	mTimer++;
}

/*--------------------------------------------------
�`��
--------------------------------------------------*/
void Score::Draw()
{
	int defaultSize = GetFontSize();

	SetFontSize(70);

	GameData::RANK mRank= GameData::RANK::NONE;

	//�l�`�̐����烉���N��t����=====================
	if (mFlag == true)
	{
		if (mpGameData->GetDollNum() == 3)
			mRank = GameData::RANK::S;
		if (mpGameData->GetDollNum() == 2)
			mRank = GameData::RANK::A;
		if (mpGameData->GetDollNum() == 1)
			mRank = GameData::RANK::B;
		if (mpGameData->GetDollNum() == 0)
			mRank = GameData::RANK::C;
	}
	//================================================

	//�����N��ۑ�����
	mpGameData->SetRank(static_cast<GameData::STAGE> (mpGameData->GetStageSelect()), mRank);


	DrawFormatString(SCREEN_CENTER_X - 280,
		SCREEN_CENTER_Y - 80,
		GetColor(255, 255, 255), "�݂��������l�`");

	//�W�߂��l�`�̕`��========================================
	if (mTimer > 80&& mpGameData->GetDollNum() >= 1)
	{
		mSprite.pos.x = SCREEN_CENTER_X - 150;
		mSprite.pos.y = SCREEN_CENTER_Y + 100;
		mSprite.Draw();
	}
	if (mTimer > 100 && mpGameData->GetDollNum() >= 2)
	{
		mSprite.pos.x = SCREEN_CENTER_X;
		mSprite.pos.y = SCREEN_CENTER_Y + 100;
		mSprite.Draw();
	}
	if (mTimer > 120 && mpGameData->GetDollNum() >= 3)
	{
		mSprite.pos.x = SCREEN_CENTER_X +150;
		mSprite.pos.y = SCREEN_CENTER_Y + 100;
		mSprite.Draw();
	}

	//���ʉ�=====================================================
	if (mTimer == 80 && mpGameData->GetDollNum() >= 1)
		PlaySoundMem(mDollAudio, DX_PLAYTYPE_BACK);
	
	if (mTimer == 100 && mpGameData->GetDollNum() >= 2)
		PlaySoundMem(mDollAudio, DX_PLAYTYPE_BACK);

	if (mTimer == 120 && mpGameData->GetDollNum() >= 3)
		PlaySoundMem(mDollAudio, DX_PLAYTYPE_BACK);
	if(mTimer==180)
		PlaySoundMem(mScoreAudio, DX_PLAYTYPE_BACK);
	//=========================================================

	SetFontSize(90);
	//========================================================

	//�����N�̕`��===================================================================================
	if (mTimer >= 180)
	{
		mNextFlag = true;

		DrawFormatString(SCREEN_CENTER_X - 250, SCREEN_CENTER_Y + 200, GetColor(255, 255, 255), "�����N");

		switch (mRank)
		{
			case GameData::RANK::C:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, SCREEN_CENTER_Y + 200, GetColor(0, 255, 0), "C");
				break;
			}
			case GameData::RANK::B:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, SCREEN_CENTER_Y + 200, GetColor(192, 0, 0), "B");
				break;
			}
			case GameData::RANK::A:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, SCREEN_CENTER_Y + 200, GetColor(128, 128, 128), "A");
				break;
			}
			case GameData::RANK::S:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, SCREEN_CENTER_Y + 200, GetColor(255, 255, 0), "S");
				break;
			}
			default:
				break;
		}
		mTimer = 180;
	}
	//======================================================================================================

	SetFontSize(defaultSize);
}