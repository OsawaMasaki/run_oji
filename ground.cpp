#include "ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/CsvReader.h"
#include "feed.h"



namespace
{
	//using std::vector;
	////メンバ化して呼んでこれるようにする
	//vector<vector<int>> mapData =
	//{
	//	{1,1,1,1,1,1,1,1,1,1},
	//	{1,0,1,0,0,0,0,0,1,1},
	//	{1,0,1,0,1,0,1,0,0,1},
	//	{1,0,1,1,1,0,1,1,0,1},
	//	{1,0,0,0,0,0,1,0,0,1},
	//	{1,0,1,1,1,1,1,0,1,1},
	//	{1,0,1,0,0,0,0,0,0,1},
	//	{1,0,1,1,1,0,1,1,1,1},
	//	{1,1,0,0,0,0,0,0,0,1},
	//	{1,1,1,1,1,1,1,1,1,1},
	//};
}

Ground::Ground(GameObject* parent)
	:GameObject(parent), hSilly(-1), hBlock(-1),mapWidth_(-1),mapHeight_(-1)
{
	CsvReader csvData;
	csvData.Load("map.csv");
	mapWidth_ = csvData.GetWidth();
	mapHeight_ = csvData.GetHeight();

	mapData_ = std::vector<std::vector<int>>(mapHeight_, std::vector<int>(mapWidth_, 0));
	for (int x = 0;x < mapWidth_;x++)
	{
		for (int y = 0; y < mapHeight_;y++)
		{
			mapData_[y][x] = csvData.GetValue(x, y);
			if (mapData_[y][x] != 1)
			{
				Feed* feed = Instantiate<Feed>(this);
				//esaCount_
				feed->SetPosition({ -9.0f + x * 2.0f,0,(9.0f - y * 2.0f)});
				if (mapData_[y][x] == 3)
				{
					feed->SetFeedType(FeedType::FEEDTYPE_POWER);
				}
				else
				{
					feed->SetFeedType(FeedType::FEEDTYPE_NORMAL);
				}
			}
		}
	}

	//mapData_ = mapData;//ファイルグローバルのmapDataをコピーして
}

void Ground::Initialize()
{
	hSilly = Model::Load("uv2.fbx");

	//hBlock = Model::Load("blook.fbx");
	hBlock = Model::Load("blook2.fbx");
	//hBlock = Model::Load("tree.fbx");

}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetTransform(hSilly, transform_);
	Model::Draw(hSilly);

	for (int j = 0;j < 10;j++)
	{
		for (int i = 0;i < 10;i++)
		{
			if (mapData_[j][i] == 1) 
			{
				Transform tr;
				//tr.position_ = { 10.0f - i * 2 - 1,0.0f, 10.0f - j * 2 - 1 };
				tr.position_ = { -9.0f + i * 2.0f,0.0f,9.0f - j * 2.0f };
				Model::SetTransform(hBlock, tr);
				Model::Draw(hBlock);
			}
		}
	}
}

void Ground::Release()
{
}
