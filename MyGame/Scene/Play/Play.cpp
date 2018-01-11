//
//play�V�[��
//
//2017/11/27
//Ito Motoya
#include "Play.h"

#include <string.h>

Play::Play()
{
	//�J����
	Scene::m_camera = new DebugCamera(Scene::s_width, Scene::s_height);

	//�I�u�W�F�N�g�̃X�^�e�B�b�N
	Obj3D::InitializeStatic(Scene::m_camera);

	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());

	//�f�o�b�N�p////////////////////////////////////////////////////////////////
	//�e�L�X�g�̏�����
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
	//�}�b�v
	m_map.Initialize();

	int gridNam = m_map.GetGridNam();

	//�O���b�g
	m_grid.SetWonRowNam(gridNam);
	m_grid.Initialize();

	//�O���E���h
	m_glound.SetWonRowNam(gridNam);
	m_glound.Initialize();

	//�v���C���[
	m_player.Initialize();
	m_player.SetTranslation(Vector3(-(gridNam / 2), 0.5, -(gridNam / 2)));//�S�̂̔�������S�̂̔�����-1��������0.5
	m_player.SetScale(Vector3(1.0f, 1.0f, 1.0f));

	m_player.SetMap(&m_map);
	m_player.SetPlayerColor(MAP::RED);

	//�T�C�R��
	m_dice.roll();
	m_countDice = m_dice.GetNumber();
	m_player.SetCountDice(m_countDice);
	m_diceflag = new bool[4];

	for (int i = 0; i < 4; i++)
	{
		m_diceflag[i] = false;
	}

	m_diceflag[0] = true;
}

void Play::Update()
{
	//�L�[�{�[�h
	m_keyTracker.Update(m_keyboard->GetState());
	
	//�}�E�X
	MouseCircumference::GetInstans()->Update();
	//�J����
	m_camera->Update();

	//�}�b�v
	m_map.Update();

	//�O���b�g
	m_grid.SetProj(m_camera->GetProj());
	m_grid.SetView(m_camera->GetView());
	m_grid.Update();


	//�v���C���[
	m_player.InputHandlerUpdate(*m_keyboard);
	m_player.Update();
	
	if (m_countDice <= 0)
	{
		m_dice.roll();
		m_countDice = m_dice.GetNumber();
		m_player.SetCountDice(m_countDice);
		//m_diceflag
	}
}

void Play::Render()
{
	//�J����
	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());
	m_effect->SetWorld(m_camera->GetWorld());

	m_effect->Apply(DirectXResourse::m_d3dContext.Get());
	DirectXResourse::m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_glound.Render();
	m_map.Render();
	m_grid.Render(); 

	m_player.Render();

	m_dice.SetDiceNamber(m_countDice);
	m_dice.Render();
	//�f�o�b�N�p////////////////////////////////////////////////////////////////
	//�V�[������\��
	Scene::m_text->Render(L"PlayScene");
	////////////////////////////////////////////////////////////////////////////
}
