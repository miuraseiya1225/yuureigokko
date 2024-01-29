/*
　クラス：マスククラス
  作成者：三浦聖矢
  作成日：１2/30　　　　
*/
#include"Mask.h"
#include"../../Resource/Resource.h"

//インスタンスする
//InitializeとDrawはいつも通り
//Updateはいらない
//使うときはまずResetMaskを先に処理してSetAlpha(座標、マスクの範囲（値が小さいほど広くなる）)を処理する

//================================================
//			コンストラクタ
//================================================
Mask::Mask() :
	mAlpha{ 1.0f }
	, mAlpha_Frequency{ 0.0f }
	, mAlphaSprite1{}
	, mAlphaSprite2{}
	, mAlphaSprite3{}
	, mAlphaSprite4{}
{
}

//================================================
//			コンストラクタ
//================================================
Mask::~Mask()
{
}

//================================================
//			初期化
//================================================
void Mask::Initialize()
{
	//画像アドレス取得
	ResourceManager* prm = ResourceManager::GetInstance();
	mTexture = prm->LoadTexture(eTEXTURE::SCREEN_ALPHA, "BlackScreen.png");

	//マスクタイルの設定========================================================
	int s = (SCREEN_CENTER_Y) / BLACK_SIZE;
	mAlphaSprite1.resize(s);

	int h = ((SCREEN_RIGHT) / 2) / BLACK_SIZE;
	for (int i = 0; i < s; i++)
		mAlphaSprite1[i].resize(h);

	//黒い画面=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite1[y][x].SetTexture(mTexture);
			mAlphaSprite1[y][x].src.x = 0;
			mAlphaSprite1[y][x].src.y = 0;
			mAlphaSprite1[y][x].size.x = BLACK_SIZE;
			mAlphaSprite1[y][x].size.y = BLACK_SIZE;

			mAlphaSprite1[y][x].pos.x = 0;
			mAlphaSprite1[y][x].pos.y = 0;
			mAlphaSprite1[y][x].alpha = mAlpha;
		}
	}
	s = (SCREEN_CENTER_Y) / BLACK_SIZE;
	mAlphaSprite2.resize(s);

	h = (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1;
	for (int i = 0; i < s; i++)
		mAlphaSprite2[i].resize(h);

	//黒い画面=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite2[y][x].SetTexture(mTexture);
			mAlphaSprite2[y][x].src.x = 0;
			mAlphaSprite2[y][x].src.y = 0;
			mAlphaSprite2[y][x].size.x = BLACK_SIZE;
			mAlphaSprite2[y][x].size.y = BLACK_SIZE;

			mAlphaSprite2[y][x].pos.x = 0;
			mAlphaSprite2[y][x].pos.y = 0;
			mAlphaSprite2[y][x].alpha = mAlpha;
		}
	}
	s = ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1;
	mAlphaSprite3.resize(s);

	h = (((SCREEN_RIGHT) / 2) / BLACK_SIZE);
	for (int i = 0; i < s; i++)
		mAlphaSprite3[i].resize(h);

	//黒い画面=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite3[y][x].SetTexture(mTexture);
			mAlphaSprite3[y][x].src.x = 0;
			mAlphaSprite3[y][x].src.y = 0;
			mAlphaSprite3[y][x].size.x = BLACK_SIZE;
			mAlphaSprite3[y][x].size.y = BLACK_SIZE;

			mAlphaSprite3[y][x].pos.x = 0;
			mAlphaSprite3[y][x].pos.y = 0;
			mAlphaSprite3[y][x].alpha = mAlpha;
		}
	}
	s = ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1;
	mAlphaSprite4.resize(s);

	h = (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1;
	for (int i = 0; i < s; i++)
		mAlphaSprite4[i].resize(h);

	//黒い画面=======================
	for (int y = 0; y < s; y++)
	{
		for (int x = 0; x < h; x++)
		{
			mAlphaSprite4[y][x].SetTexture(mTexture);
			mAlphaSprite4[y][x].src.x = 0;
			mAlphaSprite4[y][x].src.y = 0;
			mAlphaSprite4[y][x].size.x = BLACK_SIZE;
			mAlphaSprite4[y][x].size.y = BLACK_SIZE;

			mAlphaSprite4[y][x].pos.x = 0;
			mAlphaSprite4[y][x].pos.y = 0;
			mAlphaSprite4[y][x].alpha = mAlpha;
		}
	}
	//==================================================================================
}


//================================================
//			描画
//			三平方の定理を使ってプレーヤーとタイル一つ当たりの距離を求め、透明度を変える
//================================================
void Mask::Draw()
{
	//左上↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	mPos.mX = -8;
	mPos.mY = -8;

	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		mPos.mX = -8;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < ((SCREEN_RIGHT) / 2) / BLACK_SIZE; x++)
		{
			mPos.mX += BLACK_SIZE;

			if (y + 1 == (SCREEN_CENTER_Y) / BLACK_SIZE)
				mPos2.mX = mPos.mX;

			mAlphaSprite1[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite1[y][x].pos.y = static_cast<float>(mPos.mY);

			if (x != ((SCREEN_RIGHT) / 2) / BLACK_SIZE)
				mAlphaSprite1[y][x].Draw();

		}
	}
	//左上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//==============================================================================

	//右上↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	mPos.mX = mPos2.mX;
	mPos.mY = -8;

	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		mPos.mX = mPos2.mX;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			mPos.mX += BLACK_SIZE;

			mAlphaSprite2[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite2[y][x].pos.y = static_cast<float>(mPos.mY);

			mAlphaSprite2[y][x].Draw();
		}
		if (y + 1 == (SCREEN_CENTER_Y) / BLACK_SIZE)
			mPos2.mY = mPos.mY;
	}
	//右上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//=================================================================================

	//左下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	mPos.mX = -8;
	mPos.mY = mPos2.mY;

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		mPos.mX = -8;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE); x++)
		{
			mPos.mX += BLACK_SIZE;

			if (y + 1 == (SCREEN_CENTER_Y) / BLACK_SIZE)
				mPos2.mX = mPos.mX;

			mAlphaSprite3[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite3[y][x].pos.y = static_cast<float>(mPos.mY);

			mAlphaSprite3[y][x].Draw();
		}

	}
	//左下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//============================================================================

	//右下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	mPos.mX = mPos2.mX;
	mPos.mY = mPos2.mY;

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		mPos.mX = mPos2.mX;
		mPos.mY += BLACK_SIZE;
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			mPos.mX += BLACK_SIZE;

			mAlphaSprite4[y][x].pos.x = static_cast<float>(mPos.mX);
			mAlphaSprite4[y][x].pos.y = static_cast<float>(mPos.mY);

			mAlphaSprite4[y][x].Draw();
		}
	}
	//右下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
}


//==============================================================================
// 引数：基点の座標　マスクの大きさ(値が小さいほど大きくなる)
//==============================================================================
void Mask::SetAlpha(Int2 BasePos, float Alpha_Frequency)
{
	if (BasePos.mX == 0 || BasePos.mY == 0)
		return;

	mAlpha_Frequency = Alpha_Frequency;

	mAlpha = 0.0f;
	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		for (int x = 0; x < ((SCREEN_RIGHT) / 2) / BLACK_SIZE; x++)
		{
			//基準からの距離を計算=========================
			int DisX = BasePos.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================
			//基準から遠いほど画面を暗くする
			mAlpha = (mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite1[y][x].alpha = mAlpha + 0.05f;
		}
	}
	//左上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//==============================================================================

	//右上↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	mAlpha = 0.0f;

	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
	{
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			//基準からの距離を計算=========================
			int DisX = BasePos.mX - mPos2.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================

			//基準から遠いほど画面を暗くする
			mAlpha =(mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite2[y][x].alpha = mAlpha + 0.05f;
		}
	}
	//右上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//=================================================================================

	//左下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	mAlpha = 0.0f;

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE); x++)
		{
			//基準からの距離を計算=========================
			int DisX = BasePos.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - mPos2.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================

			//基準から遠いほど画面を暗くする
			mAlpha = (mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite3[y][x].alpha = mAlpha + 0.05f;
		}

	}
	//左下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//============================================================================

	//右下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	mAlpha = 0.0f;

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
	{
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
		{
			//基準からの距離を計算=========================
			int DisX = BasePos.mX - mPos2.mX - x * BLACK_SIZE;
			int DisY = BasePos.mY - mPos2.mY - y * BLACK_SIZE;

			if (DisX < 0)
				DisX *= -1;

			if (DisY < 0)
				DisY *= -1;

			float Dis = static_cast<float>((DisX * DisX) + (DisY * DisY));
			Dis = sqrtf(Dis);
			//==================================================

			//基準から遠いほど画面を暗くする
			mAlpha =(mAlpha_Frequency * Dis);

			if (mAlpha < 1.0f)
				mAlphaSprite4[y][x].alpha = mAlpha + 0.05f;
		}
	}
	//右下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
}


//================================================
//			マスクの初期化
//================================================
void Mask::ResetMask()
{
	mAlpha = 1.0f;
	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < ((SCREEN_RIGHT) / 2) / BLACK_SIZE; x++)
			mAlphaSprite1[y][x].alpha = mAlpha + 0.05f;
	//左上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//==============================================================================

	//右上↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
			mAlphaSprite2[y][x].alpha = mAlpha + 0.05f;
	//右上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//=================================================================================

	//左下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE); x++)
			mAlphaSprite3[y][x].alpha = mAlpha + 0.05f;
	//左下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//============================================================================

	//右下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < (((SCREEN_RIGHT) / 2) / BLACK_SIZE) + 1; x++)
			mAlphaSprite4[y][x].alpha = mAlpha + 0.05f;

	//右下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
}

//================================================
//			終了処理
//================================================
void Mask::Finalize()
{
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < ((SCREEN_RIGHT - 128) / 2) / BLACK_SIZE; x++)
			mAlphaSprite1[y][x].Finalize();
	//左上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//==============================================================================

	//右上↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
	//画面を暗くする
	for (int y = 0; y < (SCREEN_CENTER_Y) / BLACK_SIZE; y++)
		for (int x = 0; x < ((SCREEN_RIGHT - 96) / 2) + 1 / BLACK_SIZE; x++)
			mAlphaSprite2[y][x].Finalize();
	//右上↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//=================================================================================

	//左下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < (((SCREEN_RIGHT - 96) / 2) / BLACK_SIZE) - 2; x++)
			mAlphaSprite3[y][x].Finalize();
	//左下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑

	//============================================================================

	//右下↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

	//画面を暗くする
	for (int y = 0; y < ((SCREEN_CENTER_Y) / BLACK_SIZE) + 1; y++)
		for (int x = 0; x < ((SCREEN_RIGHT - 96) / 2) + 1 / BLACK_SIZE; x++)
			mAlphaSprite4[y][x].Finalize();

	//右下↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
}
