/*
　クラス：ゲームのスコア
  作成者：三浦聖矢
  作成日：１/14　　　
*/
#include"../GameData/GameData.h"
#include "Score.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
Score::Score(GameData* pGameData):
 mTimer{}
, mFlag{ false }
,mNextFlag{false}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
Score::~Score()
{
	StopSoundMem(mDollAudio);
	StopSoundMem(mScoreAudio);
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void Score::Initialize()
{
	//画像データ
	ResourceManager* prm = ResourceManager::GetInstance();

	//音源取得
	mDollAudio = prm->LoadAudio(eAUDIO::DOLL_PULL, "Doll.mp3");
	mScoreAudio = prm->LoadAudio(eAUDIO::SCORE, "Push.mp3");

	//画像データ取得
	mTexture = prm->LoadTexture(eTEXTURE::DOLL, "miseityanningyou.png");

	//画像の設定=================================
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
更新
--------------------------------------------------*/
void Score::Update()
{
	if (mTimer >= 60)
		mFlag = true;
	mTimer++;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void Score::Draw()
{
	int defaultSize = GetFontSize();

	SetFontSize(70);

	GameData::RANK mRank= GameData::RANK::NONE;

	//人形の数からランクを付ける=====================
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

	//ランクを保存する
	mpGameData->SetRank(static_cast<GameData::STAGE> (mpGameData->GetStageSelect()), mRank);


	DrawFormatString(SCREEN_CENTER_X - 280,
		SCREEN_CENTER_Y - 80,
		GetColor(255, 255, 255), "みせいちゃん人形");

	//集めた人形の描画========================================
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

	//効果音=====================================================
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

	//ランクの描画===================================================================================
	if (mTimer >= 180)
	{
		mNextFlag = true;

		DrawFormatString(SCREEN_CENTER_X - 250, SCREEN_CENTER_Y + 200, GetColor(255, 255, 255), "ランク");

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