#pragma once
/*
　クラス：ステージ
  作成者：三浦聖矢
  作成日：9/16　　
*/

#include<string>

#include"../../Utility.h"
#include"../../GameMain.h"

#include"../Player/Player.h"
#include"../Enemy/Enemy.h"
#include"Box.h"
#include"../UI/UI.h"
#include"../Mask/Mask.h"
#include"../Mist/Mist.h"
#include"Door.h"
#include"Doll.h"

//前方宣言
class GameData;

class Stage
{
public:
	//敵を配置できる最大数
	static const int ENEMY_NUM = 32;

	//箱を配置できる最大数
	static const int BOX_NUM = 32;

	//UIの数
	static const int UI_NUM = 5;

	//シーン
	enum class RESULTSCENE :int
	{
		GOAL,
		DIE,
		TIMEOVER,
		THUTRIAL,
		THUTRIAL2,
		THUTRIAL3,

		NONE,
	};

	//ステージ切り替え用
	enum class MODE :int
	{
		PLAY,
		THUTRIAL,
		THUTRIAL2,
		THUTRIAL3,
	};
private:
	//ステージ切り替え用
	int mSelectNum;

	//モード
	MODE mMode;

	//シーンの切り替え用
	RESULTSCENE mRS;

	//ＣＳＶステージデータの保存用配列
	int mStage[STAGE_SIZEY][STAGE_SIZEX];

	//ステージデータ更新用配列
	int mStageDefault[STAGE_SIZEY][STAGE_SIZEX];

	//画像用操作構造体
	SpriteData mSprite[STAGE_SIZEY][STAGE_SIZEX];

	//画像ハンドル
	int mTexture;

	//描画座標	
	Float2 mPos;
	Int2 mPos2;

	//箱の位置
	Int2 mBoxPos;

	//プレーヤーの位置
	Int2 mPlayerPos;

	//プレイヤークラスのポインタ
	Player* mpPlayer;

	//敵クラスのポインタ
	Enemy* mpEnemy[ENEMY_NUM];

	//箱のポインタ
	Box* mpBox[BOX_NUM];

	//ドアクラス
	std::vector<Door*> mpDoor;

	//UIクラス
	GameUI* mpUI[UI_NUM];

	//マスククラス
	Mask* mpMask;

	//ステージ上の敵の数
	int mEnemyCounter;

	//ステージ上の箱の数
	int mBoxCounter;

	//鍵の数
	int mKey;

	//霧クラス
	Mist* mpMist;

	//ゲームデータクラス
	GameData* mpGameData;

	//人形クラス
	std::vector<Doll*> mpDoll;

	//人形の数
	int mDollCounter;

	//ステージの移動フラグ
	bool mMoveFlag;

	//ステージの移動座標
	Int2 mMovePos;
public:
	Stage(int SelectNum,MODE mode, GameData* pGameData);		//コンストラクタ
	~Stage();		//デストラクタ

	bool LoadCSV();	//ステージデータの読み込み
	void Initialize();	//初期化
	void Update();		//更新
	void Draw();		//描画

	//ステージの移動
	void MoveStage();

	//ゲームの終了フラグ
	RESULTSCENE GameEnd();

	//鍵の数の確認
	bool KeyCheckFlag();

	//時間の取得
	void SetTimerLimit(int num);

	void Finalize();	//終了処理
};