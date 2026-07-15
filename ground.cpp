#include "ground.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/CsvReader.h"



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
	:GameObject(parent), hSilly(-1), hTree(-1),mapWidth_(-1),mapHeight_(-1)
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
		}
	}


	//mapData_ = mapData;//ファイルグローバルのmapDataをコピーして
}

void Ground::Initialize()
{
	hSilly = Model::Load("uv2.fbx");
	Model::SetAnimFrame(hSilly, 0, 59, 1.0);

	//hTree = Model::Load("blook.fbx");
	hTree = Model::Load("blook2.fbx");
	//hTree = Model::Load("tree.fbx");

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
			if (mapData_[j][i] != 0) 
			{
				Transform tr;
				//tr.position_ = { 10.0f - i * 2 - 1,0.0f, 10.0f - j * 2 - 1 };
				tr.position_ = { -9.0f + i * 2.0f,0.0f,9.0f - j * 2.0f };
				Model::SetTransform(hTree, tr);
				Model::Draw(hTree);
			}
		}
	}
}

void Ground::Release()
{
}
