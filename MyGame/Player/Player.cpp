//
//プレイヤークラス
//
//2017/11/30
//Ito Motoya
#include "Player.h"

#include "..//MyMas//MyMas.h"

//内部関数===================================================================
float Player::TakePosY(Vector3 MovePos)
{
	int gritNamHalf = m_map->GetGridNam() / 2;		//一列当たりのマスの数の半分
	Vector3 NextPos = m_player.GetTranslation() + MovePos;//次に進む場所の座標

	int mapDataPos = gritNamHalf + NextPos.x + (((gritNamHalf + NextPos.z)) * m_map->GetGridNam());
	int mapdata = m_map->GetMapDate(mapDataPos);

	//高低差が0の場所
	if (mapdata == MAP::POISON_SWAMP || mapdata == MAP::POND)
	{
		mapdata = 0;
	}

	////山
	//if (mapdata == MAP::MOUNT1)
	//{
	//	(*m_CountDice) += (int)m_player.GetTranslation().y - mapdata;
	//}
	//if (mapdata == MAP::MOUNT2)
	//{
	//	(*m_CountDice) += MyMas::RoundUp(m_player.GetTranslation().y) - mapdata;
	//}

	return (mapdata + 1) * 0.5;
}

//public関数===================================================================
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
	//キー設定
	m_input.SetComandUp(&m_upComand);
	m_input.SetComandDown(&m_DownComand);
	m_input.SetComandRight(&m_RightComand);
	m_input.SetComandLeft(&m_LeftComand);
}

void Player::Update()
{
	m_player.UpdateO();
}

void Player::Render()
{
	m_player.Render();
}

void Player::InputHandlerUpdate(DirectX::Keyboard& keybord)
{
	m_input.HandleInput(*this, keybord);
}
