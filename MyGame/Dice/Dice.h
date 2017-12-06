#pragma once

class Dice
{
private:
	int m_number;		//サイコロの出てる目
	int m_numsize;		//サイコロの面の数
public:
	//コンストラクタ
	Dice();

	//デストラクタ
	~Dice();

	//転がる
	int roll();

	//目の取得
	int getNumber();
};