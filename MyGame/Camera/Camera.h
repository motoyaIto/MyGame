//
//�J�����̊��N���X
//
//Motoya Ito
//2017/10/16
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>

class Camera
{
protected:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector2 = DirectX::SimpleMath::Vector2;
	using Vector3 = DirectX::SimpleMath::Vector3;

protected:
	Matrix m_world;		//���[���h���W�s��

	Matrix m_proj;		//�v���W�F�N�V�����s��(�ˉe�s��)
	float m_fovY;		//�c�̎ʂ��͈�(������������p)
	float m_aspect;		//�c���̔䗦(�A�X�y�N�g��)
	float m_nearclip;	//��O�̕\�����E����(�j�A�N���b�v)
	float m_farclip;	//���̕\�����E����(�t�@�[�N���b�v)

	Matrix m_view;		//�r���[�s��
	Vector3 m_eyepos;	//���_(�J�����̈ʒu)
	Vector3 m_refpos;	//�Q�Ɠ_(����ꏊ)
	Vector3 m_upvec;	//������x�N�g��(�ǂ��炪�ォ)

public:
	Camera(int width, int height);
	virtual ~Camera();

	virtual void Update();

public://getter
	const Matrix& GetView() { return m_view; }
	const Matrix& GetProj() { return m_proj; }
	const Matrix& GetWorld() { return m_world; }

public://setter
	void SetEyepos(Vector3 eyepos) { m_eyepos = eyepos; }
	void SetRefpos(Vector3 refpos) { m_refpos = refpos; }
	void SetUpvec(Vector3 upvec) { m_upvec = upvec; }
};