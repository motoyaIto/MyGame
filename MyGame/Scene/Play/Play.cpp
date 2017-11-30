//
//playシーン
//
//2017/11/27
//Ito Motoya
#include "Play.h"

Play::Play()
{
	Scene::m_camera = new DebugCamera(Scene::s_width, Scene::s_height);

	Obj3D::InitializeStatic(Scene::m_camera);

	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());

	m_map = new MAP();
	m_grid = new Grid();
	m_glound = new Glound();

	//デバック用////////////////////////////////////////////////////////////////
	//テキストの初期化
	Scene::m_text = new Text();
	Scene::m_text->SetPos(DirectX::SimpleMath::Vector2(0, 0));
	////////////////////////////////////////////////////////////////////////////
}

Play::~Play()
{
	delete m_map;
	delete m_grid;

	Scene::~Scene();
}

void Play::Initialize()
{
	m_map->Initialize();

	m_grid->SetWonRowNam(m_map->GetGridNam());
	m_grid->Initialize();

	m_glound->SetWonRowNam(m_map->GetGridNam());
	m_glound->Initialize();
}

void Play::Update()
{
	MouseCircumference::GetInstans()->Update();
	m_camera->Update();

	m_map->Update();

	m_grid->SetProj(m_camera->GetProj());
	m_grid->SetView(m_camera->GetView());
	m_grid->Update();


}

void Play::Render()
{
	//カメラ
	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());
	m_effect->SetWorld(m_camera->GetWorld());

	m_effect->Apply(DirectXResourse::m_d3dContext.Get());
	DirectXResourse::m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_glound->Render();
	m_map->Render();
	m_grid->Render(); 

	//デバック用////////////////////////////////////////////////////////////////
	//シーン名を表示
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}
