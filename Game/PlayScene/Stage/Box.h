#pragma once
/*
　クラス：箱
  作成者：三浦聖矢
  作成日：9/16　　
*/
#include"../../Utility.h"

//前方宣言
class Player;

class Box
{
public:
	//向き
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};

private:
	Int2 mBoadPos;	//ステージ上の座標
	Int2 mPos;		//スクリーン上の座標
	Int2 mPlayerPos;	//プレイヤーの座標	

	int mTexture;	//画像データ
	SpriteData mSprite;		//スプライト

	int mStageBourd[STAGE_SIZEY][STAGE_SIZEX];		//ステージデータ

	bool mKeyNum;	//鍵が入っているか

	Player* mpPlayer;	//プレイヤークラス

	int mAudio;		//音声データ
public:
	Box(Player* pPlayer);	//コンストラクタ
	~Box();		//デストラクタ

	void Initialize();		//初期化
	void Update();		//更新
	const void Draw();	//描画

	void SetPos(int x, int y);		//座標の取得
	void GetPlayerPos();		//プレイヤーの座標取得

	const Int2 GetPos() { return mBoadPos; };		//座標のゲッター
	void SetStage(int stage[STAGE_SIZEY][STAGE_SIZEX]);		//ステージ情報の取得

	void OpenBox();		//箱を開ける

	void DeleteKey();		//鍵を無くす

	const bool ChackKey();		//鍵が入っているか

	bool StageMove(MOVE move);		//ステージが動いた時の処理
};