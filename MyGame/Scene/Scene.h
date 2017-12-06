//
//シーンクラス
//
//2017/11/27
//Ito Motoya
#pragma once

#include <d3d11_1.h>

#include <Effects.h>
#include <Keyboard.h>
#include <SimpleMath.h>
#include <VertexTypes.h>

#include "..//Camera//Camera.h"
#include "..//Camera//DebugCamera//DebugCamera.h"
#include "..//DirectXResourse//Text//Text.h"
#include "..//Mouse//Mouse.h"

class Scene
{
protected:
	using Vector2 = DirectX::SimpleMath::Vector2;
	using Vector3 = DirectX::SimpleMath::Vector3;
protected:
	static int s_width;	//スクリーンサイズ(横)
	static int s_height;//スクリーンサイズ(縦)

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	DirectX::BasicEffect* m_effect;

	DirectX::Keyboard* m_keyboard;//キーボード
	DirectX::Keyboard::KeyboardStateTracker m_keyTracker;//キーボードトラッカー

	Camera* m_camera;	//カメラ
	Text* m_text;		//テキスト

public:
	Scene();
	virtual ~Scene();

	virtual void Initialize();
	virtual void Update();
	virtual void Render();

public://geter

public://setter
	static void SetWidth(int width) { s_width = width; }
	static void SetHeight(int height) { s_height = height; }


};