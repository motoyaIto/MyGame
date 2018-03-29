//
//play�V�[��
//
//2017/11/27
//Ito Motoya
#include "Play.h"

#include <string.h>

#include "..//..//Constant//Constant.h"

const int Play::PLAYERNAM = 4;

//private�֐�========================================================================================
/// <summary>
/// ���̈ړ���̃f�[�^�̈ʒu���v�Z���邽�߂̒l���o��
/// </summary>
/// <param name="player">�v���C���[</param>
/// <returns>�v�Z���邽�߂̒l</returns>
int Play::ValueToCalculateNextData(Player& player)
{
	switch (player.GetMoveKey())
	{
	case MOVE_KEY::UP:
		return -m_map.GetGridNam();
		break;

	case MOVE_KEY::DOWN:
		return m_map.GetGridNam();
		break;

	case MOVE_KEY::RIGHT:
		return 1;
		break;

	case MOVE_KEY::LEFT:
		return -1;
		break;
	}

	return 0;
}

/// <summary>
/// �ړ��ł��邩�m�F����
/// </summary>
/// <param name="player">�m�F����v���C���[</param>
/// <returns>�ړ��ł���(true)�o���Ȃ�(false)</returns>
bool Play::MoveChecker(Player& player, int datapos)
{
	Vector3 pos = player.GetPosition();

	switch (player.GetMoveKey())
	{
	case MOVE_KEY::UP:
		//��
		if (-(m_map.GetGridNam() / 2) >= pos.z)
		{
			this->ResetPlayerMove(player, MOVE_KEY::UP, Vector3(pos.x, pos.y, pos.z));

			return false;
		}
		
		//�G
		if (m_flag[datapos].GetFlagType() != FLAGMAP_TIP::NONE && m_flag[datapos].GetFlagType() != player.GetPlayerColor())
		{
			this->ResetPlayerMove(player, MOVE_KEY::UP, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		break;

	case MOVE_KEY::DOWN:
		//��
		if (m_map.GetGridNam() / 2 <= pos.z)
		{
			this->ResetPlayerMove(player, MOVE_KEY::DOWN, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		//�G
		if (m_flag[datapos].GetFlagType() != FLAGMAP_TIP::NONE&& m_flag[datapos].GetFlagType() != player.GetPlayerColor())
		{
			this->ResetPlayerMove(player, MOVE_KEY::DOWN, Vector3(pos.x, pos.y, pos.z));

			return false;
		}
		break;

	case MOVE_KEY::RIGHT:
		//��
		if (m_map.GetGridNam() / 2 <= pos.x)
		{
			this->ResetPlayerMove(player, MOVE_KEY::RIGHT, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		//�G
		if (m_flag[datapos].GetFlagType() != FLAGMAP_TIP::NONE&& m_flag[datapos].GetFlagType() != player.GetPlayerColor())
		{
			this->ResetPlayerMove(player, MOVE_KEY::RIGHT, Vector3(pos.x, pos.y, pos.z));

			return false;
		}
		break;

	case MOVE_KEY::LEFT:
		if (-(m_map.GetGridNam() / 2) >= pos.x)
		{
			this->ResetPlayerMove(player, MOVE_KEY::LEFT, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		//�G
		if (m_flag[datapos].GetFlagType() != FLAGMAP_TIP::NONE&& m_flag[datapos].GetFlagType() != player.GetPlayerColor())
		{
			this->ResetPlayerMove(player, MOVE_KEY::LEFT, Vector3(pos.x, pos.y, pos.z));

			return false;
		}
		break;
	}

	return true;
}

/// <summary>
/// �m�F�����v���C���[�̈ړ����Ȃ��ɂ���
/// </summary>
/// <param name="player">�m�F�����v���C���[</param>
/// <param name="key">�I������Ă����ړ���</param>
/// <param name="resetPos">�Ȃ��ɂ��Ė߂�Ƃ��̍��W</param>
void Play::ResetPlayerMove(Player& player, MOVE_KEY key, Vector3 resetPos)
{
		player.ResetMoveKey(key);

		player.SetTranslation(Vector3(resetPos));
}

//public�֐�========================================================================================

Play::Play()
	: m_gameManager(ROLLDICE)
{
	//�J����
	Scene::m_camera = new DebugCamera(Scene::s_width, Scene::s_height);

	//�I�u�W�F�N�g�̃X�^�e�B�b�N
	Obj3D::InitializeStatic(Scene::m_camera);

	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());

	//�f�o�b�N�p////////////////////////////////////////////////////////////////
	//�e�L�X�g�̏�����
	Scene::m_text = new Text();
	Scene::m_text->SetPos(DirectX::SimpleMath::Vector2(0, 0));
	////////////////////////////////////////////////////////////////////////////
}

Play::~Play()
{
	Scene::~Scene();
}

void Play::Initialize()
{
	//�}�b�v
	m_map.Initialize();

	int gridNam = m_map.GetGridNam();

	//�t���O
	m_flag = new Flag[gridNam * gridNam];

	//�O���b�g
	m_grid.SetWonRowNam(gridNam);
	m_grid.Initialize();

	//�O���E���h
	m_glound.SetWonRowNam(gridNam);
	m_glound.Initialize();

	//�v���C���[
	m_player = new Player[PLAYERNAM]();
	m_playerState = new PlayerState[PLAYERNAM]();

	for (int i = 0; i < PLAYERNAM; i++)
	{
		m_player[i].SetPlayerNamber(i);
		m_player[i].CreatePlayer(gridNam);
		m_player[i].Initialize();

		//�����ʒu�Ɋ������
		Vector3 playerPos = m_player[i].GetPosition();//�v���C���[�̍��̃|�W�V����

		int gritNamHalf = m_map.GetGridNam() / 2;		//��񓖂���̃}�X�̐��̔���
		int datapos = gritNamHalf + m_player[i].GetPosition().x + (((gritNamHalf + m_player[i].GetPosition().z)) * m_map.GetGridNam());//�ꎟ���z��̈ʒu

		float x = datapos % m_map.GetGridNam() - gritNamHalf;//x���W
		float y = 0;//y���W
		if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT1)
		{
			y = 0.5;
		}

		if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT2)
		{
			y = 1.0f;
		}
		float z = datapos / m_map.GetGridNam() - (m_map.GetGridNam() / 2);//z���W

		//�����̃t���O�𗧂Ă�
		m_flag[datapos].CreateFlag(m_player[i].GetPlayerColor(), x, y, z);
	}

	m_playerState[0].playing = true;

	
	
	
	//�T�C�R��
	/*m_dice.roll();
	m_countDice = m_dice.GetNumber();
	m_player.SetCountDice(m_countDice);*/
	
}

void Play::Update()
{
	//�}�E�X
	MouseCircumference::GetInstans()->Update();
	//�J����
	m_camera->Update();

	//�}�b�v
	m_map.Update();

	//�O���b�g
	m_grid.SetProj(m_camera->GetProj());
	m_grid.SetView(m_camera->GetView());
	m_grid.Update();
	
	//�v���C���[
	for (int i = 0; i < PLAYERNAM; i++)
	{
		//�v���C���̃v���C���[��T��
		if (m_playerState[i].playing == true)
		{
			static int countTime = 0;

			int DecreaseDice = 1;//�T�C�R���̌��炷��
			Vector3 playerPos = m_player[i].GetPosition();//�v���C���[�̍��̃|�W�V����

			
			int gritNamHalf = m_map.GetGridNam() / 2;		//��񓖂���̃}�X�̐��̔���
			int datapos = gritNamHalf + m_player[i].GetPosition().x + (((gritNamHalf + m_player[i].GetPosition().z)) * m_map.GetGridNam());//�ꎟ���z��̈ʒu

			float x = datapos % m_map.GetGridNam() - gritNamHalf;//x���W
			float y = 0;//y���W
			if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT1)
			{
				y = 0.5;
			}

			if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT2)
			{
				y = 1.0f;
			}
			float z = datapos / m_map.GetGridNam() - (m_map.GetGridNam() / 2);//z���W

			//���v���C���Ă��郂�[�h
			switch (m_gameManager)
			{
			case ROLLDICE://�T�C�R����U��
				m_countDice = 0;

				//�T�C�R����1�̏ꍇ
				if (m_playerState[i].RollTwoDice == false)
				{
					m_dice[0].roll();
					m_countDice = m_dice[0].GetNumber();
					
				}
				else//�T�C�R����2�̏ꍇ
				{
					for (int i = 0; i < DICENAM; i++)
					{
						m_dice[i].roll();

						m_countDice += m_dice[i].GetNumber();
					}
				}

				countTime++;

				if (countTime / 60 >= 2)
				{
					m_gameManager = MOVESERECT;

					countTime = 0;
				}				
				break;
			case MOVESERECT://�ړ����I��
				//�L�[�{�[�h
				m_keyTracker.Update(m_keyboard->GetState());
				m_player[i].InputHandlerUpdate(*m_keyboard);

				//�ړ��悪�I�΂�Ă��Ȃ�
				if (!m_player[i].ThcekMoveFlag())
				{
					m_player[i].InputHandlerUpdate(*m_keyboard);
				}
				else
				{
					m_gameManager = MOVE;
				}
				
				
				break;
			case MOVE://�ړ�

				datapos += this->ValueToCalculateNextData(m_player[i]);//���̃f�[�^���W���v�Z����

				//�ړ��ł��邩�m�F����
				if (!this->MoveChecker(m_player[i], datapos))
				{
					m_gameManager = MAPGIMMICK;

					break;
				}

				x = datapos % m_map.GetGridNam() - gritNamHalf;//x���W
				z = datapos / m_map.GetGridNam() - (m_map.GetGridNam() / 2);//z���W

				//�t���O�������Ă��Ȃ��ꍇ
				if (m_flag[datapos].GetFlagType() == FLAGMAP_TIP::NONE)
				{
					m_player[i].Move(m_map.GetGridNam());
					//�����̃t���O�𗧂Ă�
					m_flag[datapos].CreateFlag(m_player[i].GetPlayerColor(), x, y, z);
				}
				else
				{
					//�����̃t���O�̏ꍇ�ړ��ɂ�����R�X�g������炷
					if (m_flag[datapos].GetFlagType() == m_player[i].GetPlayerColor())
					{
						m_player[i].Move(m_map.GetGridNam());

						DecreaseDice -= 1;
					}
				}

				

				m_gameManager = MAPGIMMICK;

				m_countDice -= DecreaseDice;
				break;

			case MAPGIMMICK://�M�~�b�N
				
				if (m_countDice < 1)
				{
					//���̃v���C���[�Ɍ�シ��
					for (int i = 0; i < PLAYERNAM; i++)
					{
						if (m_playerState[i].playing == true)
						{
							m_playerState[i].playing = false;

							if (i + 1 >= PLAYERNAM)
							{
								m_playerState[0].playing = true;

								break;
							}
							m_playerState[i + 1].playing = true;

							break;
						}
					}

					m_gameManager = ROLLDICE;
				}
				else
				{
					m_gameManager = MOVESERECT;
				}
				break;
			}
		}
	}

	
	for (int i = 0; i < PLAYERNAM; i++)
	{
		m_player[i].Update();
	}

	//��
	for (int i = 0; i < m_map.GetGridNam() * m_map.GetGridNam(); i++)
	{
		m_flag[i].Update();
	}
}

void Play::Render()
{
	//�J����
	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());
	m_effect->SetWorld(m_camera->GetWorld());

	m_effect->Apply(DirectXResourse::m_d3dContext.Get());
	DirectXResourse::m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	//��
	m_glound.Render();
	//�}�b�v
	m_map.Render();
	//�}�X��
	m_grid.Render(); 

	//�v���C���[	
	for (int i = 0; i < PLAYERNAM; i++)
	{
		m_player[i].Render();

		//�s������v���C���[�Ȃ��
		if (m_playerState[i].playing == true)
		{
			//�T�C�R���̕\��
			if (m_playerState[i].RollTwoDice == false)
			{
				m_dice[0].SetDiceNamber(m_countDice);
				m_dice[0].Render();
			}
			else
			{
				for (int i = 0; i < DICENAM; i++)
				{
					m_dice[i].SetDiceNamber(m_countDice);
					m_dice[i].Render();
				}
			}
		}
	}

	//��
	for (int i = 0; i < m_map.GetGridNam() * m_map.GetGridNam(); i++)
	{
		m_flag[i].Render();
	}

	//�f�o�b�N�p////////////////////////////////////////////////////////////////
	//�V�[������\��
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}



