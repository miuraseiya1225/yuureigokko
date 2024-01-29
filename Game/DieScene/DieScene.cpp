/*
リザルトシーン
*/
#include"DieScene.h"

#include "../GameMain.h"
#include"../Resource/Resource.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
DieScene::DieScene():mpBlood{},mModeSelect{MODE_SELECT::PLAY},mFlow{FLOW::MAIN},mColor3{}
{
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
DieScene::~DieScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void DieScene::Initialize()
{
	//リソースマネージャー
	ResourceManager* prm = ResourceManager::GetInstance();

	mPushAudio = prm->LoadAudio(eAUDIO::SCORE, "Push.mp3");

	//画像の読み込み
	mTexture = prm->LoadTexture(eTEXTURE::GAMEOVER_LOGO, "GameOver.png");

	//画像の設定========================================================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 549;
	mSprite.size.y = 123;
	mSprite.scale.x = 2.0f;
	mSprite.scale.y = 2.0f;
	mSprite.pos.x = SCREEN_CENTER_X;
	mSprite.pos.y = SCREEN_TOP + 150;
	//=============================================================

	//血クラスの実体化と初期化=======
	mpBlood = new Blood();
	mpBlood->Initialize();
	//=========================-----

	FadeInUpdate(1.0f);
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE DieScene::Update()
{
	switch (mFlow)
	{
		case FLOW::MAIN:
		{			
			//色の初期化==================
			for (int i = 0; i < 2; i++)
			{
				mColor3[i].mRed = 255;
				mColor3[i].mGreen = 255;
				mColor3[i].mBlue = 255;
			}
			//=============================

			//血の更新
			if (mpBlood->End() == false)
				mpBlood->Update();
			else
			{
				//シーン選択=============================
				if (IsButtonPressed(PAD_INPUT_UP))
					mModeSelect = MODE_SELECT::PLAY;
				if (IsButtonPressed(PAD_INPUT_DOWN))
					mModeSelect = MODE_SELECT::TITLE;

				switch (mModeSelect)
				{
					case MODE_SELECT::PLAY:
					{
						mColor3[0].mRed = 255;
						mColor3[0].mGreen = 0;
						mColor3[0].mBlue = 255;
						break;
					}
					case MODE_SELECT::TITLE:
					{
						mColor3[1].mRed = 255;
						mColor3[1].mGreen = 0;
						mColor3[1].mBlue = 255;
						break;
					}
					default:
						break;
				}
				//=====================================-

				if (IsButtonPressed(PAD_INPUT_1))
				{
					PlaySoundMem(mPushAudio, DX_PLAYTYPE_BACK);
					mFlow = FLOW::FADE_OUT;
				}
			}
			break;
		}
		case FLOW::FADE_OUT:
		{
			//フェードの更新
			int res = FadeOutUpdate(FADE_TIME);

			//フェードが終了したら次の状態へ
			if (res == false)
				mFlow = FLOW::FINALIZE;

			break;
		}
		case FLOW::FINALIZE:
		{
			Reset();

			//次のシーンへ================================
			if(mModeSelect==MODE_SELECT::PLAY)
				return GAME_SCENE::PLAY;
			if (mModeSelect == MODE_SELECT::TITLE)
				return GAME_SCENE::TITLE;
			//===========================================

			break;
		}
	}
	
	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void DieScene::Draw()
{
	//血の描画
	mpBlood->Draw();

	//文字などの描画===============================================================================================================================================
	if (mpBlood->End() == true)
	{
		mSprite.Draw();

		int defaultSize = GetFontSize();

		SetFontSize(120);

		DrawFormatString(SCREEN_CENTER_X - 400, (SCREEN_CENTER_Y - 100), GetColor(mColor3[0].mRed, mColor3[0].mGreen, mColor3[0].mBlue), "コンティニュー");
		DrawFormatString(SCREEN_CENTER_X - 300, (SCREEN_CENTER_Y + 100), GetColor(mColor3[1].mRed, mColor3[1].mGreen, mColor3[1].mBlue), "タイトルへ");

		SetFontSize(defaultSize);
	}
	//==============================================================================================================================================================
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void DieScene::Finalize()
{
	delete mpBlood;
	mpBlood = nullptr;
}

void DieScene::Reset()
{
	mFlow = FLOW::MAIN;
}
