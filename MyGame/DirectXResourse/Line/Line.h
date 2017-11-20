//
//��
//ItoMotoya
//2017/10/16
//�Q�l����:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#pragma once

#include "..//DirectXResourse.h"

#include <CommonStates.h>
#include <Effects.h>
#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>


class Line : public DirectXResourse
{
protected:
	using Matrix = DirectX::SimpleMath::Matrix;
	using Vector3 = DirectX::SimpleMath::Vector3;

protected:
	DirectX::CommonStates* m_states;//�X�e�[�^�X
	DirectX::BasicEffect* m_effect;//�G�t�F�N�g
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;//���_�A�|�W�V�����A�F�ō����`��
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;//���̓��A�E�g

private:
	Matrix m_cameraWorld;	//�J�����̃��[���h�s��
	Matrix m_cameraView;	//�J�����̃r���[�s��
	Matrix m_cameraProj;	//�v���W�F�N�V�����s��(�ˉe�s��)

	Vector3 m_startPos;	//���C���̏o���_
	Vector3 m_endPos;	//���C���̓��B�_

public:
	Line();
	~Line();

	void Initialize();
	virtual void Update();
	virtual void Render();

public://getter

public://setter
	void SetView(Matrix CameraView) { m_cameraView = CameraView; }
	void SetProj(Matrix CameraProj) { m_cameraProj = CameraProj; }
	void SetStartPos(Vector3 startPos) { m_startPos = startPos; }
	void SetEndPos(Vector3 endPos) { m_endPos = endPos; }
	
};