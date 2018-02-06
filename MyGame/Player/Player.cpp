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
	m_player.LoadModel(L"Resources/Player.cmo");
	//m_player = new Obj3D();
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

void Player::Move()
{
	Vector3 pos = m_player.GetTranslation();

	if (m_moveFlag.Up == true)
	{
		if (-(m_map->GetGridNam() / 2) < pos.z)
		{
			float posY = this->TakePosY(Vector3(0, 0, -1));
			m_player.SetTranslation(Vector3(pos.x, posY, pos.z - 1));
		}
	}


	if (m_moveFlag.Down == true)
	{
		if (m_map->GetGridNam() / 2 > pos.z)
		{
			float posY = this->TakePosY(Vector3(0, 0, 1));
			m_player.SetTranslation(Vector3(pos.x, posY, pos.z + 1));
		}
	}


	if (m_moveFlag.Right == true)
	{
		if (m_map->GetGridNam() / 2 > pos.x)
		{
			float posY = this->TakePosY(Vector3(1, 0, 0));
			m_player.SetTranslation(Vector3(pos.x + 1, posY, pos.z));
		}
	}


	if (m_moveFlag.Left == true)
	{
		if (-(m_map->GetGridNam() / 2) < pos.x)
		{
			float posY = this->TakePosY(Vector3(-1, 0, 0));
			m_player.SetTranslation(Vector3(pos.x - 1, posY, pos.z));
		}
	}
	m_map->SetFlagMap(m_playerColor, m_player.GetTranslation(), *m_CountDice);

	(*m_CountDice)--;
}

bool Player::ThcekMoveFlag()
{
	if (!(m_moveFlag.Up && m_moveFlag.Down && m_moveFlag.Right && m_moveFlag.Left))
	{
		return false;
	}

	return true;
}

void Player::CreatePlayer(int grid)
{
	switch (m_PlayerNamber)
	{
	case 0:
		m_player.LoadModel(L"Resources/Player.cmo");
		m_player.SetTranslation(Vector3(-(grid / 2), 0.5, -(grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_playerColor = MAP::RED;

		break;
	case 1:
		m_player.LoadModel(L"Resources/Player2.cmo");
		m_player.SetTranslation(Vector3((grid / 2), 0.5, -(grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_playerColor = MAP::GREEN;

		break;
	case 2:
		m_player.LoadModel(L"Resources/Player3.cmo");
		m_player.SetTranslation(Vector3(-(grid / 2), 0.5, (grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_playerColor = MAP::BLUE;

		break;
	case 3:
		m_player.LoadModel(L"Resources/Player4.cmo");
		m_player.SetTranslation(Vector3((grid / 2), 0.5, (grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_playerColor = MAP::YELLOW;

		break;
	}
}
