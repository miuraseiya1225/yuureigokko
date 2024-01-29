#pragma once
/*
　クラス：メッセージログクラス
  作成者：三浦聖矢
  作成日：１２/２１　　　　
*/
#include"../Utility.h"

class ScrollMassage
{
private:
	std::string  mMassage;		//メッセージ
	Int2 mPos;					//座標
	int mMassageSize;			//大きさ
	int mMassageVel;			//流す速さ
	int mMassageLine;			//改行
	int mTimer;					//タイマー
	int mMassageNum;			//メッセージの個数
	int mType;					//タイプ
	Color3 mColor;				//色
public:
	//コンストラクタ
	ScrollMassage();

	//デストラクタ
	~ScrollMassage();

	//メッセージの初期化
	void SetMessage(const std::string  massage, Int2 pos2, Color3 color3,const int massagesize = 18, const int massageVel = 30, const int massageline = 10,int Type=1);

	//メッセージの描画
	bool DrawScrollMassage();

	//メッセージ全体を描画する
	void DrawMassageAll();

	//メッセージの設定をリセットする
	void Reset();
};