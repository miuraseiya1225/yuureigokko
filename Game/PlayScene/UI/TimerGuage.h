#pragma once
/*
　クラス：制限時間
		　ゲームUI:派生クラス
  作成者：三浦聖矢
  作成日：１2/9　　　　
*/
#include"UI.h"

//前方宣言
class GameData
	;
class TimerGuage :public GameUI
{
private:
	int mTimerLimit;		//制限時間

	GameData* mpGameData;	//ゲームデータ
public:
	TimerGuage(GameData* pGameData);	//コンストラクタ
	~TimerGuage()override;			//デストラクタ

	void Initialize()override;		//初期化

	void Update()override;		//更新

	void Draw()override;		//描画
};