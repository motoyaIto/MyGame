//
//�{�^���R�}���h�Ɠo�^�p�n���h���[
//
//Ito Motoya
//2017/12/03
//
#pragma once

#include <d3d11_1.h>
#include <Keyboard.h>

#include "Comand//Comand.h"
#include "..//..//KeyboradUtil//KeyboradUtil.h"

class UpComand : public Comand
{
public:
	void Execute(Actor& actor) override { actor.Up(); }
};

class DownComand : public Comand
{
public:
	void Execute(Actor& actor) override { actor.Down(); }
};

class RightComand : public Comand
{
public:
	void Execute(Actor& actor) override { actor.Right(); }
};

class LeftComand : public Comand
{
public:
	void Execute(Actor& actor) override { actor.Left(); }
};

//---------------------------------------------------------------

class InputHandler
{
private:
	Comand* buttonUp;
	Comand* buttonDown;
	Comand* buttonRight;
	Comand* buttonLeft;
	
	DirectX::Keyboard::State m_oldKeyState;

public:
	void HandleInput(Actor& Actor, KeyboradUtil& keybord);

public://setter
	void SetComandUp(Comand* cmd) { buttonUp = cmd; }//��L�[
	void SetComandDown(Comand* cmd) { buttonDown = cmd; }//���L�[
	void SetComandRight(Comand* cmd) { buttonRight = cmd; }//�E�L�[
	void SetComandLeft(Comand* cmd) { buttonLeft = cmd; }//���L�[
	
};