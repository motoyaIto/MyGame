//
//プレイシーン
//
//2017/4/01
//Ito Motoya
#pragma once
//
//セレクトシーン
//
//2017/4/01
//Ito Motoya
#include "..//Scene.h"

class Select : public Scene
{
private:
	DirectX::Keyboard::State m_oldKeyState;

public:

	Select();
	~Select();

	void Initialize() override;
	void Update() override;
	void Render() override;
};