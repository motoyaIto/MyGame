#include <cstdlib>
#include"Dice.h"

//������
Dice::Dice()
{
	m_numsize = 6;
	m_number = 1;
}

//�j��
Dice::~Dice()
{

}

//�]����
int Dice::roll()
{
	m_number = rand() % m_numsize + 1;

	return m_number;
}

//�ڂ̎擾
int Dice::getNumber()
{
	return m_number;
}