//
//�R�}���h�ꗗ�ƃR�}���h�̊��N���X
//
//Ito Motoya
//2017/12/03
#pragma once

class Actor
{
public:
	virtual void Up() = 0;//��ړ�
	virtual void Down() = 0;//���ړ�
	virtual void Right() = 0;//�E�ړ�
	virtual void Left() = 0;//���ړ�
};

class Comand
{
private:

public:
	virtual ~Comand(){}
	virtual void Execute(Actor& actor) = 0;
};