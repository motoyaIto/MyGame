//
//�}�E�X(singleton)
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
	std::unique_ptr<Mouse> m_mouse;//�}�E�X
	Mouse::State m_state;//�}�E�X�X�e�[�g
	Mouse::ButtonStateTracker m_buttonStateTracker;//�}�E�X�{�^���g���b�J�[
	bool* m_buttonClick[Button::Num];//�{�^����������Ă���(true)���Ȃ�(false)
	Mouse::ButtonStateTracker::ButtonState* m_buttonTrackerState[Button::Num];//�{�^���g���b�J�[�X�e�[�g

private://�����֐�
	MouseCircumference();
	MouseCircumference(const MouseCircumference& cp);
	~MouseCircumference();

public:
	static MouseCircumference* GetInstans();

public:
	void Update();

	
	bool PushButton(Button button);// �w��{�^����������Ă��邩
	bool ThickButtonTrigger(Button button);//�w��{�^���̃g���K�[�`�F�b�N
	bool ReleasedButton(Button button);//�w��̃{�^�������ꂽ��

	void ResetWheelValue();//�z�C�[���̒l�����Z�b�g
public://getter
	const int GetPos_X() { return m_state.x; }
	const int GetPos_Y() { return m_state.y; }

	const int GetWheelValue() { return m_state.scrollWheelValue; }

public://setter
	void SetMouseInWindow(const HWND window) { m_mouse->SetWindow(window); }
};