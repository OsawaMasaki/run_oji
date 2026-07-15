#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
//#include "TestScene.h"
#include "Engine/Input.h"

Enemy::Enemy(GameObject* parent)
         :GameObject(parent), hModel_(-1)
{
}
void Enemy::Initialize()
{
	hModel_ = Model::Load("ranoji_en.fbx");
	
}


void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
