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

	, m_RedFlag(nullptr), m_BlueFlag(nullptr)
	, m_GreenFlag(nullptr), m_yerowllFlag(nullptr)
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

	//フラグマップ
	m_flagMAP = new FLAGMAP_TIP[gridNam * gridNam];

	for (int i = 0; i < gridNam * gridNam; i++)
	{
		m_flagMAP[i] = FLAGMAP_TIP::NONE;
	}
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
	}

	m_playerState[0].playing = true;

	//フラグ
	m_RedFlag = new Obj3D;
	
	//サイコロ
	/*m_dice.roll();
	m_countDice = m_dice.GetNumber();
	m_player.SetCountDice(m_countDice);*/
	
}

void Play::Update()
{
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
		//プレイ中のプレイヤーを探す
		if (m_playerState[i].playing == true)
		{
			static int countTime = 0;

			//今プレイしているモード
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

				countTime++;

				if (countTime / 60 >= 2)
				{
					m_gameManager = MOVESERECT;

					countTime = 0;
				}				
				break;
			case MOVESERECT://移動先を選ぶ
				//キーボード
				m_keyTracker.Update(m_keyboard->GetState());
				m_player[i].InputHandlerUpdate(*m_keyboard);

				//移動先が選ばれていない
				if (!m_player[i].ThcekMoveFlag())
				{
					m_player[i].InputHandlerUpdate(*m_keyboard);
				}
				else
				{
					m_gameManager = MOVE;
				}
				
				
				break;
			case MOVE://移動
				m_player[i].Move(m_map.GetGridNam());

				m_gameManager = MAPGIMMICK;

				m_countDice--;

				break;

			case MAPGIMMICK://ギミック
				
				if (m_countDice < 1)
				{
					//次のプレイヤーに交代する
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
