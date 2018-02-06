//
//playシーン
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
	//カメラ
	Scene::m_camera = new DebugCamera(Scene::s_width, Scene::s_height);

	//オブジェクトのスタティック
	Obj3D::InitializeStatic(Scene::m_camera);

	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());

	//デバック用////////////////////////////////////////////////////////////////
	//テキストの初期化
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
	//マップ
	m_map.Initialize();

	int gridNam = m_map.GetGridNam();

	//グリット
	m_grid.SetWonRowNam(gridNam);
	m_grid.Initialize();

	//グラウンド
	m_glound.SetWonRowNam(gridNam);
	m_glound.Initialize();

	//プレイヤー
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

	//サイコロ
	/*m_dice.roll();
	m_countDice = m_dice.GetNumber();
	m_player.SetCountDice(m_countDice);*/
	
}

void Play::Update()
{
	static int count = 0;
	int dicenamber = 0;

	//キーボード
	m_keyTracker.Update(m_keyboard->GetState());
	
	//マウス
	MouseCircumference::GetInstans()->Update();
	//カメラ
	m_camera->Update();

	//マップ
	m_map.Update();

	//グリット
	m_grid.SetProj(m_camera->GetProj());
	m_grid.SetView(m_camera->GetView());
	m_grid.Update();
	
	//プレイヤー
	for (int i = 0; i < PLAYERNAM; i++)
	{
		if (m_playerState[i].playing == true)
		{
			m_player[i].InputHandlerUpdate(*m_keyboard);

			switch (m_gameManager)
			{
			case ROLLDICE://サイコロを振る

				m_countDice = 0;

				//サイコロが1つの場合
				if (m_playerState[i].RollTwoDice == false)
				{
					m_dice[0].roll();
					m_countDice = m_dice[0].GetNumber();
					
				}
				else//サイコロが2つの場合
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
					//サイコロの目の数を登録
					m_player[i].SetCountDice(m_countDice);

					m_gameManager = MOVESERECT;

					m_countTime = 0;
				}				
				break;
			case MOVESERECT://移動先を選ぶ
				break;
			case MOVE://移動
				break;

			case MAPGIMMICK://ギミック
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
	//カメラ
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
	//デバック用////////////////////////////////////////////////////////////////
	//シーン名を表示
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}
