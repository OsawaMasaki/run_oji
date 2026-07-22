#include "TestScene.h"
#include "Player.h"
#include "ground.h"
#include "Enemy.h"
#include "Engine/Camera.h"
#include "feed.h"

namespace {
	int myScore = 10;
}

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{	
	//pWp = Instantiate<Weapon>(this);
	//Instantiate <Player>(this);
	//Instantiate <Ground>(this);
	Instantiate <Enemy>(this);
	Instantiate <Feed>(this);

	Player* pPlayer = Instantiate<Player>(this);
	Ground* pGround = Instantiate<Ground>(this);

	pPlayer->SetGround(pGround);

	//pText_ = new Text;
	//pText_ -> Initialize();


	Camera::SetPosition(XMFLOAT3(0.0f, 20.0f, -30.0f));
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
	//std::string scrText;
	//std::string remText;
	//scrText = "SCORE:" + std::to_string(myScore);
	//pText_ -> Draw(20, 20, scrText.c_str());
	//remText = "REMAINING" + std::to_string(myRemaining);
	//rText_->Draw(20, 50, remText.c_str());

}

//開放
void TestScene::Release()
{
}
