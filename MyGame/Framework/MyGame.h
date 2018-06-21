//
//MyGame用
//
//2017/06/21
//Ito Motoya

#pragma once
#ifndef MYGAME_DEFINED
#define MYGAME_DEFINED

#include "Game.h"

class MyGame : public Game
{
public:
	MyGame(int width, int height);
	~MyGame();

	//ゲームオブジェクトを初期化する
	void Initialize(int width, int height) override;


};
#endif // !MYGAME_DEFINED
