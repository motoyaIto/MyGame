//
//��
//ItoMotoya
//2017/10/16
//�Q�l����:https://github.com/Microsoft/DirectXTK/wiki/Simple-rendering
#include "Line.h"

#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Line::Line()
{
	this->Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Line::~Line()
{
	delete m_states;//�X�e�[�^�X
	delete m_effect;//�G�t�F�N�g
}

/// <summary>
/// ������
/// </summary>
void Line::Initialize()
{
	//�f�o�C�X�ˑ��̏�����=======================================================================
	m_states = new DirectX::CommonStates( m_d3dDevice.Get());

	m_effect = new DirectX::BasicEffect(m_d3dDevice.Get());
	m_effect->SetVertexColorEnabled(true);//���_�̐F��L���ɂ���

	//���̓��C�A�E�g�̍쐬============================================================================
	void const* shaderByteCode;
	size_t byteCodeLength;

	//���_�V�F�[�_�̋@�B�R�[�h���擾
	m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

	//���̓��C�A�E�g�Ɋ֘A�t����
	m_d3dDevice->CreateInputLayout(VertexPositionColor::InputElements
		, VertexPositionColor::InputElementCount
		, shaderByteCode, byteCodeLength
		, m_inputLayout.ReleaseAndGetAddressOf());

	//���_�̃|�W�V�����ƐF��������=========================================================
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(m_d3dContext.Get());


	//�����P�ʍs��̎擾
	m_cameraWorld = DirectX::SimpleMath::Matrix::Identity;
}

/// <summary>
/// �X�V
/// </summary>
void Line::Update()
{
	m_cameraWorld = m_cameraView * m_cameraProj ;
}

/// <summary>
/// �`��
/// </summary>
void Line::Render()
{
	//�������Ńu�����h���@���m��(�m�[�}���u�����h)
	m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	//�[�x�X�e���V��(�[�x�o�b�t�@�[�A�X�e���V���o�b�t�@�[)
	m_d3dContext->OMSetDepthStencilState(m_states->DepthRead(), 0);
	//�T�[�t�F�C�X��Ƀ����_�����O
	m_d3dContext->RSSetState(m_states->CullNone());

	//�J�����̃��[���h�s����Z�b�g����
	m_effect->SetWorld(m_cameraWorld);
	//�G�t�F�N�g��K�p
	m_effect->Apply(m_d3dContext.Get());
	//���̓��C�A�E�g�̓K�p
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_batch->Begin();

	VertexPositionColor v1(m_startPos, Colors::White);//�J�n�n�_
	VertexPositionColor v2(m_endPos, Colors::White);//�I���n�_
	m_batch->DrawLine(v1, v2);//�`��


	m_batch->End();
}
