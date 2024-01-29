#pragma once
/*
　クラス：Explanation:説明クラス　基底
  作成者：三浦聖矢
  作成日：１2/2　　　　
*/
#include"../../Utility.h"
#include"../../PlayScene/Stage/Stage.h"
#include"../../ScroolMassage/ScrollMassage.h"

//前方宣言
class GameData;

//メッセージ構造体
struct Message
{
	std::string mMessage;		//メッセージ	
	Int2 mPos;					//座標
	Color3 mColor;				//色
	int mSize;					//大きさ
	int mVel;					//流す速度
	int mLine;					//改行
	int mType;					//タイプ
};

class Explanation
{
public:
	//チュートリアル
	enum class THUTRIAL :int
	{
		BOX,
		ENEMY,
		STAGE,

		NONE,
	};
protected:
	std::vector<Message> mMessage;		//メッセージ構造体

	int mMessageNum;					//メッセージの数

	ScrollMassage* mpSM;				//スクロールメッセージクラス

	SpriteData mSprite;					//スプライト

	Stage* mpStage;						//ステージクラス

	bool mPlayFlag;						//プレイできるか

	int mCounter;						//カウンター

	GameData* mpGameData;				//ゲームデータ
public:
	Explanation();					//コンストラクタ
	virtual ~Explanation();			//デストラクタ

	bool LoadCSV(int low,int high);	//メッセージ用CSVファイルの読み込み
	virtual void Initialize()=0;		//初期化
	virtual void Update()=0;			//更新
	virtual void Draw()=0;			//描画

	virtual THUTRIAL FinalFlag()=0;	//終了フラグ

	void Finalize();				//終了処理
};