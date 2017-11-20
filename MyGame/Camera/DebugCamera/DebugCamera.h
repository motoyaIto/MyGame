//
//�f�o�b�N�p�J����
//
//Motoya Ito
//2017/10/16
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#pragma once
#include "..//Camera.h"


class DebugCamera : public Camera
{
private://�ÓI�ϐ�
	//�f�t�H���g�̃J�����̋���
	static const float DEFAULT_CAMERA_DISTANCE;

private://�����֐�
	void Motion(const int& x, const int& y);//�ړ���̍s����v�Z

private:
	Vector2 m_nowAngle;		//���̉�]�p
	Vector2 m_afterAngle;	//��]��̉�]�p
	
	Vector2 m_drag;			//�h���b�O���ꂽ���W
	
	Vector2 m_relativeScale;//��ʂ̑��ΓI�X�P�[��

	int m_scrollWheelValue;	// �X�N���[���t�H�C�[���l

public:
	DebugCamera(int width, int height);
	~DebugCamera() override;

	void Update() override;

public://getter

public://setter
	
};
