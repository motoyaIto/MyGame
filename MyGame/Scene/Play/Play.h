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

class Play : public Scene 
{
private:
	MAP m_map;
	Grid m_grid;
	Glound m_glound;

	Player m_player;

public:
	Play();
	~Play();

	void Initialize() override;
	void Update() override;
	void Render() override;

};