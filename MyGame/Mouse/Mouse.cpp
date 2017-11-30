//
//マウス
//
//2017/10/26
//Motoya Ito
#include "Mouse.h"

#include <assert.h>

MouseCircumference* MouseCircumference::m_instans;
//内部関数====================================================
MouseCircumference::MouseCircumference()
	//: m_clickLeftButton(false), m_clickRightButton(false)
{
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetMode(Mouse::Mode::MODE_ABSOLUTE);

	//ボタンが押されている時の変数アドレスを登録
	m_buttonClick[Left] = &m_state.leftButton;
	m_buttonClick[Middle] = &m_state.middleButton;
	m_buttonClick[Right] = &m_state.rightButton;
	
	//ボタントリガーの変数アドレスを登録
	m_buttonTrackerState[Left] = &m_buttonStateTracker.leftButton;
	m_buttonTrackerState[Middle] = &m_buttonStateTracker.middleButton;
	m_buttonTrackerState[Right] = &m_buttonStateTracker.rightButton;
}

MouseCircumference::MouseCircumference(const MouseCircumference& cp)
{
	
}

MouseCircumference::~MouseCircumference()
{
	
}

//public関数==================================================
MouseCircumference* MouseCircumference::GetInstans()
{
	if (m_instans == nullptr)
	{
		m_instans = new MouseCircumference();
	}

	return m_instans;
}

/// <summary>
/// 更新
/// </summary>
void MouseCircumference::Update()
{
	// マウス情報を取得
	m_state = m_mouse->GetState();

	//トリガーの更新
	m_buttonStateTracker.Update(m_state);
}

/// <summary>
/// 指定ボタンが押されているか
/// </summary>
/// <param name="button">ボタン番号</param>
/// <returns>押されてる(true)押されていない(false)</returns>
bool MouseCircumference::PushButton(Button button)
{
	//ボタン番号が範囲内に収まっていることをチェック
	assert(0 <= button && button < Num);

	return *m_buttonClick[button];
}

/// <summary>
/// 指定ボタンのトリガーチェック
/// </summary>
/// <param name="button">ボタン番号</param>
/// <returns>押されたばかり(true)それ以外(false)</returns>
bool MouseCircumference::ThickButtonTrigger(Button button)
{
	//ボタン番号が範囲内に収まっていることをチェック
	assert(0 <= button && button < Num);

	if (*m_buttonTrackerState[button] == Mouse::ButtonStateTracker::PRESSED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// 指定のボタンが放れたか
/// </summary>
/// <param name="button">ボタン番号</param>
/// <returns>放された(ture)放されていない(fasle)</returns>
bool MouseCircumference::ReleasedButton(Button button)
{
	// ボタン番号が範囲内に収まっていることをチェック
	assert(0 <= button && button < Num);

	if (*m_buttonTrackerState[button] == Mouse::ButtonStateTracker::RELEASED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// ホイールの値をリセット
/// </summary>
void MouseCircumference::ResetWheelValue()
{
	m_mouse->ResetScrollWheelValue();
}

