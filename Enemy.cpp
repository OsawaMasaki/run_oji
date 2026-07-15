#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/Input.h"

Enemy::Enemy(GameObject* parent)
         :GameObject(parent), hModel_(-1)
{
}
void Enemy::Initialize()
{
	hModel_ = Model::Load("Walking_furafura.fbx");
}


void Enemy::Update()
{
}

void Enemy::Draw()
{
}

void Enemy::Release()
{
}
