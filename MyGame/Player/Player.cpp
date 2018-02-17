//
//�v���C���[�N���X
//
//2017/11/30
//Ito Motoya
#include "Player.h"

#include "..//MyMas//MyMas.h"

//�����֐�===================================================================


//public�֐�===================================================================
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
	//�L�[�ݒ�
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

/// <summary>
/// �ړ�
/// </summary>
/// <param name="gridNam">�O���b�g�̐�</param>
void Player::Move(int gridNam)
{
	Vector3 pos = m_player.GetTranslation();

	if (m_moveFlag.Up == true)
	{
		if (-(gridNam / 2) < pos.z)
		{
			m_player.SetTranslation(Vector3(pos.x, pos.y, pos.z - 1));
		}

		m_moveFlag.Up = false;
	}


	if (m_moveFlag.Down == true)
	{
		if (gridNam / 2 > pos.z)
		{
			m_player.SetTranslation(Vector3(pos.x, pos.y, pos.z + 1));
		}

		m_moveFlag.Down = false;
	}


	if (m_moveFlag.Right == true)
	{
		if (gridNam / 2 > pos.x)
		{
			m_player.SetTranslation(Vector3(pos.x + 1, pos.y, pos.z));
		}

		m_moveFlag.Right = false;
	}


	if (m_moveFlag.Left == true)
	{
		if (-(gridNam / 2) < pos.x)
		{
			m_player.SetTranslation(Vector3(pos.x - 1, pos.y, pos.z));
		}

		m_moveFlag.Left = false;
	}
	/*m_map->SetFlagMap(m_playerColor, m_player.GetTranslation(), *m_CountDice);*/
}

/// <summary>
/// moveFlag�̃t���O���`�F�b�N����
/// </summary>
/// <returns>moveFlag�̒��̃t���O����ł�true�Ȃ�true�����łȂ����false</returns>
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
		m_player.SetTranslation(Vector3(-(grid / 2), 0.5, -(grid / 2)));//�S�̂̔�������S�̂̔�����-1��������0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//m_playerColor = MAP::RED;

		break;
	case 1:
		m_player.LoadModel(L"Resources/Player2.cmo");
		m_player.SetTranslation(Vector3((grid / 2), 0.5, -(grid / 2)));//�S�̂̔�������S�̂̔�����-1��������0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//m_playerColor = MAP::GREEN;

		break;
	case 2:
		m_player.LoadModel(L"Resources/Player3.cmo");
		m_player.SetTranslation(Vector3(-(grid / 2), 0.5, (grid / 2)));//�S�̂̔�������S�̂̔�����-1��������0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//m_playerColor = MAP::BLUE;

		break;
	case 3:
		m_player.LoadModel(L"Resources/Player4.cmo");
		m_player.SetTranslation(Vector3((grid / 2), 0.5, (grid / 2)));//�S�̂̔�������S�̂̔�����-1��������0.5
		m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));
		//m_playerColor = MAP::YELLOW;

		break;
	}
}
