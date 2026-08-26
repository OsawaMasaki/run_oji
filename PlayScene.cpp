#include "PlayScene.h"
#include "Player.h"
#include "ground.h"
#include "Enemy.h"
#include "feed.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

namespace {
	int myScore = 10;
}

//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//初期化
void PlayScene::Initialize()
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
void PlayScene::Update()
{
	if (FindObject("feed") == nullptr)
	{
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);

	}

	if (Input::IsKeyDown(DIK_C))
	{
		//シーンマネージャーを探して、シーン切り替えの関数を呼ぶ
		// 見つからない場合はnullptrが返るので、nullptrでないことを確認してから呼ぶ
		SceneManager* pSceneManager = (SceneManager*)(this->GetParent());
		pSceneManager->ChangeScene(SCENE_ID_CLEAR);
	}
}

//描画
void PlayScene::Draw()
{
	//std::string scrText;
	//std::string remText;
	//scrText = "SCORE:" + std::to_string(myScore);
	//pText_ -> Draw(20, 20, scrText.c_str());
	//remText = "REMAINING" + std::to_string(myRemaining);
	//rText_->Draw(20, 50, remText.c_str());

}

//開放
void PlayScene::Release()
{
}
