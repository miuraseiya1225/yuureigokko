/*
　クラス：ゲームのスコア
  作成者：三浦聖矢
  作成日：１/14　　　
*/
#pragma once

//前方宣言
class GameData;

class Score
{	
private:
	int mDollAudio;			//音源データ
	int mScoreAudio;			//音源データ

	SpriteData mSprite;		//スプライト

	int mTexture;		//画像データ

	int mTimer;		//タイマー

	bool mFlag;		//フラグ

	GameData* mpGameData;		//ゲームデータ

	bool mNextFlag;		//タイトルに戻れるフラグ
public:
	Score(GameData* pGameData);		//コンストラクタ
	~Score();			//デストラクタ

	void Initialize();		//初期化
	void Update();			//更新
	void Draw();			//描画

	const bool NextFlag() { return mNextFlag; };		//タイトルシーンに戻れるか
};