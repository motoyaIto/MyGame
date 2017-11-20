//
//3D�`��
//itomotoya
//2017.08.09

#include "Obj3D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

std::unique_ptr<DirectX::CommonStates> Obj3D::m_states;//�ėp�`��X�e�[�g
std::unique_ptr<DirectX::EffectFactory> Obj3D::m_factory;//�G�t�F�N�g�t�@�N�g��

Camera* Obj3D::m_camera;//�J����

void Obj3D::InitializeStatic(Camera * camera)
{
	m_camera = camera;
}


Obj3D::Obj3D()
	//: m_model(nullptr)
	: m_scale(Vector3::Zero)
	, m_rotationQ(Quaternion::Identity)
	, m_rotationO(Vector3::Zero)
	, m_translation(Vector3::Zero)
	, m_world(Matrix::Identity)

	, m_parent(nullptr)
	
{
	
	// �ėp�`��X�e�[�g
		m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());
	//�G�t�F�N�g�t�@�N�g�����쐬
	m_factory = std::make_unique<DirectX::EffectFactory>(m_d3dDevice.Get());
	//�e�N�X�`���̓ǂݍ��݃p�X�ݒ�
	m_factory->SetDirectory(L"Resources");
}



Obj3D::~Obj3D()
{
	delete m_parent;
}


void Obj3D::UpdateQ()
{
	//�s��̌v�Z======================================================
	//�X�P�[���̍s����쐬
	Matrix scalemat = Matrix::CreateScale(m_scale);

	//��]�s��
	Matrix rotmat;

	//�N�I�[�^�j�I���s��̍쐬
	rotmat = Matrix::CreateFromQuaternion(m_rotationQ);

	//���s�s��
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//���[���h�s����v�Z����
	m_world = scalemat * transmat* rotmat;

	if (m_parent != nullptr)
	{
		m_world *= m_parent->m_world;
	}
}

void Obj3D::UpdateO()
{
	//�X�P�[���̍s����쐬
	Matrix scalemat = Matrix::CreateScale(m_scale);

	//��]�s��
	Matrix rotmat;

	Matrix rotmatZ = Matrix::CreateRotationZ(m_rotationO.z);
	Matrix rotmatX = Matrix::CreateRotationX(m_rotationO.x);
	Matrix rotmatY = Matrix::CreateRotationY(m_rotationO.y);
	rotmat = rotmatZ * rotmatX * rotmatY;

	/*Matrix Trotmat;

	rotmatZ = Matrix::CreateRotationZ(0);
	rotmatX = Matrix::CreateRotationX(180);
	rotmatY = Matrix::CreateRotationY(0);
	Trotmat = rotmatZ * rotmatX * rotmatY;*/

	//���s�s��
	Matrix transmat = Matrix::CreateTranslation(m_translation);

	//���[���h�s����v�Z����
	m_world = scalemat * rotmat * transmat;

	if (m_parent != nullptr)
	{
		m_world *= m_parent->m_world;
	}
}

void Obj3D::Render()
{
	assert(m_camera);//�J���������邩�̊m�F

	if (m_model)
	{
		//3D���f���̕`��
		m_model->Draw(m_d3dContext.Get(), *m_states, m_world, m_camera->GetView(), m_camera->GetProj());
	}
}

/// <summary>
/// ���f���̓ǂݍ���
/// </summary>
/// <param name="fileName">�t�@�C����</param>
void Obj3D::LoadModel(const wchar_t * fileName)
{
	m_model = Model::CreateFromCMO(m_d3dDevice.Get(), fileName, *m_factory);

	//���b�V���̉���擾
	m_meshes = &m_model->meshes;
}


