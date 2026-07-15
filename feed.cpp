#include "feed.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
//#include "TestScene.h"
#include "Engine/Input.h"
#include "Engine/CsvReader.h"


Feed::Feed(GameObject* parent)
	:GameObject(parent), hModel_(-1), mapWidth_(-1), mapHeight_(-1)
{
	CsvReader csvData;
	csvData.Load("feed.csv");
	mapWidth_ = csvData.GetWidth();
	mapHeight_ = csvData.GetHeight();

	feedData_ = std::vector<std::vector<int>>(mapHeight_, std::vector<int>(mapWidth_, 0));
	for (int x = 0;x < mapWidth_;x++)
	{
		for (int y = 0; y < mapHeight_;y++)
		{
			feedData_[y][x] = csvData.GetValue(x, y);
		}
	}
}

void Feed::Initialize()
{
	hModel_ = Model::Load("feed.fbx");
	//transform_.position_ = { 10.0f,0.7f,10.0f };
	//transform_.scale_ = { 3.0f,3.0f,3.0f };
}

void Feed::Update()
{

}

void Feed::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	for (int j = 0;j < 10;j++)
	{
		for (int i = 0;i < 10;i++)
		{
			if (feedData_[j][i] != 0)
			{
				Transform tr;
				//tr.position_ = { 10.0f - i * 2 - 1,0.0f, 10.0f - j * 2 - 1 };
				tr.position_ = { -9.0f + i * 2.0f,0.5f,9.0f - j * 2.0f };//高さが原点の位置だったからyを少し上げた
				tr.scale_ = { 2.0f,2.0f,2.0f };//モデルが小さかったから大きくした
				Model::SetTransform(hModel_, tr);
				Model::Draw(hModel_);
			}
		}
	}
}

void Feed::Release()
{
}
