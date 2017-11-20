//
//テキスト
//itomotoya
//2017.08.09

#pragma once

#include <SpriteFont.h>
#include <SimpleMath.h>

#include "..//DirectXResourse.h"

class Text : public DirectXResourse
{
private:
	using Vector2 = DirectX::SimpleMath::Vector2;

private:
	DirectX::SpriteBatch* m_spriteBatch;


	DirectX::SpriteFont* m_font;//文字フォント

	Vector2 m_pos;//描画座標
	

public:
	Text();
	~Text();

	void Render(const wchar_t* output);

public://getter

public://setter
	void SetPos(Vector2 pos) { m_pos = pos; }
};