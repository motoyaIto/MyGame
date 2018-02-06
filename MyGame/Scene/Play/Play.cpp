//
//play�V�[��
//
//2017/11/27
//Ito Motoya
#include "Play.h"

#include <string.h>

const int Play::PLAYERNAM = 4;

Play::Play()
	: m_gameManager(ROLLDICE)
	, m_countTime(0)
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

		m_player[i].SetMap(&m_map);

		m_playerState[i].playing = false;
		m_playerState[i].RollTwoDice = false;
	}

	m_playerState[0].playing = true;

	//�T�C�R��
	/*m_dice.roll();
	m_countDice = m_dice.GetNumber();
	m_player.SetCountDice(m_countDice);*/
	
}

void Play::Update()
{
	static int count = 0;
	int dicenamber = 0;

	//�L�[�{�[�h
	m_keyTracker.Update(m_keyboard->GetState());
	
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
		if (m_playerState[i].playing == true)
		{
			m_player[i].InputHandlerUpdate(*m_keyboard);

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

				m_countTime++;

				if (m_countTime / 60 >= 2)
				{
					//�T�C�R���̖ڂ̐���o�^
					m_player[i].SetCountDice(m_countDice);

					m_gameManager = MOVESERECT;

					m_countTime = 0;
				}				
				break;
			case MOVESERECT://�ړ����I��
				break;
			case MOVE://�ړ�
				break;

			case MAPGIMMICK://�M�~�b�N
				break;
			}
		}
	}

	

	for (int i = 0; i < PLAYERNAM; i++)
	{
		m_player[i].Update();
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

	m_glound.Render();
	m_map.Render();
	m_grid.Render(); 

	for (int i = 0; i < PLAYERNAM; i++)
	{
		m_player[i].Render();
	}
	
	for (int i = 0; i < PLAYERNAM; i++)
	{
		if (m_playerState[i].playing == true)
		{
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
	//�f�o�b�N�p////////////////////////////////////////////////////////////////
	//�V�[������\��
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}
