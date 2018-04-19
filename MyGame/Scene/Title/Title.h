//
//タイトルシーン
//
//2017/4/01
//Ito Motoya
#pragma once
#include "..//Scene.h"


class Title : public Scene
{
private:
	

public:

	Title();
	~Title();

	void Initialize() override;
	void Update() override;
	void Render() override;
};