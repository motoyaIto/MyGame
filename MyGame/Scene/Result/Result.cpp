//
//リザルトシーン
//
//2017/4/01
//Ito Motoya
#include "Result.h"

Result::Result()
	: Scene()
{
	//デバック用////////////////////////////////////////////////////////////////
	//テキストの初期化
	Scene::m_text = new Text();
	Scene::m_text->SetPos(DirectX::SimpleMath::Vector2(0, 0));
	////////////////////////////////////////////////////////////////////////////
}

Result::~Result()
{

}

void Result::Initialize()
{
}

void Result::Update()
{
	//デバック用////////////////////////////////////////////////////////////////
	//シーン切替
	if (m_keyborad->GetKeyDown(DirectX::Keyboard::Space))
	{
		m_state = false;
	}
	////////////////////////////////////////////////////////////////////////////
}

void Result::Render()
{
	//デバック用////////////////////////////////////////////////////////////////
	//シーン名を表示
	Scene::m_text->Render(L"ResultScene");
	////////////////////////////////////////////////////////////////////////////
}
