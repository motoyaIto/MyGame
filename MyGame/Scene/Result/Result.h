//
//リザルトシーン
//
//2017/4/01
//Ito Motoya
#pragma once

#include "..//Scene.h"

class Result : public Scene
{
private:
	DirectX::Keyboard::State m_oldKeyState;

public:

	Result();
	~Result();

	void Initialize() override;
	void Update() override;
	void Render() override;
};