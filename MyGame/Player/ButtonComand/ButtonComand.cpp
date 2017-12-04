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

	if (keyState.Up)
	{
		buttonUp->Execute(Actor);
	}

	if (keyState.Down)
	{
		buttonDown->Execute(Actor);
	}

	if (keyState.Right)
	{
		buttonRight->Execute(Actor);
	}

	if (keyState.Left)
	{
		buttonLeft->Execute(Actor);
	}

	if (keyState.Space)
	{
		buttonSpace->Execute(Actor);
	}
}
