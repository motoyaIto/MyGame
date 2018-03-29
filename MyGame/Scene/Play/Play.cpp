//
//playシーン
//
//2017/11/27
//Ito Motoya
#include "Play.h"

#include <string.h>

#include "..//..//Constant//Constant.h"

const int Play::PLAYERNAM = 4;

//private関数========================================================================================
/// <summary>
/// 次の移動先のデータの位置を計算するための値を出す
/// </summary>
/// <param name="player">プレイヤー</param>
/// <returns>計算するための値</returns>
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
/// 移動できるか確認する
/// </summary>
/// <param name="player">確認するプレイヤー</param>
/// <returns>移動できる(true)出来ない(false)</returns>
bool Play::MoveChecker(Player& player, int datapos)
{
	Vector3 pos = player.GetPosition();

	switch (player.GetMoveKey())
	{
	case MOVE_KEY::UP:
		//壁
		if (-(m_map.GetGridNam() / 2) >= pos.z)
		{
			this->ResetPlayerMove(player, MOVE_KEY::UP, Vector3(pos.x, pos.y, pos.z));

			return false;
		}
		
		//敵
		if (m_flag[datapos].GetFlagType() != FLAGMAP_TIP::NONE && m_flag[datapos].GetFlagType() != player.GetPlayerColor())
		{
			this->ResetPlayerMove(player, MOVE_KEY::UP, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		break;

	case MOVE_KEY::DOWN:
		//壁
		if (m_map.GetGridNam() / 2 <= pos.z)
		{
			this->ResetPlayerMove(player, MOVE_KEY::DOWN, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		//敵
		if (m_flag[datapos].GetFlagType() != FLAGMAP_TIP::NONE&& m_flag[datapos].GetFlagType() != player.GetPlayerColor())
		{
			this->ResetPlayerMove(player, MOVE_KEY::DOWN, Vector3(pos.x, pos.y, pos.z));

			return false;
		}
		break;

	case MOVE_KEY::RIGHT:
		//壁
		if (m_map.GetGridNam() / 2 <= pos.x)
		{
			this->ResetPlayerMove(player, MOVE_KEY::RIGHT, Vector3(pos.x, pos.y, pos.z));

			return false;
		}

		//敵
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

		//敵
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
/// 確認したプレイヤーの移動をなしにする
/// </summary>
/// <param name="player">確認したプレイヤー</param>
/// <param name="key">選択されていた移動先</param>
/// <param name="resetPos">なしにして戻るときの座標</param>
void Play::ResetPlayerMove(Player& player, MOVE_KEY key, Vector3 resetPos)
{
		player.ResetMoveKey(key);

		player.SetTranslation(Vector3(resetPos));
}

//public関数========================================================================================

Play::Play()
	: m_gameManager(ROLLDICE)
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

	//フラグ
	m_flag = new Flag[gridNam * gridNam];

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

		//初期位置に旗を作る
		Vector3 playerPos = m_player[i].GetPosition();//プレイヤーの今のポジション

		int gritNamHalf = m_map.GetGridNam() / 2;		//一列当たりのマスの数の半分
		int datapos = gritNamHalf + m_player[i].GetPosition().x + (((gritNamHalf + m_player[i].GetPosition().z)) * m_map.GetGridNam());//一次元配列の位置

		float x = datapos % m_map.GetGridNam() - gritNamHalf;//x座標
		float y = 0;//y座標
		if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT1)
		{
			y = 0.5;
		}

		if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT2)
		{
			y = 1.0f;
		}
		float z = datapos / m_map.GetGridNam() - (m_map.GetGridNam() / 2);//z座標

		//自分のフラグを立てる
		m_flag[datapos].CreateFlag(m_player[i].GetPlayerColor(), x, y, z);
	}

	m_playerState[0].playing = true;

	
	
	
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

			int DecreaseDice = 1;//サイコロの減らす数
			Vector3 playerPos = m_player[i].GetPosition();//プレイヤーの今のポジション

			
			int gritNamHalf = m_map.GetGridNam() / 2;		//一列当たりのマスの数の半分
			int datapos = gritNamHalf + m_player[i].GetPosition().x + (((gritNamHalf + m_player[i].GetPosition().z)) * m_map.GetGridNam());//一次元配列の位置

			float x = datapos % m_map.GetGridNam() - gritNamHalf;//x座標
			float y = 0;//y座標
			if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT1)
			{
				y = 0.5;
			}

			if (m_map.GetMapDate(datapos) == MAP::MAP_NAME::MOUNT2)
			{
				y = 1.0f;
			}
			float z = datapos / m_map.GetGridNam() - (m_map.GetGridNam() / 2);//z座標

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

				datapos += this->ValueToCalculateNextData(m_player[i]);//次のデータ座標を計算する

				//移動できるか確認する
				if (!this->MoveChecker(m_player[i], datapos))
				{
					m_gameManager = MAPGIMMICK;

					break;
				}

				x = datapos % m_map.GetGridNam() - gritNamHalf;//x座標
				z = datapos / m_map.GetGridNam() - (m_map.GetGridNam() / 2);//z座標

				//フラグが立っていない場合
				if (m_flag[datapos].GetFlagType() == FLAGMAP_TIP::NONE)
				{
					m_player[i].Move(m_map.GetGridNam());
					//自分のフラグを立てる
					m_flag[datapos].CreateFlag(m_player[i].GetPlayerColor(), x, y, z);
				}
				else
				{
					//自分のフラグの場合移動にかかるコストを一つ減らす
					if (m_flag[datapos].GetFlagType() == m_player[i].GetPlayerColor())
					{
						m_player[i].Move(m_map.GetGridNam());

						DecreaseDice -= 1;
					}
				}

				

				m_gameManager = MAPGIMMICK;

				m_countDice -= DecreaseDice;
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

	//旗
	for (int i = 0; i < m_map.GetGridNam() * m_map.GetGridNam(); i++)
	{
		m_flag[i].Update();
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

	//床
	m_glound.Render();
	//マップ
	m_map.Render();
	//マス目
	m_grid.Render(); 

	//プレイヤー	
	for (int i = 0; i < PLAYERNAM; i++)
	{
		m_player[i].Render();

		//行動するプレイヤーならば
		if (m_playerState[i].playing == true)
		{
			//サイコロの表示
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

	//旗
	for (int i = 0; i < m_map.GetGridNam() * m_map.GetGridNam(); i++)
	{
		m_flag[i].Render();
	}

	//デバック用////////////////////////////////////////////////////////////////
	//シーン名を表示
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}



