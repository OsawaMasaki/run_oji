#include "feed.h"
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
//#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"


Feed::Feed(GameObject* parent)
	:GameObject(parent,"feed"), type_(FEEDTYPE_NORMAL), hModel_(-1), score_(0)
{
	//CsvReader csvData;
	//csvData.Load("map.csv");
	//mapWidth_ = csvData.GetWidth();
	//mapHeight_ = csvData.GetHeight();
	//feedData_ = std::vector<std::vector<int>>(mapHeight_, std::vector<int>(mapWidth_, 0));
	//for (int x = 0;x < mapWidth_;x++)
	//{
	//	for (int y = 0; y < mapHeight_;y++)
	//	{
	//		feedData_[y][x] = csvData.GetValue(x, y);
	//	}
	//}
}

void Feed::Initialize()
{
	hModel_ = Model::Load("feed.fbx");//モデルの読み込み
	//transform_.position_ = { 10.0f,0.7f,10.0f };

	SetFeedType(type_);

	//if (type_ == FeedType::FEEDTYPE_NORMAL)
	//{
	//	hModel_ = Model::Load("feed.fbx");
	//	score_ = 1;
	//}
	//if (type_ == FeedType::FEEDTYPE_POWER)
	//{
	//	hModel_ = Model::Load("powerfeed.fbx");
	//	score_ = 5;
	//}
}

void Feed::Update()
{
	if (type_ == FeedType::FEEDTYPE_POWER)
	{
		transform_.rotate_.y += 1.0f;
	}
}

void Feed::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	//for (int j =11;j < 20;j++)
	//{
	//	for (int i = 0;i < 10;i++)
	//	{
	//		if (feedData_[j][i] == 1)
	//		{
	//			Transform tr;
	//			//tr.position_ = { 10.0f - i * 2 - 1,0.0f, 10.0f - j * 2 - 1 };
	//			tr.position_ = { -9.0f + i * 2.0f,0.5f,(9.0f - j * 2.0f) + 20.0f };//高さが原点の位置だったからyを少し上げた
	//			tr.scale_ = { 2.0f,2.0f,2.0f };//モデルが小さかったから大きくした
	//			Model::SetTransform(hModel_, tr);
	//			Model::Draw(hModel_);
	//		}
	//		if (feedData_[j][i] == 2)
	//		{
	//			Transform tr;
	//			//tr.position_ = { 10.0f - i * 2 - 1,0.0f, 10.0f - j * 2 - 1 };
	//			tr.position_ = { -9.0f + i * 2.0f,0.5f,(9.0f - j * 2.0f) + 20.0f };//高さが原点の位置だったからyを少し上げた
	//			tr.scale_ = { 4.0f,4.0f,4.0f };//モデルが小さかったから大きくした
	//			Model::SetTransform(hModel_, tr);
	//			Model::Draw(hModel_);
	//		}
	//	}
	//}
}

void Feed::Release()
{
}

void Feed::SetFeedType(FeedType type)
{
	type_ = type;
	if (type_ == FeedType::FEEDTYPE_NORMAL)
	{
		SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 0.3f);
		AddCollider(collider);

		hModel_ = Model::Load("feed.fbx");
		transform_.scale_ = { 2.0f,2.0f,2.0f };
		score_ = 1;
	}
	else if (type_ == FeedType::FEEDTYPE_POWER)
	{
		SphereCollider* collider = new SphereCollider(XMFLOAT3(0.0f, 0.0f, 0.0f), 1.0f);
		AddCollider(collider);

		transform_.scale_ = { 1.0f,1.0f,1.0f };
		hModel_ = Model::Load("powerfeed.fbx");
		score_ = 5;
	}
}

void Feed::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
	}
}
