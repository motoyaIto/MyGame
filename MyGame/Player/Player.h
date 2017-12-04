//
//プレイヤークラス
//
//2017/11/30
//Ito Motoya
#pragma once
#include <d3d11_1.h>

#include <SimpleMath.h>

#include "..//DirectXResourse//Obj3D//Obj3D.h"

class Player
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

private:
	Obj3D m_player;

public:
	Player();
	~Player();

	void Initialize();
	void Update();
	void Render();

public://getter

public://setter
	void SetTranslation(Vector3 pos) { m_player.SetTranslation(pos); }
	void SetScale(Vector3 scale) { m_player.SetScale(scale); }

};