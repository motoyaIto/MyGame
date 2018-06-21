//
//テキスト
//itomotoya
//2017.08.09

#include "Text.h"

#include <iostream>
#include <windows.h>
#include <sstream> 

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

void Text::Render(int * output)
{
	std::wstringstream ss;

	//数値をストリングストリームに入れる
	ss << output;

	//ワイド文字に格納
	std::wcout << ss.str();

	this->Render(ss.str().c_str());
}

void Text::Render(float * output)
{
	std::wstringstream ss;

	//floatの精度指定（任意）
	ss.precision(17);

	//数値をストリングストリームに入れる
	ss << output;

	//ワイド文字に格納
	std::wcout << ss.str();

	this->Render(ss.str().c_str());
}
