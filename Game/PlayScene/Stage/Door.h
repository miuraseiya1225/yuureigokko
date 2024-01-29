/*
　クラス：扉
  作成者：三浦聖矢
  作成日：１/15　　
*/
#pragma once
#include"../../Utility.h"

class Door
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
	//スプライト
	SpriteData mSprite;

	//画像データ
	int mTexture;

	//座標
	Int2 mPos;
	Int2 mBoadPos;

	//扉が開いているか
	bool mOpenFlag;

	//音声データ
	int mAudio;
public:
	Door(int x, int y);		//コンストラクタ
	~Door();		//デストラクタ

	//初期化
	void Initialize();

	//描画
	void Draw();

	//ドアを開ける
	void OpenDoor();

	//ドアが開いているか
	bool CheckDoor() { return mOpenFlag; };

	//プレイヤーの座標チェック
	bool CheckPlayer(int x, int y);

	//ステージが動いた時の処理
	bool StageMove(MOVE move);
};