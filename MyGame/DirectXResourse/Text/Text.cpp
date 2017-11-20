//
//テキスト
//itomotoya
//2017.08.09

#include "Text.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Text::Text()
	: m_pos(Vector2(0, 0))
	
{
	m_font = new SpriteFont(m_d3dDevice.Get(), L"DirectXResourse//Text//myfile.spritefont");

	m_spriteBatch = new SpriteBatch(m_d3dContext.Get());

}

Text::~Text()
{
}

void Text::Render(const wchar_t* output)
{
	m_spriteBatch->Begin();

	m_font->DrawString(m_spriteBatch, output,
		m_pos, Colors::White, 0.f, Vector2(0.0f, 0.0f), Vector2(0.5f, 0.5f));

	m_spriteBatch->End();
}
