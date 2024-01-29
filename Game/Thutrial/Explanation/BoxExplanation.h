/*
　クラス：箱と鍵の説明	
  作成者：三浦聖矢
  作成日：１/１　　　　
*/

#pragma once
#include"Explanation.h"

class BoxExplanation :public Explanation
{
private:

public:
	BoxExplanation(GameData* pGameData);		//コンストラクタ
	~BoxExplanation()override;					//デストラクタ

	void Initialize()override;					//初期化
	void Update()override;						//更新
	void Draw()override;						//描画

	THUTRIAL FinalFlag()override;				//終了フラグ
};