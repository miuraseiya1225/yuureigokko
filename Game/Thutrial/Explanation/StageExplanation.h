/*
　クラス：ステージの説明
  作成者：三浦聖矢
  作成日：１/2　　　　
*/
#pragma once
#include"Explanation.h"

class StageExplanation :public Explanation
{
private:
public:
	StageExplanation(GameData* pGameData);	//コンストラクタ
	~StageExplanation()override;			//デストラクタ

	void Initialize()override;				//初期化
	void Update()override;					//更新
	void Draw()override;					//描画
	THUTRIAL FinalFlag()override;			//終了フラグ

};