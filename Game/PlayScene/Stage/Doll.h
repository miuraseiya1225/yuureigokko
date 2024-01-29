/*
　クラス：人形
  作成者：三浦聖矢
  作成日：１/16　　
*/
#pragma once
#include"../../Utility.h"

//前方宣言
class Player;

class Doll
{
public:
	//方向
	enum class MOVE :int
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
	};
private:
	SpriteData mSprite;		//スプライト
	int mTexture;		//画像データ
	Int2 mPos;		//座標
	Int2 mBoadPos;		//ステージ上の座標
	bool mPickFlag;		//人形を拾ったか

	bool mSoundFlag;	//効果音を鳴らしたか
	int mAudio;		//音声データ
public:
	Doll(int x, int y);		//コンストラクタ
	~Doll();		//デストラクタ

	void Initialize();		//初期化
	void Update(Player* pPlayer);		//更新
	const void Draw();	//描画

	//座標の取得
	const Int2 GetPos() { return mBoadPos; };

	//人形を拾う
	void Pick() { mPickFlag = true; };

	//ステージが動いた時の処理
	bool StageMove(MOVE move);
};