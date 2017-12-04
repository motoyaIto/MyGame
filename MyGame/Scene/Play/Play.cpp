//
//playシーン
//
//2017/11/27
//Ito Motoya
#include "Play.h"

Play::Play()
{
	//カメラ
	Scene::m_camera = new DebugCamera(Scene::s_width, Scene::s_height);

	//オブジェクトのスタティック
	Obj3D::InitializeStatic(Scene::m_camera);

	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());

	//デバック用////////////////////////////////////////////////////////////////
	//テキストの初期化
	Scene::m_text = new Text();
	Scene::m_text->SetPos(DirectX::SimpleMath::Vector2(0, 0));
	////////////////////////////////////////////////////////////////////////////
}

Play::~Play()
{
	Scene::~Scene();
}

void Play::Initialize()
{
	//マップ
	m_map.Initialize();

	int gridNam = m_map.GetGridNam();

	//グリット
	m_grid.SetWonRowNam(gridNam);
	m_grid.Initialize();

	//グラウンド
	m_glound.SetWonRowNam(gridNam);
	m_glound.Initialize();

	//プレイヤー
	m_player.Initialize();
	m_player.SetTranslation(Vector3((1 - gridNam / 2) - 0.5, 0, (gridNam / 2) - 0.5));
	m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));

	//全体の半分から全体の半分の-1した数と0.5
}

void Play::Update()
{
	//マウス
	MouseCircumference::GetInstans()->Update();
	//カメラ
	m_camera->Update();

	//マップ
	m_map.Update();

	//グリット
	m_grid.SetProj(m_camera->GetProj());
	m_grid.SetView(m_camera->GetView());
	m_grid.Update();


	//プレイヤー
	m_player.Update();
	
}

void Play::Render()
{
	//カメラ
	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());
	m_effect->SetWorld(m_camera->GetWorld());

	m_effect->Apply(DirectXResourse::m_d3dContext.Get());
	DirectXResourse::m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_glound.Render();
	m_map.Render();
	m_grid.Render(); 

	m_player.Render();

	//デバック用////////////////////////////////////////////////////////////////
	//シーン名を表示
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}
