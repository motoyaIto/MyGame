//
//�e�N�X�`��
//itoumotoya
//2017.07.23

#pragma once

#include "..//DirectXResourse.h"

#include <CommonStates.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>


class Texture : public DirectXResourse
{
private:
	using Vector2 = DirectX::SimpleMath::Vector2;

private:
	DirectX::CommonStates* m_states;//�X�e�[�^�X
	std::unique_ptr<DirectX::SpriteBatch> m_batch;

	
	Vector2 m_screenPos;//�X�N���[�����W
	Vector2 m_origin;	//�摜�̌��_
	RECT m_rect;		//�g���~���O

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;//�摜�f�[�^
public:

	Texture();
	
	~Texture();

	void Update();
	void Render();

	void LoadModel(const wchar_t* fileName);

public://geter
	const Vector2 GetScreenPos() { return m_screenPos; }

public://seter
	const void SetRect(RECT& rect) { m_rect = rect; }
	const void SetScreenPos(Vector2& screenPos) { m_screenPos = screenPos; }

};
