#pragma once
#include "..//DirectXResourse//Obj3D//Obj3D.h"
#include "..//Constant//Constant.h"

class Flag
{
private:
	Obj3D m_flag;
	FLAGMAP_TIP m_type;//ƒtƒ‰ƒO‚Ìó‘Ô
	
public:
	Flag();
	~Flag();

	void Update();
	void Render();

	void CreateFlag(FLAGMAP_TIP FlagColor, int x, int y, int z);

public:
	FLAGMAP_TIP GetFlagType() { return m_type; }

public:
	
};