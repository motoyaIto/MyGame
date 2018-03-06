#include "Flag.h"
#include <SimpleMath.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;


Flag::Flag()
{
	m_type = FLAGMAP_TIP::NONE;
}

Flag::~Flag()
{
	
}

void Flag::Update()
{
	m_flag.UpdateQ();
}

void Flag::Render()
{
	m_flag.Render();
}

void Flag::CreateFlag(FLAGMAP_TIP FlagColor, int x, int y, int z)
{
	switch (FlagColor)
	{
	case FLAGMAP_TIP::RED://ê‘
		m_flag.LoadModel(L"Resources/RedFlag.cmo");
		m_flag.SetTranslation(Vector3(x, y, z));
		m_flag.SetScale(Vector3(0.1f, 0.1f, 0.1f));

		m_type = FLAGMAP_TIP::RED;
		break;

	case FLAGMAP_TIP::BLUE:	//ê¬
		m_flag.LoadModel(L"Resources/BlueFlag.cmo");
		m_flag.SetTranslation(Vector3(x, y, z));
		m_flag.SetScale(Vector3(0.1f, 0.1f, 0.1f));

		m_type = FLAGMAP_TIP::BLUE;
		break;

	case FLAGMAP_TIP::GREEN://óŒ
		m_flag.LoadModel(L"Resources/GreenFlag.cmo");
		m_flag.SetTranslation(Vector3(x, y, z));
		m_flag.SetScale(Vector3(0.1f, 0.1f, 0.1f));

		m_type = FLAGMAP_TIP::GREEN;
		break;

	case FLAGMAP_TIP::YELLOW://â©êF
		m_flag.LoadModel(L"Resources/YellowFlag.cmo");
		m_flag.SetTranslation(Vector3(x, y, z));
		m_flag.SetScale(Vector3(0.1f, 0.1f, 0.1f));

		m_type = FLAGMAP_TIP::YELLOW;
		break;
	}
}

