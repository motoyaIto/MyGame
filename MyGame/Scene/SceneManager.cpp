//
//シーンマネージャー
//
//2017/11/27
//Ito Motoya
#include "SceneManager.h"

#include "Play//Play.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	delete m_scene;
}

void SceneManager::Initialize()
{
	m_scene = new Play();
	m_scene->Initialize();
}

void SceneManager::Update()
{
	m_scene->Update();
}

void SceneManager::Render()
{
	m_scene->Render();
}
