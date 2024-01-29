/*
　クラス：プレイヤーの心音
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/8　　　　
*/
#include"HeartBeat.h"
#include"../Player/Player.h"
#include"../Enemy/Enemy.h"
#include"../../Resource/Resource.h"

//=============================================
//			コンストラクタ
//=============================================
HeartBeat::HeartBeat():
	mBeatTimer{}
	,mRadius{0.0f}
{

}

//=============================================
//			デストラクタ
//=============================================
HeartBeat::~HeartBeat()
{

}

//=============================================
//			初期化
//=============================================
void HeartBeat::Initialize()
{
	//リソースマネージャー取得
	ResourceManager* prm = ResourceManager::GetInstance();

	//画像データ取得
	mTexture = prm->LoadTexture(eTEXTURE::RED_SCREEN, "RedScreen.png");

	//音声データの取得
	mAudio = prm->LoadAudio(eAUDIO::HEART, "HeartBeat2.mp4");
	ChangeVolumeSoundMem(255, mAudio);

	//赤い画面==========================
	mSprite.SetTexture(mTexture);
	mSprite.src.x = 0;
	mSprite.src.y = 0;
	mSprite.size.x = 640;
	mSprite.size.y = 480;
	mSprite.scale.x = 4.0f;
	mSprite.scale.y = 4.0f;
	mSprite.pos.x = 320;
	mSprite.pos.y = 240;
	mSprite.alpha = 0.3f;
	//====================================

	//プレイヤーのアドレス取得
	mpPlayer = GetpPlayer();

	//敵のアドレス取得
	mpEnemy = GetpEnemy();

	//敵の座標取得
	mEnemyPos.resize(mEnemyNum);

	//プレイヤーの座標取得
	mPlayerPos = mpPlayer->GetposMicro();

	//敵の座標取得
	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();
	}
	mRange.resize(mEnemyNum);
}

//=============================================
//			更新
//=============================================
void HeartBeat::Update()
{
	if (mpPlayer->GetTimerLimit() < 1)
		return;

	//プレイヤーのアドレス取得
	mPlayerPos = mpPlayer->GetposMicro();
	
	//敵の座標取得
	for (int i = 0; i < mEnemyNum; i++)
	{
		mEnemyPos[i] = mpEnemy[i]->GetposMicro();
	}

	//敵が近くにいなかったら返す===============================-
	if (EnemyRange() == false)
	{
		mRadius = 0.0f;
		mAlpha = 0.0f;
		StopSoundMem(mAudio);
		return;
	}

	//敵が近いほど赤くする
	mAlpha = (256.0f - mRange[mRangeLow]) / 512.0f;

	//一定時間経ったら音声を止める
	if (mRadius > 96)
	{
		mRadius = 0;
		StopSoundMem(mAudio);
	}


	if (mRadius == 0)
		PlaySoundMem(mAudio, DX_PLAYTYPE_BACK, TRUE);

	//敵が近いほど心音を早くする
	mBeatInterval = (256.0f - mRange[mRangeLow]) / 32.0f;

	if (mBeatInterval < 0)
		mBeatInterval = 0;

	mRadius += mBeatInterval;
}

//=============================================
//			描画
//=============================================
void HeartBeat::Draw()
{
	//敵が近くにいなかったら返す===============================-
	if (EnemyRange() == false)
		return;

	mSprite.Draw();

	//心音の描画================================================================
	DrawCircle(mPlayerPos.mX, mPlayerPos.mY, 2, GetColor(255, 0, 0), true);

	for (int i = 0; i < 5; i++)
	{
		DrawCircle(mPlayerPos.mX, mPlayerPos.mY, static_cast<int>(mRadius) + i, GetColor(64, 0, 0), false);
	}
	//============================================================================--

	mSprite.alpha = mAlpha;
}

//=============================================
//			敵との距離
//=============================================
bool HeartBeat::EnemyRange()
{
	for (int i = 0; i < mEnemyNum; i++)
	{
		//敵の距離を計算=================================
		float RangeX = static_cast<float>(mPlayerPos.mX - mEnemyPos[i].mX);
		float RangeY = static_cast<float>(mPlayerPos.mY - mEnemyPos[i].mY);

		if (RangeX < 0)
			RangeX *= -1;
		if (RangeY < 0)
			RangeY *= -1;

		mRange[i] = (RangeX * RangeX) + (RangeY * RangeY);

		mRange[i] = static_cast<float> (sqrt(mRange[i]));

		//==============================================
	}

	mRangeLow = 0;

	//一番プレイヤーに近い敵を探す===============================================
	for (int i = 0; i < mEnemyNum; i++)
	{
		if (mRange[mRangeLow] > mRange[i])
			mRangeLow = i;
	}
	//=========================================================-

	//敵の索敵距離を指定
	if (mRange[mRangeLow] < 256.0f)
		return true;

	return false;
}

