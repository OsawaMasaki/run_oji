#pragma once
#include "Engine/GameObject.h"
#include "ground.h"

enum FeedType
{
	FEEDTYPE_NORMAL,
	FEEDTYPE_POWER,
	FEEDTYPE_MAX
};

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

	void SetFeedType(FeedType type);
	void OnCollision(GameObject* pTarget) override;

private:
	std::vector<std::vector<int>> feedData_;
	FeedType type_;//餌のモデル
	int hModel_;//
	int score_;
};

