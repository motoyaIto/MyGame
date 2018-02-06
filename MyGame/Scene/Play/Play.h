//
//playシーン
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
	static const int PLAYERNAM;

	static const int DICENAM = 2;

	enum GameManager
	{
		ROLLDICE,//サイコロを振る
		MOVESERECT,//移動先を選ぶ
		MOVE,//移動
		MAPGIMMICK//ギミック
	};

	struct PlayerState
	{
		bool playing;
		bool RollTwoDice;
	};
	
	GameManager m_gameManager;

	MAP m_map;
	Grid m_grid;
	Glound m_glound;

	Player* m_player;
	PlayerState* m_playerState;
	
	Dice m_dice[DICENAM];
	int m_countDice;

	int m_countTime;

public:
	Play();
	~Play();

	void Initialize() override;
	void Update() override;
	void Render() override;

};