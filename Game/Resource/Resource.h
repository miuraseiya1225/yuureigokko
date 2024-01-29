/*
リソースの管理クラス
*/
#pragma once

#include<string>

//テクスチャの種類
enum class eTEXTURE :int
{
	MAP_TILE,
	CHARA,
	NORMAL,
	NORMALLIGHT,
	CHASEV1,
	CHASEV2,
	HAND,
	ENEMY_ALL,
	BOX,
	SCREEN_ALPHA,
	RED_SCREEN,
	BLOOD,
	MIST,
	DOLL,
	DOLL_MOLD,
	TITLE,
	TITLE_LOAD,
	SELECT_BACK,
	RESULT_LOGO,
	RESULT_BACK,
	GAMEOVER_LOGO,

	MAX,
};

//音源の種類
enum class eAUDIO :int
{
	TITLE,
	DOLL_PULL,
	SCORE,
	WALK,
	HEART,
	CREAM,
	BLOOD,
	ATTACK,
	NORMAL,
	BLACK,
	CHASEV1,
	CHASEV2,
	HAND,
	ROOM,
	GETKEY,
	OPENDOOR,
	OPENBOX,
	MAX,
};

class ResourceManager
{
public:
	
	//どこからでもアクセスできるようにするための処理
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;

		return &instance;
	}

private:

	//テクスチャの配列
	int mTextures[static_cast<int>(eTEXTURE::MAX)];

	//音源の配列
	int mAudio[static_cast<int>(eAUDIO::MAX)];
public:
	//コンストラクタ
	ResourceManager();

	//デストラクタ
	~ResourceManager();

	//テクスチャ=====================================
	//テクスチャの読み込み
	int LoadTexture(eTEXTURE textureId, std::string path);

	//テクスチャの取得
	int GetTexture(eTEXTURE textureId);

	//画像の削除
	void DeleteTexture(eTEXTURE textureId);

	//全画像の削除
	void DeleteTextureALL();
	//==================================================

	//音源==============================================
	//音源の読み込み
	int LoadAudio(eAUDIO audioId, std::string path);

	//音源の取得
	int GetAudio(eAUDIO audioId);

	//音源の削除
	void DeleteAudio(eAUDIO audioId);

	//音源の削除
	void DeleteAudioALL();
	//==================================================
};