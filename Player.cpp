#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "TestScene.h"
#include "Engine/Input.h"

namespace
{
	enum PLAYER_STATE
	{
		PLAYER_IDLE,
		PLAYER_WALK,
		PLAYER_TURN,
		PLAYER_FLIP,
		PLAYER_STATE_MAX //状態の数
	};
	PLAYER_STATE pstate = PLAYER_STATE::PLAYER_IDLE; //プレイヤーの状態を管理する変数

	enum PLAYER_DIRECTION
	{
		PLAYER_UP,
		PLAYER_DOWN,
		PLAYER_LEFT,
		PLAYER_RIGHT,
		PLAYER_DIRECTION_MAX //方向の数
	};
	PLAYER_DIRECTION pdirection = PLAYER_DOWN;
	float P_ANGLE[4] = { 180,0,90,-90 };
	XMVECTOR P_MOVE[4] = { XMVectorSet(0, 0, 1, 0),
		                   XMVectorSet(0, 0, -1, 0),
	                       XMVectorSet(-1, 0, 0, 0),
	                       XMVectorSet(1, 0, 0, 0) };
	float TURN_FRAME = 0.3f;
}




Player::Player(GameObject* parent)
	:GameObject(parent), hWalkModel_(-1), hIdleModel_(-1), hFlipModel_(-1){
	//swordDirには、初期方向として、ローカルモデルの剣の根っこから
	//先端までのベクトルとして（0,1,0)を代入しておく
	//初期位置は原点
}

void Player::Initialize()
{
	//hSilly = Model::Load("Walking_z.fbx");
	//Model::SetAnimFrame(hSilly, 0, 158, 1.0);

	//hSilly = Model::Load("Thriller Part 2.fbx");
	//Model::SetAnimFrame(hSilly, 0, 1130, 1.0);

	hWalkModel_ = Model::Load("Walking_furafura.fbx");
	Model::SetAnimFrame(hWalkModel_, 0, 91, 1.0);

	hIdleModel_ = Model::Load("Idle.fbx");
	Model::SetAnimFrame(hIdleModel_, 0, 500, 1.0);

	hFlipModel_ = Model::Load("Backflip.fbx");
	Model::SetAnimFrame(hFlipModel_, 0, 129, 1.0);

}

void Player::Update()
{
	//transform_.rotate_.y +=1;
	//static float angle = 0.0;
	//angle = angle + 0.3f;
	//XMMATRIX scale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	//XMMATRIX rotateX = XMMatrixRotationX(XMConvertToRadians(angle));
	//XMMATRIX rotate = XMMatrixRotationY(XMConvertToRadians(angle));
	//XMMATRIX translate = XMMatrixTranslation(1.0f, 0.0f, 0.0f);

	//SetWorldMatrix(scale *  rotate * translate);

	XMVECTOR pos = XMLoadFloat3(&transform_.position_);
	XMVECTOR move = XMVectorSet(0, 0, 0, 0);
	const float SPEED = 0.015f;
	float angle = 0.0f;
	pstate = PLAYER_STATE::PLAYER_IDLE;
	PLAYER_DIRECTION oldDir = pdirection;

	if (Input::IsKey(DIK_UP))
	{
		//angle = 180.0f;
		//move = XMVectorSet(0, 0, 1, 0);

		pdirection = PLAYER_DIRECTION::PLAYER_UP;
		pstate = PLAYER_STATE::PLAYER_WALK;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		//angle = 0.0f;
		//move = XMVectorSet(0, 0, -1, 0);
		
		pdirection = PLAYER_DIRECTION::PLAYER_DOWN;
		pstate = PLAYER_STATE::PLAYER_WALK;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		//angle = 90.0f;
		//move = XMVectorSet(-1, 0, 0, 0);
		
		pdirection = PLAYER_DIRECTION::PLAYER_LEFT;
		pstate = PLAYER_STATE::PLAYER_WALK;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		//angle = -90.0f;
		//move = XMVectorSet(1, 0, 0, 0);
		
		pdirection = PLAYER_DIRECTION::PLAYER_RIGHT;
		pstate = PLAYER_STATE::PLAYER_WALK;
	}

	if (oldDir != pdirection)
	{
		pstate = PLAYER_STATE::PLAYER_TURN;
	}

	if (pstate != PLAYER_STATE::PLAYER_IDLE)
	{
		move = P_MOVE[pdirection];
		angle = P_ANGLE[pdirection];
		transform_.rotate_.y = angle;
	}
	else if (pstate == PLAYER_STATE::PLAYER_TURN)
	{
		//回転中の処理

		//30フレームで回転するようにする

	}

		pos = pos + move * SPEED;
	XMStoreFloat3(&transform_.position_, pos);
	//pos = XMVectorAdd(pos, SPEED * move);

	if (Input::IsKeyDown(DIK_B))
	{
		pstate = PLAYER_STATE::PLAYER_FLIP;
	}
}

void Player::Draw()
{
	//transform_.scale_ = { 0.01,0.01,0.01 };
	//transform_.position_ = { 0, 0.0, 0 };
	if (pstate == PLAYER_STATE::PLAYER_IDLE)
	{
		Model::SetTransform(hIdleModel_, transform_);
		Model::Draw(hIdleModel_);
	}
	else if (pstate == PLAYER_STATE::PLAYER_WALK)
	{
		Model::SetTransform(hWalkModel_, transform_);
		Model::Draw(hWalkModel_);
	}
	else if (pstate == PLAYER_STATE::PLAYER_FLIP)
	{
		Model::SetTransform(hFlipModel_, transform_);
		Model::Draw(hFlipModel_);
	}
}


void Player::Release()
{
}
