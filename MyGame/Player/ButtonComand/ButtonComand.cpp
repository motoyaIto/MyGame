//
//“o˜^—pƒnƒ“ƒhƒ‰[
//
//Ito Motoya
//2017/12/03
//
#include "ButtonComand.h"

void InputHandler::HandleInput(Actor & Actor, DirectX::Keyboard & keyboard)
{
	DirectX::Keyboard::State keyState = keyboard.GetState();

	if (keyState.Up && !m_oldKeyState.Up)
	{
		buttonUp->Execute(Actor);
	}

	if (keyState.Down && !m_oldKeyState.Down)
	{
		buttonDown->Execute(Actor);
	}

	if (keyState.Right && !m_oldKeyState.Right)
	{
		buttonRight->Execute(Actor);
	}

	if (keyState.Left && !m_oldKeyState.Left)
	{
		buttonLeft->Execute(Actor);
	}

	m_oldKeyState = keyState;
}
