//
//DirectX�̃f�o�C�X(singleton)
//ito motya
//2017.08.07
//�Q�l����:�w�Z�z�z�̃v���W�F�N�g
#pragma once

#include <d3d11_1.h>

#include <wrl/client.h>


class DirectXResourse
{
private://�Q�Ƃł���N���X
	friend class Obj3D;
	friend class Text;
	friend class Line;

private://�����֐�
	DirectXResourse();

	static DirectXResourse& GetInstacse();

public:
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;//�f�o�C�X
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_d3dContext;//�f�o�C�X�e�L�X�g
	

	

public:
	static void InitializeStatic(static Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice
									, static Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);
};