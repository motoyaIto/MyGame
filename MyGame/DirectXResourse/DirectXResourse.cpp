//
//DirectXのデバイス
//ito motya
//2017.08.07
//参考資料:学校配布のプロジェクト
#include "DirectXResourse.h"

//静的変数の実体
Microsoft::WRL::ComPtr<ID3D11Device> DirectXResourse::m_d3dDevice;//デバイス
Microsoft::WRL::ComPtr<ID3D11DeviceContext> DirectXResourse::m_d3dContext;//デバイスコンテキスト								

/// <summary>
///インスタンス化したクラスを返す 
/// </summary>
/// <returns>インスタンス化したクラス</returns>
DirectXResourse& DirectXResourse::GetInstacse()
{
	static DirectXResourse object;

	return object;
}

/// <summary>
/// 静的メンバの初期化
/// </summary>
/// <param name="d3dDevice">デバイス</param>
/// <param name="d3dContext">デバイステキスト</param>
void DirectXResourse::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
}

/// <summary>
/// イニシャライズ
/// </summary>
DirectXResourse::DirectXResourse()
{
	
}