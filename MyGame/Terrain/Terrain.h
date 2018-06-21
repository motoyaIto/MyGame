//
//地形
//
//2018/04/19
//Ito Motoya
#pragma once
#include "..//DirectXResourse//Obj3D//Obj3D.h"

class Terrain
{
protected:
	using Vector3 = DirectX::SimpleMath::Vector3;

protected:
	enum TERRAIN_TYPE
	{
		MOUNTAIN,
		POND,
		POISON_SWAMP,
	};


protected:
	Obj3D* m_terrain;

	const wchar_t* m_objFile;

	float m_height;


public:
	Terrain();
	virtual ~Terrain();

	virtual void TerrainInfluence() = 0;//地形の影響


	void UpdateO();
	void Render();
public://getter

public://setter
	void CreateTerrain(float gridNam, int vertical, int horizontal);//地形を作る

};