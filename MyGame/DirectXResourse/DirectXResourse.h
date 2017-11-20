//
//DirectXのデバイス(singleton)
//ito motya
//2017.08.07
//参考資料:学校配布のプロジェクト
#pragma once

#include <d3d11_1.h>

#include <wrl/client.h>


class DirectXResourse
{
private://参照できるクラス
	friend class Obj3D;
	friend class Text;
	friend class Line;

private://内部関数
	DirectXResourse();

	static DirectXResourse& GetInstacse();

public:
	static Microsoft::WRL::ComPtr<ID3D11Device> m_d3dDevice;//デバイス
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>m_d3dContext;//デバイステキスト
	

	

public:
	static void InitializeStatic(static Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice
									, static Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext);
};