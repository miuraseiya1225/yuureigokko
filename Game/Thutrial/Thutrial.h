#pragma once
#include "../IScene.h"
#include"Explanation/Explanation.h"

//前方宣言
class GameData;

class ThutrialScene : public IScene
{
public:
	//状態
	enum class FLOW :int
	{
		FADE_IN,
		FADE_OUT,
		INITIALIZE,
		MAIN,
		FINALIZE,
	};

private:
	Explanation::THUTRIAL mState;	//チュートリアル用

	GameData* mpGameData;			//ゲームデータ
	FLOW mFlow;						//状態

	Explanation* mpExplanation;		//説明クラス	
public:

	// コンストラクタ
	ThutrialScene(GameData* pGameData);

	// デストラクタ
	~ThutrialScene();

	// 初期化
	void Initialize() override;

	// 更新
	GAME_SCENE Update() override;

	// 描画
	void Draw() override;

	// 終了処理
	void Finalize() override;

	//次のシーン
	void Next();

	//リセット
	void Reset();
};