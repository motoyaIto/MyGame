//
//playÉVÅ[Éì
//
//2017/11/27
//Ito Motoya
#pragma once

#include "..//Scene.h"

#include "..//..//DirectXResourse//Line//Grid//Grid.h"

#include "..//..//Glound//Glound.h"
#include "..//..//MAP//MAP.h"
#include "..//..//Player//Player.h"
#include "..//..//Dice//Dice.h"

class Play : public Scene 
{
private:
	enum mode
	{
		ROLLDICE,
		MOVESERECT,
		MOVE,
		MAPGIMMICK
	};
	
	MAP m_map;
	Grid m_grid;
	Glound m_glound;

	Player m_player;

	Dice m_dice;
	int m_countDice;
	bool* m_diceflag;

public:
	Play();
	~Play();

	void Initialize() override;
	void Update() override;
	void Render() override;

};