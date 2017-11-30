//
//�}�E�X
//
//2017/10/26
//Motoya Ito
#include "Mouse.h"

#include <assert.h>

MouseCircumference* MouseCircumference::m_instans;
//�����֐�====================================================
MouseCircumference::MouseCircumference()
	//: m_clickLeftButton(false), m_clickRightButton(false)
{
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetMode(Mouse::Mode::MODE_ABSOLUTE);

	//�{�^����������Ă��鎞�̕ϐ��A�h���X��o�^
	m_buttonClick[Left] = &m_state.leftButton;
	m_buttonClick[Middle] = &m_state.middleButton;
	m_buttonClick[Right] = &m_state.rightButton;
	
	//�{�^���g���K�[�̕ϐ��A�h���X��o�^
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

//public�֐�==================================================
MouseCircumference* MouseCircumference::GetInstans()
{
	if (m_instans == nullptr)
	{
		m_instans = new MouseCircumference();
	}

	return m_instans;
}

/// <summary>
/// �X�V
/// </summary>
void MouseCircumference::Update()
{
	// �}�E�X�����擾
	m_state = m_mouse->GetState();

	//�g���K�[�̍X�V
	m_buttonStateTracker.Update(m_state);
}

/// <summary>
/// �w��{�^����������Ă��邩
/// </summary>
/// <param name="button">�{�^���ԍ�</param>
/// <returns>������Ă�(true)������Ă��Ȃ�(false)</returns>
bool MouseCircumference::PushButton(Button button)
{
	//�{�^���ԍ����͈͓��Ɏ��܂��Ă��邱�Ƃ��`�F�b�N
	assert(0 <= button && button < Num);

	return *m_buttonClick[button];
}

/// <summary>
/// �w��{�^���̃g���K�[�`�F�b�N
/// </summary>
/// <param name="button">�{�^���ԍ�</param>
/// <returns>�����ꂽ�΂���(true)����ȊO(false)</returns>
bool MouseCircumference::ThickButtonTrigger(Button button)
{
	//�{�^���ԍ����͈͓��Ɏ��܂��Ă��邱�Ƃ��`�F�b�N
	assert(0 <= button && button < Num);

	if (*m_buttonTrackerState[button] == Mouse::ButtonStateTracker::PRESSED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �w��̃{�^�������ꂽ��
/// </summary>
/// <param name="button">�{�^���ԍ�</param>
/// <returns>�����ꂽ(ture)������Ă��Ȃ�(fasle)</returns>
bool MouseCircumference::ReleasedButton(Button button)
{
	// �{�^���ԍ����͈͓��Ɏ��܂��Ă��邱�Ƃ��`�F�b�N
	assert(0 <= button && button < Num);

	if (*m_buttonTrackerState[button] == Mouse::ButtonStateTracker::RELEASED)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �z�C�[���̒l�����Z�b�g
/// </summary>
void MouseCircumference::ResetWheelValue()
{
	m_mouse->ResetScrollWheelValue();
}

