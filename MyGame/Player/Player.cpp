//
//プレイヤークラス
//
//2017/11/30
//Ito Motoya
#include "Player.h"

#include "..//MyMas//MyMas.h"

//内部関数===================================================================


//public関数===================================================================
Player::Player()
{
	m_player.LoadModel(L"Resources/Player.cmo");
	//m_player = new Obj3D();
	m_player.SetTranslation(Vector3(0, 0, 0));
	m_player.SetScale(Vector3(0, 0, 0));

	m_moveFlag.Up = false;
	m_moveFlag.Down = false;
	m_moveFlag.Left = false;
	m_moveFlag.Right = false;
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

void Player::InputHandlerUpdate(KeyboradUtil& keybord)
{
	m_input.HandleInput(*this, keybord);
}

/// <summary>
/// 移動
/// </summary>
/// <param name="gridNam">グリットの数</param>
void Player::Move(int gridNam)
{
	Vector3 pos = m_player.GetTranslation();

	if (m_moveFlag.Up == true)
	{
		m_player.SetTranslation(Vector3(pos.x, pos.y, pos.z - 1));

		m_moveFlag.Up = false;
	}


	if (m_moveFlag.Down == true)
	{
		m_player.SetTranslation(Vector3(pos.x, pos.y, pos.z + 1));

		m_moveFlag.Down = false;
	}


	if (m_moveFlag.Right == true)
	{
		
		m_player.SetTranslation(Vector3(pos.x + 1, pos.y, pos.z));

		m_moveFlag.Right = false;
	}


	if (m_moveFlag.Left == true)
	{
		m_player.SetTranslation(Vector3(pos.x - 1, pos.y, pos.z));
		
		m_moveFlag.Left = false;
	}
	/*m_map->SetFlagMap(m_playerColor, m_player.GetTranslation(), *m_CountDice);*/
}

/// <summary>
/// moveFlagのフラグをチェックする
/// </summary>
/// <returns>moveFlagの中のフラグが一つでもtrueならtrueそうでなければfalse</returns>
bool Player::ThcekMoveFlag()
{
	if (m_moveFlag.Up || m_moveFlag.Down || m_moveFlag.Right || m_moveFlag.Left)
	{
		return true;
	}

	return false;
}

void Player::CreatePlayer(int grid)
{
	switch (m_PlayerNamber)
	{
	case 0:
		m_player.LoadModel(L"Resources/Player.cmo");
		m_player.SetTranslation(Vector3(-(grid / 2), 0.5, -(grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_myColor = FLAGMAP_TIP::RED;

		break;
	case 1:
		m_player.LoadModel(L"Resources/Player2.cmo");
		m_player.SetTranslation(Vector3((grid / 2), 0.5, -(grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_myColor = FLAGMAP_TIP::BLUE;

		break;
	case 2:
		m_player.LoadModel(L"Resources/Player3.cmo");
		m_player.SetTranslation(Vector3(-(grid / 2), 0.5, (grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_myColor = FLAGMAP_TIP::GREEN;

		break;
	case 3:
		m_player.LoadModel(L"Resources/Player4.cmo");
		m_player.SetTranslation(Vector3((grid / 2), 0.5, (grid / 2)));//全体の半分から全体の半分の-1した数と0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		m_myColor = FLAGMAP_TIP::YELLOW;

		break;
	}
}

void Player::ResetMoveKey(MOVE_KEY key)
{
	switch (key)
	{
	case MOVE_KEY::UP:
		m_moveFlag.Up = false;
		break;

	case MOVE_KEY::DOWN:
		m_moveFlag.Down = false;
		break;

	case MOVE_KEY::RIGHT:
		m_moveFlag.Right = false;
		break;

	case MOVE_KEY::LEFT:
		m_moveFlag.Left = false;
		break;
	}
}

MOVE_KEY Player::GetMoveKey()
{
	if (m_moveFlag.Up == true)
	{
		return MOVE_KEY::UP;
	}


	if (m_moveFlag.Down == true)
	{
		return MOVE_KEY::DOWN;
	}


	if (m_moveFlag.Right == true)
	{
		return MOVE_KEY::RIGHT;
	}


	if (m_moveFlag.Left == true)
	{
		return MOVE_KEY::LEFT;
	}

	return MOVE_KEY::NOT;
}
