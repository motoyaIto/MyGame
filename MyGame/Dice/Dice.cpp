#include <cstdlib>
#include <time.h>
#include"Dice.h"

//‰Šú‰»
Dice::Dice()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	m_numsize = 6;
	m_number = 1;
	
	m_dice = new Texture();
	m_dice->LoadModel(L"Resources//Images//Dice.png");
	m_dice->SetScreenPos(Vector2(0, 20));
}

//”jŠü
Dice::~Dice()
{

}

void Dice::Render()
{
	RECT rect;
	rect.top = 32;	rect.bottom = 32;
	rect.left = 32;	rect.right = 32;

	switch (m_nowDiceNamber)
	{
	case ONE:
		rect.top *= 0;
		rect.left *= 0;
		break;

	case TWO:
		rect.top *= 0;
		rect.right *= 2;
		break;

	case THREE:
		rect.top *= 0;
		rect.left *= 2;	rect.right *= 3;
		break;

	case FOUR:
		rect.bottom *= 2;
		rect.left *= 0;
		break;

	case FIVE:
		rect.bottom *= 2;
		rect.right *= 2;
		break;

	case SIX:
		rect.bottom *= 2;
		rect.left *= 2; rect.right *= 3;
		break;

	}	

	m_dice->SetRect(rect);

	m_dice->Render();
}		

//“]‚ª‚é
void Dice::roll()
{
	m_number = rand() % m_numsize + 1;
}

