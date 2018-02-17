//
//�v���C���[�N���X
//
//2017/11/30
//Ito Motoya
#pragma once
#include "ButtonComand//Comand//Comand.h"

#include <d3d11_1.h>
#include <SimpleMath.h>


#include "ButtonComand//ButtonComand.h"
#include "..//DirectXResourse//Obj3D//Obj3D.h"


class Player : public Actor
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

private:
	struct MoveFlag
	{
		bool Up;
		bool Down;
		bool Right;
		bool Left;
	};

	Obj3D m_player;//�v���C���[
	//MAP::FLAGMAP_TIP m_playerColor;//�v���C���[�J���[
	MoveFlag m_moveFlag;

	//�L�[�ݒ�
	InputHandler m_input;

	UpComand m_upComand;
	DownComand m_DownComand;
	RightComand m_RightComand;
	LeftComand m_LeftComand;

	int m_PlayerNamber;

private:
	
public:
	Player();
	~Player();

	void Initialize();
	void Update();
	void Render();

	void InputHandlerUpdate(DirectX::Keyboard& keybord);

	void Move(int gridNam);

	bool ThcekMoveFlag();

	void CreatePlayer(int grid);

public://getter
	Vector3 GetPosition() { return m_player.GetTranslation(); }
	//MAP::FLAGMAP_TIP GetPlayerColor() { return m_playerColor; }
	
public://setter
	void SetPlayerNamber(int namber) { if(namber < 4)m_PlayerNamber = namber; }
	void SetTranslation(Vector3 pos) { m_player.SetTranslation(pos); }
	void SetScale(Vector3 scale) { m_player.SetScale(scale); }
	//void SetPlayerColor(MAP::FLAGMAP_TIP color) { m_playerColor = color; }

public://�R�}���h

	   //��ړ��R�}���h
	void Up() override
	{
		m_moveFlag.Up = true;
		
	}

	//���ړ��R�}���h
	void Down() override
	{
		m_moveFlag.Down = true;
	}

	//�E�ړ��R�}���h
	void Right() override
	{
		m_moveFlag.Right = true;
	}

	//���ړ��R�}���h
	void Left() override
	{
		m_moveFlag.Left = true;
	}
};