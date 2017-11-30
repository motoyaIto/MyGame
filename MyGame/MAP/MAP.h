//
//map用
//
//2017/11/06
//Ito Motoya
#pragma once

#include"..//DirectXResourse//Obj3D//Obj3D.h"

class MAP
{
private:
	static const float SENTERPOS;
	
private:
	enum MAP_NAME
	{
		N,			//何もなし
		MOUNT1,		//山1
		MOUNT2,
		POND = 5,	//池
		POISON_SWAMP//毒沼

	};

private:
	int m_countN;
	int m_countMount1;
	int m_countMount2;
	int m_countPOND;
	int m_countPOISON_SWAMP;

	int m_CSVDateNam;
	int* m_map;
	int m_gridNam;
	

	Obj3D* m_mount1;
	Obj3D* m_mount2;
	Obj3D* m_pond;
	Obj3D* m_PoisonSwamp;

private://内部関数
	void GetCSVFile(int fileNumber);// CSVファイルの読み込み

	// オブジェクトの作成
	void CreateObj(Obj3D* obj, const wchar_t * objFile, int i, int j, int& count, float height);
	
	

public:
	MAP();
	~MAP();

	void Initialize();
	void Update();
	void Render();

public://getter
	int GetGridNam() { return m_gridNam; }
public://setter


};