//
//�f�o�b�N�p�J����
//
//Motoya Ito
//2017/10/16
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#include "DebugCamera.h"

#include "..//..//Mouse//Mouse.h"

//�ÓI�ϐ��̎���
const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

//�����֐�====================================================
/// <summary>
/// �ړ���̍s����v�Z
/// </summary>
/// <param name="x">�}�E�X�̍��W.x</param>
/// <param name="y">�}�E�X�̍��W.y</param>
void DebugCamera::Motion(const int& x, const int& y)
{
	//�}�E�X�|�C���^�̈ʒu�̃h���b�O�J�n�ʒu����ψ�(���Βl)
	float dx = (x - m_drag.x) * m_relativeScale.x;
	float dy = (y - m_drag.y) * m_relativeScale.y;

	if (dx != 0.0f || dy != 0.0f)
	{
		//X���̉�]
		float xAngle = dy * DirectX::XM_PI;
		//Y���̉�]
		float yAngle = dx * DirectX::XM_PI;

		//��]��̊p�x���i�[
		m_afterAngle.x = m_nowAngle.x + xAngle;
		m_afterAngle.y = m_nowAngle.y + yAngle;
	}
}


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="width">��ʂ̉��̃T�C�Y</param>
/// <param name="height">��ʂ̏c�̃T�C�Y</param>
DebugCamera::DebugCamera(int width, int height)
	: Camera(width, height)
	, m_nowAngle(Vector2::Zero)
	, m_afterAngle(Vector2::Zero)
	, m_drag(Vector2::Zero)
	, m_relativeScale(Vector2(1.0f / (float)width, 1.0f / (float)height))
	, m_scrollWheelValue(0)
{
	
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
DebugCamera::~DebugCamera()
{
	Camera::~Camera();
}

/// <summary>
/// �X�V
/// </summary>
void DebugCamera::Update()
{
	MouseCircumference* mouse = MouseCircumference::GetInstans();

	//�}�E�X�̍��{�^���������ꂽ
	if (mouse->ThickButtonTrigger(MouseCircumference::Button::Left))
	{
		//�}�E�X�̍��W���擾
		m_drag.x = mouse->GetPos_X();
		m_drag.y = mouse->GetPos_Y();
	}
	//�}�E�X�̍��{�^���������ꂽ��
	else if (mouse->ReleasedButton(MouseCircumference::Button::Left))
	{
		m_nowAngle = m_afterAngle;
	}

	//�}�E�X�̃{�^����������Ă�����J�������ړ�������
	if (mouse->PushButton(MouseCircumference::Button::Left))
	{
		Motion(mouse->GetPos_X(), mouse->GetPos_Y());
	}

	//�}�E�X�̃t�H�C�[���l���擾
	m_scrollWheelValue = mouse->GetWheelValue();

	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		mouse->ResetWheelValue();
	}

	//�r���[�s����Z�o����
	Matrix rotX = Matrix::CreateRotationX(m_afterAngle.x);
	Matrix rotY = Matrix::CreateRotationY(m_afterAngle.y);

	Matrix rt = rotY * rotX;

	Vector3 eye(0.0f, 0.5f, 0.3f);
	Vector3 target(0.0f, 0.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	eye = Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = Vector3::Transform(up, rt.Invert());

	Camera::SetEyepos(eye);
	Camera::SetRefpos(target);
	Camera::SetUpvec(up);
	Camera::Update();
}



