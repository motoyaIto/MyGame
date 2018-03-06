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
#include "..//..//Flag//Flag.h"

#include "..//..//DirectXResourse//Obj3D//Obj3D.h"

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
	
	
	

	GameManager m_gameManager;//ゲームのコントローラー

	MAP m_map;//マップ
	Flag* m_flag;
	Grid m_grid;//グリット
	Glound m_glound;//床

	Player* m_player;//プレイヤー
	PlayerState* m_playerState;//プレイヤーのコントロール状態
	
	Dice m_dice[DICENAM];//サイコロ
	int m_countDice;//ダイスからの移動

	//Obj3D* m_RedFlag;		//フラグ(赤)
	//Obj3D* m_BlueFlag;		//フラグ(青)
	//Obj3D* m_GreenFlag;		//フラグ(緑)
	//Obj3D* m_yerowllFlag;	//フラグ(黄色)

public:
	Play();
	~Play();

	void Initialize() override;
	void Update() override;
	void Render() override;

};