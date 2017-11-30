//
//シーンマネージャー
//
//2017/11/27
//Ito Motoya
#pragma once

#include "Scene.h"


class SceneManager
{
private:
	Scene* m_scene;

public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update();
	void Render();


};