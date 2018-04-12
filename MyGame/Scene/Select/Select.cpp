//
//セレクトシーン
//
//2017/4/01
//Ito Motoya
#include "Select.h"
#include <Keyboard.h>

Select::Select()
	: Scene()
{
	//デバック用////////////////////////////////////////////////////////////////
	//テキストの初期化
	Scene::m_text = new Text();
	Scene::m_text->SetPos(DirectX::SimpleMath::Vector2(0, 0));
	////////////////////////////////////////////////////////////////////////////
}

Select::~Select()
{

}

void Select::Initialize()
{
}

void Select::Update()
{
	//キーボード
	m_keyTracker.Update(m_keyboard->GetState());

	DirectX::Keyboard::State keyState = m_keyboard->GetState();

	// デバック用////////////////////////////////////////////////////////////////
	//シーン切替
	if (keyState.A && !m_oldKeyState.A)
	{
		m_state = false;
	}
	////////////////////////////////////////////////////////////////////////////
}

void Select::Render()
{
	//デバック用////////////////////////////////////////////////////////////////
	//シーン名を表示
	Scene::m_text->Render(L"SelectScene");
	////////////////////////////////////////////////////////////////////////////
}
