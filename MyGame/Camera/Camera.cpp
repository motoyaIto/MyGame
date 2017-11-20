//
//�J�����̊��N���X
//
//Motoya Ito
//2017/10/16
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#include "Camera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="width">��ʂ̉��̃T�C�Y</param>
/// <param name="height">��ʂ̏c�̃T�C�Y</param>
Camera::Camera(int width, int height)
	: m_world(Matrix::Identity)
	, m_proj(Matrix::Identity)
	, m_fovY(XMConvertToRadians(60.0f))
	, m_aspect((float)width / height)
	, m_nearclip(0.1f)
	, m_farclip(1000.0f)

	, m_view(Matrix::Identity)
	, m_eyepos(Vector3(0.0f, 0.0f, 0.0f))
	, m_refpos(Vector3(0.0f, 0.0f, 0.0f))
	, m_upvec(Vector3(0.0f, 1.0f, 0.0f))
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
}

/// <summary>
/// �X�V
/// </summary>
void Camera::Update()
{
	//�r���[�s����쐬
	m_view = Matrix::CreateLookAt(m_eyepos, m_refpos, m_upvec);

	//�v���W�F�N�V�����s��
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearclip, m_farclip);
}
