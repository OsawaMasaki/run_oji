#include "PlayScene.h"
#include "Player.h"
#include "ground.h"
#include "Enemy.h"
#include "feed.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Text.h"


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),myScore(0)
{
}

//初期化
void PlayScene::Initialize()
{
	//pWp = Instantiate<Weapon>(this);
	//Instantiate <Player>(this);
	//Instantiate <Ground>(this);
	//Instantiate <Enemy>(this);
	//Instantiate <Feed>(this);

	Player* pPlayer = Instantiate<Player>(this);
	Ground* pGround = Instantiate<Ground>(this);

	pPlayer->SetGround(pGround);

	Camera::SetPosition(XMFLOAT3(0.0f, 20.0f, -30.0f));


	pText_ = new Text;
	pText_->Initialize();
}

//更新
void PlayScene::Update()
{
	if (FindObject("feed") == nullptr || Input::IsKeyDown(DIK_C))
	{
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}

}

//描画
void PlayScene::Draw()
{
	std::string scrText;
	char buffer[256];
	sprintf(buffer, "%010d", myScore);
	scrText = "SCORE:" + std::string(buffer);
	pText_->Draw(30, 30, scrText.c_str());

}

//開放
void PlayScene::Release()
{
	pText_->Release();//テキストの解放
}
