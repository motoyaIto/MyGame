//
//�V�[���N���X
//
//2017/11/27
//Ito Motoya
#include "Scene.h"
#include "..//DirectXResourse//Obj3D//Obj3D.h"


//�ÓI�����o�̏�����
int Scene::s_width;
int Scene::s_height;

Scene::Scene()
{
	//�J����
	m_camera = new Camera(s_width, s_height);

	//�I�u�W�F�N�g�̃C�j�V�����C�Y
	Obj3D::InitializeStatic(m_camera);

	//�L�[�{�[�h
	if(!m_keyboard)
	m_keyboard = new DirectX::Keyboard();
	
	m_effect = new DirectX::BasicEffect(DirectXResourse::m_d3dDevice.Get());
	
	m_effect->SetView(m_camera->GetView());
	m_effect->SetProjection(m_camera->GetProj());

	void const* shaderByCode;
	size_t byteCodeLength;

	m_effect->GetVertexShaderBytecode(&shaderByCode, &byteCodeLength);
	DirectXResourse::m_d3dDevice->CreateInputLayout(DirectX::VertexPositionColor::InputElements, DirectX::VertexPositionColor::InputElementCount, shaderByCode, byteCodeLength, m_inputLayout.GetAddressOf());

	m_state = true;
}

Scene::~Scene()
{
	//delete m_camera;
	//delete m_text;
}

void Scene::Initialize()
{
	
}

void Scene::Update()
{
	
}

void Scene::Render()
{
	
}
