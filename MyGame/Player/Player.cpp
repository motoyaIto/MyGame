//
//プレイヤークラス
//
//2017/11/30
//Ito Motoya
#include "Player.h"

Player::Player()
{
	//m_player = new Obj3D();
	m_player.LoadModel(L"Resources/Player.cmo");
	m_player.SetTranslation(Vector3(0, 0, 0));
	m_player.SetScale(Vector3(0, 0, 0));
}

Player::~Player()
{
}

void Player::Initialize()
{
}

void Player::Update()
{
	m_player.UpdateO();
}

void Player::Render()
{
	m_player.Render();
}
