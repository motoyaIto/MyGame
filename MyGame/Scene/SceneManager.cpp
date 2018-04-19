//
//シーンマネージャー
//
//2017/11/27
//Ito Motoya
#include "SceneManager.h"

#include "Title//Title.h"
#include "Select//Select.h"
#include "Play//Play.h"
#include "Result//Result.h"


Scene* SceneManager::m_scene;
int SceneManager::m_selected;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	delete m_scene;
}

void SceneManager::Initialize()
{
	this->ChangeScene(SCENE_ID::TITLE);
	
	m_scene->Initialize();
}

void SceneManager::Update()
{
	m_scene->Update();

	if (m_scene->GetState() == false)
	{
		if (m_selected < SCENE_ID::MAX)
		{
			m_selected++;

			this->ChangeScene(m_selected);
		}
		else
		{
			m_selected = 0;

			this->ChangeScene(m_selected);
		}

		m_scene->Initialize();
	}
	
}

void SceneManager::Render()
{
	m_scene->Render();
}

void SceneManager::ChangeScene(int id)
{
	switch (id)
	{
	case SCENE_ID::TITLE:
		m_scene = new Title();
		break;

	case SCENE_ID::SELECT:
		m_scene = new Select();
		break;

	case SCENE_ID::PLAY:
		m_scene = new Play();
		break;

	case SCENE_ID::RESULT:
		m_scene = new Result();
		break;
	}

	m_selected = id;
}
