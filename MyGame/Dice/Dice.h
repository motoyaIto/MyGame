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
	int m_number;		//�T�C�R���̏o�Ă��
	int m_numsize;		//�T�C�R���̖ʂ̐�

	Texture* m_dice;
	int m_nowDiceNamber;


public:
	//�R���X�g���N�^
	Dice();

	//�f�X�g���N�^
	~Dice();

	void Render();

	//�]����
	void roll();

public://getter
	int GetNumber() { return m_number; }

public://setter
	void SetDiceNamber(int diceNumber) { m_nowDiceNamber = diceNumber; }
};