#include <cstdlib>
#include"Dice.h"

//‰Šú‰»
Dice::Dice()
{
	m_numsize = 6;
	m_number = 1;
}

//”jŠü
Dice::~Dice()
{

}

//“]‚ª‚é
int Dice::roll()
{
	m_number = rand() % m_numsize + 1;

	return m_number;
}

//–Ú‚Ìæ“¾
int Dice::getNumber()
{
	return m_number;
}