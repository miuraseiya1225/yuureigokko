#pragma once
/*
　クラス：人形の数
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１/17　　　　
*/
#include"UI.h"

//前方宣言
class GameData;

class DollNum :public GameUI
{
private:
	GameData* mpGameData;		//ゲームデータクラス
	SpriteData mMoldSprite;		//人形の型用のスプライト

	int mDollNum;		//人形の数
public:
	DollNum(GameData* pGameData);		//コンストラクタ
	~DollNum()override;		//デストラクタ

	void Initialize()override;		//初期化
	void Update()override;			//更新
	void Draw()override;			//描画
};