//
//DirectX�̃f�o�C�X
//ito motya
//2017.08.07
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#include "DirectXResourse.h"

//�ÓI�ϐ��̎���
Microsoft::WRL::ComPtr<ID3D11Device> DirectXResourse::m_d3dDevice;//�f�o�C�X
Microsoft::WRL::ComPtr<ID3D11DeviceContext> DirectXResourse::m_d3dContext;//�f�o�C�X�R���e�L�X�g								

/// <summary>
///�C���X�^���X�������N���X��Ԃ� 
/// </summary>
/// <returns>�C���X�^���X�������N���X</returns>
DirectXResourse& DirectXResourse::GetInstacse()
{
	static DirectXResourse object;

	return object;
}

/// <summary>
/// �ÓI�����o�̏�����
/// </summary>
/// <param name="d3dDevice">�f�o�C�X</param>
/// <param name="d3dContext">�f�o�C�X�e�L�X�g</param>
void DirectXResourse::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
}

/// <summary>
/// �C�j�V�����C�Y
/// </summary>
DirectXResourse::DirectXResourse()
{
	
}