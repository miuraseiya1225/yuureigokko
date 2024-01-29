/*
　クラス：ステージ選択シーン
  作成者：三浦聖矢
  作成日：１2/15　　　
*/
#include<fstream>
#include<sstream>
#include"SSScene.h"
#include"../GameData/GameData.h"
#include"../Resource/Resource.h"

#include "../GameMain.h"

/*--------------------------------------------------
コンストラクタ
--------------------------------------------------*/
SelectScene::SelectScene(GameData* pGameData):mFlow{FLOW::INITIALIZE},mState{STATE::STAGE1},mColor{},mpEN{},mPos{},mDisplay{DISPLAY::ENEMY_NUM},mFinalStageFlag{false}
{
	mpGameData = pGameData;
}

/*--------------------------------------------------
デストラクタ
--------------------------------------------------*/
SelectScene::~SelectScene()
{
}

/*--------------------------------------------------
初期化
--------------------------------------------------*/
void SelectScene::Initialize()
{
	//リソースマネージャーのインスタンスを取得する
	ResourceManager* Resource = ResourceManager::GetInstance();
	//画像をリソースマネージャーに登録して画像ハンドルを取得する
	mTexture = Resource->LoadTexture(eTEXTURE::SELECT_BACK, "SS.png");
	//音源取得
	mAudio = Resource->LoadAudio(eAUDIO::TITLE, "TitleBGM.mp3");
	mPushAudio = Resource->LoadAudio(eAUDIO::SCORE, "Push.mp3");

	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = SCREEN_RIGHT;
	mSprite.size.y = SCREEN_BOTTOM;
	mSprite.pos.x = SCREEN_CENTER_X;
	mSprite.pos.y = SCREEN_CENTER_Y;

	//敵の数クラスの実体化と初期化
	mpEN = new EnemyNum();
	mpEN->Initialize();

	mPos.mX = 50;
	mPos.mY = SCREEN_CENTER_Y - 200;

	//ランクデータの取得
	mpGameData->InputData();
}

/*--------------------------------------------------
更新
戻り値	:次のシーン番号
--------------------------------------------------*/
GAME_SCENE SelectScene::Update()
{
	switch (mFlow)
	{
		case FLOW::INITIALIZE:
		{
			Reset();

			mFlow = FLOW::FADE_IN;

			SetFadeOut();
			break;
		}
		case FLOW::FADE_IN:
		{
			int res = FadeInUpdate(FADE_TIME);

			if (res == false)
				mFlow = FLOW::MAIN;
			break;
		}
		case FLOW::MAIN:
		{
			//入力による表示切り替え================================================================
			bool res = false;
			if (IsButtonPressed(PAD_INPUT_10) && mDisplay == DISPLAY::ENEMY_NUM && res == false)
			{
				mDisplay = DISPLAY::RANK;
				res = true;
			}
			if (IsButtonPressed(PAD_INPUT_10) && mDisplay == DISPLAY::RANK && res == false)
			{
				mDisplay = DISPLAY::ENEMY_NUM;
				res = true;
			}
			//======================================================================================

			//フォント色の初期化===================================================================
			for (int i = 0; i < static_cast<int> (STATE::STAGE_NUM); i++)
			{
				mColor[i].mRed = 255;
				mColor[i].mGreen = 255;
				mColor[i].mBlue = 255;
			}
			//=====================================================================================

			//ファイナルステージに行けるかのチェック===============================================
			mFinalStageFlag = false;

			for (int i = 0; i < 5; i++)
			{
				GameData::RANK mRank;
				mpGameData->GetRank(&mRank, i);

				if (mRank == GameData::RANK::S)
					mFinalStageFlag = true;
				else
				{
					mFinalStageFlag = false;

					break;
				}
			}
			//========================================================================================
			
			//ステージ選択画面切り替え================================================================
			if (IsButtonPressed(PAD_INPUT_RIGHT) && mFinalStageFlag == true)
			{
				mState = STATE::FINALMAP;
			}
			if (IsButtonPressed(PAD_INPUT_LEFT) && mFinalStageFlag == true)
			{
				mState = STATE::STAGE1;
			}
			//=========================================================================================

			//ステージ選択=============================================================================

			switch (mState)
			{
				case STATE::STAGE1:
				{
					mColor[0].mRed = 255;
					mColor[0].mGreen = 0;
					mColor[0].mBlue = 0;

					mPos.mY = SCREEN_CENTER_Y - 200;

					if (IsButtonPressed(PAD_INPUT_DOWN))
						mState = STATE::STAGE2;
					mpGameData->SetStageSelect(GameData::STAGE::SELECT_1);
					break;
				}
				case STATE::STAGE2:
				{
					mColor[1].mRed = 255;
					mColor[1].mGreen = 0;
					mColor[1].mBlue = 0;

					mPos.mY = SCREEN_CENTER_Y - 80;

					if (IsButtonPressed(PAD_INPUT_UP))
						mState = STATE::STAGE1;
					if (IsButtonPressed(PAD_INPUT_DOWN))
						mState = STATE::STAGE3;
					mpGameData->SetStageSelect(GameData::STAGE::SELECT_2);
					break;
				}
				case STATE::STAGE3:
				{
					mColor[2].mRed = 255;
					mColor[2].mGreen = 0;
					mColor[2].mBlue = 0;

					mPos.mY = SCREEN_CENTER_Y + 40;

					if (IsButtonPressed(PAD_INPUT_UP))
						mState = STATE::STAGE2;
					if (IsButtonPressed(PAD_INPUT_DOWN))
						mState = STATE::STAGE4;
					mpGameData->SetStageSelect(GameData::STAGE::SELECT_3);
					break;
				}
				case STATE::STAGE4:
				{
					mColor[3].mRed = 255;
					mColor[3].mGreen = 0;
					mColor[3].mBlue = 0;

					mPos.mY = SCREEN_CENTER_Y + 160;

					if (IsButtonPressed(PAD_INPUT_UP))
						mState = STATE::STAGE3;
					if (IsButtonPressed(PAD_INPUT_DOWN))
						mState = STATE::STAGE5;
					mpGameData->SetStageSelect(GameData::STAGE::SELECT_4);
					break;
				}
				case STATE::STAGE5:
				{
					mColor[4].mRed = 255;
					mColor[4].mGreen = 0;
					mColor[4].mBlue = 0;

					mPos.mY = SCREEN_CENTER_Y + 280;

					if (IsButtonPressed(PAD_INPUT_UP))
						mState = STATE::STAGE4;
					mpGameData->SetStageSelect(GameData::STAGE::SELECT_5);
					break;
				}
				case STATE::FINALMAP:
				{
					mpGameData->SetStageSelect(GameData::STAGE::FINALSTAGE);

					break;
				}
				default:
					break;
			}
			//===============================================================================-

			//プレーシーンへ=================================================================
			if (IsButtonPressed(PAD_INPUT_1))
			{
				PlaySoundMem(mPushAudio, DX_PLAYTYPE_BACK);
				mFlow = FLOW::FADE_OUT;
			}
			//=============================================================================

			//タイトルシーンへ================================================================
			if (IsButtonPressed(PAD_INPUT_2))
			{
				PlaySoundMem(mPushAudio, DX_PLAYTYPE_BACK);
				return GAME_SCENE::TITLE;
			}
			//==============================================================================
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
			StopSoundMem(mAudio);

			Reset();

			return GAME_SCENE::PLAY;
			break;
		}
	}

	return GAME_SCENE::NONE;
}

/*--------------------------------------------------
描画
--------------------------------------------------*/
void SelectScene::Draw()
{
	//背景
	mSprite.Draw();

	int defaultSize = GetFontSize();

	SetFontSize(90);


	if (mState != STATE::FINALMAP)
	{
		for (int i = 0; i < static_cast<int> (STATE::STAGE_NUM); i++)
		{
			DrawFormatString(SCREEN_CENTER_X - 550, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(mColor[i].mRed, mColor[i].mGreen, mColor[i].mBlue), "STAGE%d", i + 1);
		}
	

		if (mDisplay == DISPLAY::RANK)
		{
			for (int i = 0; i < static_cast<int> (STATE::STAGE_NUM); i++)
			{
				GameData::RANK mRank;
				mpGameData->GetRank(&mRank, i);

				DrawFormatString(SCREEN_CENTER_X - 100, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(255, 255, 255), "ランク");

				switch (mRank)
				{
					case GameData::RANK::NONE:
					{
						DrawFormatString(SCREEN_CENTER_X + 230, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(255, 255, 255), "NONE");

						break;
					}
					case GameData::RANK::C:
					{
						DrawFormatString(SCREEN_CENTER_X + 230, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(0, 255, 0), "C");
						break;
					}
					case GameData::RANK::B:
					{
						DrawFormatString(SCREEN_CENTER_X + 230, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(192, 0, 0), "B");
						break;
					}
					case GameData::RANK::A:
					{
						DrawFormatString(SCREEN_CENTER_X + 230, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(128, 128, 128), "A");
						break;
					}
					case GameData::RANK::S:
					{
						DrawFormatString(SCREEN_CENTER_X + 230, (SCREEN_CENTER_Y - 300) + i * 120, GetColor(255, 255, 0), "S");
						break;
					}
					default:
						break;
				}
			}
		}
		else
			mpEN->Draw(0, 5);

		DrawBox(mPos.mX, mPos.mY, mPos.mX + 1200, mPos.mY + 10, GetColor(255, 0, 0), true);

		SetFontSize(50);

		DrawFormatString(SCREEN_CENTER_X - 300, SCREEN_BOTTOM - 70, GetColor(255, 255, 255), "スぺースキーで表示を切り替えられます");

		if(mFinalStageFlag==true)
			DrawFormatString(SCREEN_CENTER_X - 500, SCREEN_BOTTOM - 70, GetColor(255, 255, 255), "--->");
	}
	else
	{
		SetFontSize(150);

		DrawFormatString(SCREEN_CENTER_X - 360, (SCREEN_CENTER_Y - 300), GetColor(255, 0, 0), "FINALSTAGE");

		mpEN->FinalStageDraw();

		GameData::RANK mRank;
		mpGameData->GetRank(&mRank, 5);

		SetFontSize(120);

		DrawFormatString(SCREEN_CENTER_X - 300, (SCREEN_CENTER_Y + 100), GetColor(255, 255, 255), "ランク");

		switch (mRank)
		{
			case GameData::RANK::NONE:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, (SCREEN_CENTER_Y + 100), GetColor(255, 255, 255), "NONE");

				break;
			}
			case GameData::RANK::C:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, (SCREEN_CENTER_Y + 100) , GetColor(0, 255, 0), "C");
				break;
			}
			case GameData::RANK::B:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, (SCREEN_CENTER_Y + 100) , GetColor(192, 0, 0), "B");
				break;
			}
			case GameData::RANK::A:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, (SCREEN_CENTER_Y + 100) , GetColor(128, 128, 128), "A");
				break;
			}
			case GameData::RANK::S:
			{
				DrawFormatString(SCREEN_CENTER_X + 80, (SCREEN_CENTER_Y + 100) , GetColor(255, 255, 0), "S");
				break;
			}
			default:
				break;
		}

		SetFontSize(50);

		DrawFormatString(SCREEN_CENTER_X - 500, SCREEN_BOTTOM - 70, GetColor(255, 255, 255), "<---");
	}

	SetFontSize(defaultSize);
}

/*--------------------------------------------------
終了処理
--------------------------------------------------*/
void SelectScene::Finalize()
{
	delete mpEN;
	mpEN = nullptr;
}

void SelectScene::Reset()
{
	mFlow = FLOW::INITIALIZE;
	mpGameData->GameDataReset();
}