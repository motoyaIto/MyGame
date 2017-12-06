#include <cstdlib>
#include"Dice.h"

//初期化
Dice::Dice()
{
	m_numsize = 6;
	m_number = 1;
}

//破棄
Dice::~Dice()
{

}

//転がる
int Dice::roll()
{
	m_number = rand() % m_numsize + 1;

	return m_number;
}

//目の取得
int Dice::getNumber()
{
	return m_number;
}