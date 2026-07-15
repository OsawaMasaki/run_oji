#pragma once
#include "Engine/GameObject.h"
#include "ground.h"

//class Ground; // 前方宣言

class Feed :
	public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Feed(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

private:
	std::vector<std::vector<int>> feedData_;
	int hModel_;//
	int mapWidth_;
	int mapHeight_;
};

