#include "Terrain.h"
//
//’nŒ`
//
//2018/04/19
//Ito Motoya

Terrain::Terrain()
	: m_terrain(nullptr)
	, m_objFile(nullptr)
{
}

Terrain::~Terrain()
{
	delete m_terrain;
}

void Terrain::UpdateO()
{
	m_terrain->UpdateO();
}

void Terrain::Render()
{
	m_terrain->Render();
}

void Terrain::CreateTerrain(float gridNam, int vertical, int horizontal)
{
	m_terrain = new Obj3D();
	m_terrain->LoadModel(m_objFile);
	m_terrain->SetTranslation(Vector3(horizontal - (gridNam / 2 - 0.5f), m_height, vertical - (gridNam / 2 - 0.5f)));
	m_terrain->SetScale(Vector3(1.0f, 1.0f, 1.0f));
}
