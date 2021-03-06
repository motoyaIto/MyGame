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
#include "..//KeyboradUtil//KeyboradUtil.h"

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

	
	KeyboradUtil* m_keyborad;
	Camera* m_camera;	//カメラ
	Text* m_text;		//テキスト
	bool m_state;		//プレイ中(true)していない(false)

public:
	Scene();
	virtual ~Scene();

	virtual void Initialize() = 0;
	virtual void Update()  = 0;
	virtual void Render()  = 0;

public://geter
	bool GetState() { return m_state; }

public://setter
	static void SetWidth(int width) { s_width = width; }
	static void SetHeight(int height) { s_height = height; }


};