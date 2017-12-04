//
//コマンド一覧とコマンドの基底クラス
//
//Ito Motoya
//2017/12/03
#pragma once

class Actor
{
public:
	virtual void Up() = 0;//上移動
	virtual void Down() = 0;//下移動
	virtual void Right() = 0;//右移動
	virtual void Left() = 0;//左移動
};

class Comand
{
private:

public:
	virtual ~Comand(){}
	virtual void Execute(Actor& actor) = 0;
};