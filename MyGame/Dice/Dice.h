#pragma once

#include "..//DirectXResourse//Texture//Texture.h"

#include <SimpleMath.h>

class Dice
{
private:
	using Vector2 = DirectX::SimpleMath::Vector2;

public:
	enum DiceNamber
	{
		ONE = 1,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX
	};

private:
	int m_number;		//サイコロの出てる目
	int m_numsize;		//サイコロの面の数

	Texture* m_dice;
	int m_nowDiceNamber;


public:
	//コンストラクタ
	Dice();

	//デストラクタ
	~Dice();

	void Render();

	//転がる
	void roll();

public://getter
	int GetNumber() { return m_number; }

public://setter
	void SetDiceNamber(int diceNumber) { m_nowDiceNamber = diceNumber; }
};