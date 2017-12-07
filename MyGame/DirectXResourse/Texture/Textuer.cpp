//
//テクスチャ
//itoumotoya
//2017.07.23

#include "Texture.h"

#include <WICTextureLoader.h>
#include <SpriteBatch.h>

using namespace Microsoft::WRL;

using namespace DirectX;
using namespace DirectX::SimpleMath;



/// <summary>
/// コンストラクタ
/// </summary>
Texture::Texture()
	: m_screenPos(Vector2(0, 0))
	, m_origin(Vector2(0, 0))
{
	m_states = new CommonStates(m_d3dDevice.Get());
	m_batch = std::make_unique<SpriteBatch>(m_d3dContext.Get());

	
}

/// <summary>
/// デストラクタ
/// </summary>
Texture::~Texture()
{

}

/// <summary>
/// アプデ
/// </summary>
void Texture::Update()
{

}

/// <summary>
/// レンダー
/// </summary>
void Texture::Render()
{
	m_batch->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	m_batch->Draw(m_texture.Get(), m_screenPos, &m_rect, Colors::White,
		0.f, m_origin);

	m_batch->End();
}

/// <summary>
/// 画像読み込み	
/// </summary>
/// <param name="fileName">ファイルデータ</param>
void Texture::LoadModel(const wchar_t * fileName)
{
	ComPtr<ID3D11Resource> resource;
	CreateWICTextureFromFile(m_d3dDevice.Get(), fileName,
		resource.GetAddressOf(),
		m_texture.ReleaseAndGetAddressOf());

	ComPtr<ID3D11Texture2D> textuer;
	resource.As(&textuer);
}
