//
//グラウンド
//
//ItoMotoya
//2017/11/02
#pragma once

#include <d3d11_1.h>

#include <SimpleMath.h>

#include "..//DirectXResourse//Obj3D//Obj3D.h"

class Glound
{
private:
	using Vector3 = DirectX::SimpleMath::Vector3;

private:
	Obj3D* m_glound;
	int m_wonRowNam;//マスの合計

public:
	Glound();
	~Glound();

	void Initialize();
	void Render();

public://getter

public://setter
	void SetWonRowNam(int nam) { m_wonRowNam = nam; }

};
