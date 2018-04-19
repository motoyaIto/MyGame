//
//�L�[�{�[�h
//
//2017/04/19
//Ito Motoya
#pragma once

#include <d3d11_1.h>
#include <memory>
#include <Keyboard.h>


class KeyboradUtil
{
private:
	static KeyboradUtil* m_instans;

private:
	std::unique_ptr<DirectX::Keyboard> m_keyboard;//�L�[�{�[�h
	DirectX::Keyboard::KeyboardStateTracker m_keyTracker;//�L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::State m_oldKeyState;

private://�����֐�
	KeyboradUtil() { m_keyboard = std::make_unique<DirectX::Keyboard>(); }
	
public:
	static KeyboradUtil* GetInstans();

public:
	void Update();

	bool GetKeyDown(DirectX::Keyboard::Keys key);

public://getter

public://setter
	void SetOldKeyState() { m_oldKeyState = m_keyboard->GetState(); }


};