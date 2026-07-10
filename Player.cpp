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
		PLAYER_TURN_NEAR, //180°を超えたとき近いほうから回るように
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
		PLAYER_UP_RIGHT,
		PLAYER_UP_LEFT,
		PLAYER_DOWN_RIGHT,
		PLAYER_DOWN_LEFT,
		PLAYER_DIRECTION_MAX //方向の数
	};
	PLAYER_DIRECTION pdirection = PLAYER_DOWN;
	float P_ANGLE[8] = { 180,0,90,-90,-135,135,-45,45,};
	XMVECTOR P_MOVE[8] = { 
		XMVectorSet(0, 0, 1, 0),
		XMVectorSet(0, 0, -1, 0),
	    XMVectorSet(-1, 0, 0, 0),
	    XMVectorSet(1, 0, 0, 0), 
	    XMVectorSet(1, 0, 1, 0), 
	    XMVectorSet(-1, 0, 1, 0), 
		XMVectorSet(1, 0, -1, 0),
		XMVectorSet(-1, 0, -1, 0),
	};

	float TURN_FRAME = 10.0f;

	float turnStartAngle = 0.0f; //回転開始時の角度を管理する変数
	float turnEndAngle = 0.0f;   //回転終了時の角度を管理する変数
	PLAYER_DIRECTION turnEndDirection = PLAYER_DOWN;

	std::vector<std::vector<int>>gmap;
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

	hIdleModel_ = Model::Load("Zombie Idle.fbx");
	Model::SetAnimFrame(hIdleModel_, 0, 240, 1.0);

	hFlipModel_ = Model::Load("Backflip.fbx");
	Model::SetAnimFrame(hFlipModel_, 0, 129, 1.0);

	if (ground_ != nullptr)
	{
		gmap = ground_->GetMapData();
	}
	else
	{
		Debug::Log("Ground is not set for Player.");
	}

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
	const float SPEED = 0.1f;
	float angle = 0.0f;
	static float turnFrame = 0.0f; //回転中のフレーム数を管理する変数
	
	//バックフリップのエモートを出したい
	//if (Input::IsKeyDown(DIK_B))
	//{
	//	pstate = PLAYER_STATE::PLAYER_FLIP;
	//	return;
	//}
	//if (pstate == PLAYER_STATE::PLAYER_FLIP) 
	//{
	//	if (Model::GetAnimFrame(hFlipModel_) >= 129) { pstate = PLAYER_STATE::PLAYER_IDLE; }
	//}

	if (pstate != PLAYER_STATE::PLAYER_TURN) {
		pstate = PLAYER_STATE::PLAYER_IDLE;
	}//回転中でなければ状態を待機にする

	PLAYER_DIRECTION oldDir = pdirection; // 今の向き



	if (pstate != PLAYER_STATE::PLAYER_TURN)
	{
		//上下左右の移動
		if (Input::IsKey(DIK_UP) || Input::IsKey(DIK_W))
		{
			//angle = 180.0f;
			//move = XMVectorSet(0, 0, 1, 0);

			pdirection = PLAYER_DIRECTION::PLAYER_UP;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_DOWN) || Input::IsKey(DIK_S))
		{
			//angle = 0.0f;
			//move = XMVectorSet(0, 0, -1, 0);

			pdirection = PLAYER_DIRECTION::PLAYER_DOWN;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_LEFT) || Input::IsKey(DIK_A))
		{
			//angle = 90.0f;
			//move = XMVectorSet(-1, 0, 0, 0);

			pdirection = PLAYER_DIRECTION::PLAYER_LEFT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_RIGHT) || Input::IsKey(DIK_D))
		{
			//angle = -90.0f;
			//move = XMVectorSet(1, 0, 0, 0);

			pdirection = PLAYER_DIRECTION::PLAYER_RIGHT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		//斜め移動
		if (Input::IsKey(DIK_UP) && Input::IsKey(DIK_RIGHT) ||
			Input::IsKey(DIK_W) && Input::IsKey(DIK_D))
		{
			pdirection = PLAYER_DIRECTION::PLAYER_UP_RIGHT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_UP) && Input::IsKey(DIK_LEFT) ||
			Input::IsKey(DIK_W) && Input::IsKey(DIK_A))
		{
			pdirection = PLAYER_DIRECTION::PLAYER_UP_LEFT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_DOWN) && Input::IsKey(DIK_RIGHT) ||
			Input::IsKey(DIK_S) && Input::IsKey(DIK_D))
		{
			pdirection = PLAYER_DIRECTION::PLAYER_DOWN_RIGHT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		if (Input::IsKey(DIK_DOWN) && Input::IsKey(DIK_LEFT) ||
			Input::IsKey(DIK_S) && Input::IsKey(DIK_A))
		{
			pdirection = PLAYER_DIRECTION::PLAYER_DOWN_LEFT;
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
	}

	
	//
	if (oldDir != pdirection)
	{
		pstate = PLAYER_STATE::PLAYER_TURN;
		turnFrame = 0.0f;
		turnStartAngle = P_ANGLE[oldDir];
		turnEndDirection = pdirection;
		turnEndAngle = P_ANGLE[turnEndDirection];
	}

	//---------回転方向を最短にする為のところ--------------
	float diffAngle = turnEndAngle - turnStartAngle;

	// 180度を超えて大回りしている場合は補正
	if (diffAngle > 180.0f)
	{
		turnEndAngle -= 360.0f;
	}
	else if (diffAngle < -180.0f)
	{
		turnEndAngle += 360.0f;
	}
	//------------------------------------------------------

	if(pstate == PLAYER_STATE::PLAYER_TURN)
	{
		//回転中の処理
		//oldDir → 今の角度
		//pdirection → 目標角度
		//30フレームで回転するようにする
		turnFrame += 1.0f;
		float t = turnFrame / TURN_FRAME;
		if (t > 1.0f)
		{
			t = 1.0f;
		}
		angle = turnStartAngle + (turnEndAngle - turnStartAngle) * t;
		transform_.rotate_.y = angle;
		if(turnFrame >= TURN_FRAME)
		{
			pdirection = turnEndDirection;
			transform_.rotate_.y = P_ANGLE[pdirection];
			pstate = PLAYER_STATE::PLAYER_WALK;
		}
		return;
	}
	else if (pstate != PLAYER_STATE::PLAYER_IDLE)
	{
		move = P_MOVE[pdirection];
		move = XMVector3Normalize(move); // 正規化をする（1に直す）、これをしないと斜め移動したときにスピードが早くなる
		angle = P_ANGLE[pdirection];
		transform_.rotate_.y = angle;
	}

	pos = pos + move * SPEED;
	//pos = XMVectorAdd(pos, SPEED * move);
	XMStoreFloat3(&transform_.position_, pos);

	//壁オブジェクトに食い込んでいたら戻す！
	//ground_->GetMapData();

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
	else if (pstate == PLAYER_STATE::PLAYER_WALK || pstate == PLAYER_STATE::PLAYER_TURN || pstate == PLAYER_STATE::PLAYER_TURN_NEAR)
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
