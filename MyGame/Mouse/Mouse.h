//
//マウス(singleton)
//
//2017/10/26
//Motoya Ito
#pragma once

#include <d3d11_1.h>

#include <memory>

#include <Mouse.h>

class MouseCircumference
{
private:
	using Mouse = DirectX::Mouse;

private:
	static MouseCircumference* m_instans;
	
public:
	enum Button
	{
		Left,
		Middle,
		Right,

		Num

	};
private:
	std::unique_ptr<Mouse> m_mouse;//マウス
	Mouse::State m_state;//マウスステート
	Mouse::ButtonStateTracker m_buttonStateTracker;//マウスボタントラッカー
	bool* m_buttonClick[Button::Num];//ボタンが押されている(true)いない(false)
	Mouse::ButtonStateTracker::ButtonState* m_buttonTrackerState[Button::Num];//ボタントラッカーステート

private://内部関数
	MouseCircumference();
	MouseCircumference(const MouseCircumference& cp);
	~MouseCircumference();

public:
	static MouseCircumference* GetInstans();

public:
	void Update();

	
	bool PushButton(Button button);// 指定ボタンが押されているか
	bool ThickButtonTrigger(Button button);//指定ボタンのトリガーチェック
	bool ReleasedButton(Button button);//指定のボタンが放れたか

	void ResetWheelValue();//ホイールの値をリセット
public://getter
	const int GetPos_X() { return m_state.x; }
	const int GetPos_Y() { return m_state.y; }

	const int GetWheelValue() { return m_state.scrollWheelValue; }

public://setter
	void SetMouseInWindow(const HWND window) { m_mouse->SetWindow(window); }
};