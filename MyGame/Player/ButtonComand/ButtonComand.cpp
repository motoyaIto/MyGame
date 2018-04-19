//
//“o˜^—pƒnƒ“ƒhƒ‰[
//
//Ito Motoya
//2017/12/03
//
#include "ButtonComand.h"

void InputHandler::HandleInput(Actor & Actor, KeyboradUtil& keybord)
{
	if (keybord.GetKeyDown(DirectX::Keyboard::Up))
	{
		buttonUp->Execute(Actor);
	}

	if (keybord.GetKeyDown(DirectX::Keyboard::Down))
	{
		buttonDown->Execute(Actor);
	}

	if (keybord.GetKeyDown(DirectX::Keyboard::Right))
	{
		buttonRight->Execute(Actor);
	}

	if (keybord.GetKeyDown(DirectX::Keyboard::Left))
	{
		buttonLeft->Execute(Actor);
	}

}
