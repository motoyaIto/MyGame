//
//ƒOƒ‰ƒEƒ“ƒh
//
//ItoMotoya
//2017/11/02
#include "Glound.h"


Glound::Glound()
	: m_glound(nullptr)
	, m_wonRowNam(20)
{

}

Glound::~Glound()
{
	delete[] m_glound;
}

void Glound::Initialize()
{
	m_glound = new Obj3D[m_wonRowNam * m_wonRowNam];

	for (int i = 0; i < m_wonRowNam; i++)//c
	{
		for (int j = 0; j < m_wonRowNam; j++)//‰¡
		{
			m_glound[i * m_wonRowNam + j].LoadModel(L"Resources/Ground.cmo");
			m_glound[i * m_wonRowNam + j].SetTranslation(Vector3(j - (m_wonRowNam / 2 - 0.5f), 0.0f, i - (m_wonRowNam / 2 - 0.5f)));
			m_glound[i * m_wonRowNam + j].SetScale(Vector3(1.0f, 1.0f, 1.0f));
		}
	}
}

void Glound::Render()
{
	for (int i = 0; i < m_wonRowNam * m_wonRowNam; i++)
	{
		m_glound[i].UpdateO();
		m_glound[i].Render();
	}
	
}
