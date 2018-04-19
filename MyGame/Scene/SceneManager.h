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
	enum SCENE_ID
	{
		TITLE,
		SELECT,
		PLAY,
		RESULT,

		MAX,
	};
	static int m_selected;
	static Scene* m_scene;

public:
	SceneManager();
	~SceneManager();

	void Initialize();
	void Update();
	void Render();

	static void ChangeScene(int id);
};