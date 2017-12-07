//
//プレイヤークラス
//
//2017/11/30
//Ito Motoya
#pragma once
#include "ButtonComand//Comand//Comand.h"

#include <d3d11_1.h>

#include <SimpleMath.h>


#include "ButtonComand//ButtonComand.h"
#include "..//DirectXResourse//Obj3D//Obj3D.h"
#include "..//MAP//MAP.h"


class Player : public Actor
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

private:
	Obj3D m_player;//プレイヤー

	int* m_CountDice;

	MAP* m_map;
	//キー設定
	InputHandler m_input;

	UpComand m_upComand;
	DownComand m_DownComand;
	RightComand m_RightComand;
	LeftComand m_LeftComand;

private:
	float TakePosY(Vector3 MovePos);
public:
	Player();
	~Player();

	void Initialize();
	void Update();
	void Render();

	void InputHandlerUpdate(DirectX::Keyboard& keybord);

public://getter
	Vector3 GetPosition() { m_player.GetTranslation(); }
public://setter
	void SetTranslation(Vector3 pos) { m_player.SetTranslation(pos); }
	void SetScale(Vector3 scale) { m_player.SetScale(scale); }
	void SetMap(MAP* map) { m_map = map; }
	void SetCountDice(int& countDice) { m_CountDice = &countDice; }


public://コマンド

	   //上移動コマンド
	void Up() override
	{
		Vector3 pos = m_player.GetTranslation();
		if (-(m_map->GetGridNam() / 2) < pos.z)
		{
			float posY = this->TakePosY(Vector3(0, 0, -1));
			m_player.SetTranslation(Vector3(pos.x, posY, pos.z - 1));

			m_map->SetFlagMap(MAP::RED, m_player.GetTranslation());

			(*m_CountDice)--;
		}
	}

	//下移動コマンド
	void Down() override
	{
		Vector3 pos = m_player.GetTranslation();
		if (m_map->GetGridNam() / 2 > pos.z)
		{
			float posY = this->TakePosY(Vector3(0, 0, 1));
			m_player.SetTranslation(Vector3(pos.x, posY, pos.z + 1));

			m_map->SetFlagMap(MAP::RED, m_player.GetTranslation());

			(*m_CountDice)--;
		}
	}

	//右移動コマンド
	void Right() override
	{
		Vector3 pos = m_player.GetTranslation();
		if (m_map->GetGridNam() / 2 > pos.x)
		{
			float posY = this->TakePosY(Vector3(1, 0, 0));
			m_player.SetTranslation(Vector3(pos.x + 1, posY, pos.z));

			m_map->SetFlagMap(MAP::RED, m_player.GetTranslation());

			(*m_CountDice)--;
		}
	}

	//左移動コマンド
	void Left() override
	{
		Vector3 pos = m_player.GetTranslation();

		if (-(m_map->GetGridNam() / 2) < pos.x)
		{
			float posY = this->TakePosY(Vector3(-1, 0, 0));
			m_player.SetTranslation(Vector3(pos.x - 1, posY, pos.z));

			m_map->SetFlagMap(MAP::RED, m_player.GetTranslation());

			(*m_CountDice)--;
		}
	}
};