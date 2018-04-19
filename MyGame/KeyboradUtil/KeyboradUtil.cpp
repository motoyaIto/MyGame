//
//キーボード
//
//2017/11/27
//Ito Motoya
#include "KeyboradUtil.h"

KeyboradUtil* KeyboradUtil::m_instans;

//public関数========================================================================================
KeyboradUtil* KeyboradUtil::GetInstans()
{
	if (m_instans == nullptr)
	{
		m_instans = new KeyboradUtil();
	}

	return m_instans;
}

void KeyboradUtil::Update()
{
	//キーボード
	m_keyTracker.Update(m_keyboard->GetState());

	DirectX::Keyboard::State keyState = m_keyboard->GetState();
}

bool KeyboradUtil::GetKeyDown(DirectX::Keyboard::Keys key)
{
	DirectX::Keyboard::State keyState = m_keyboard->GetState();

	if (keyState.IsKeyDown(key) == true && m_oldKeyState.IsKeyDown(key) == false)
	{
		return true;
	}

	return false;
}
