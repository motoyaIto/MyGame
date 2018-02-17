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
	using Vector3 = DirectX::SimpleMath::Vector3;

private:
	static const float SENTERPOS;
	
public:
	enum MAP_NAME
	{
		N,			//何もなし
		MOUNT1,		//山1
		MOUNT2,
		POND = 5,	//池
		POISON_SWAMP//毒沼

	};

	

private:
	//各オブジェクトの数
	int m_countN;
	int m_countMount1;
	int m_countMount2;
	int m_countPOND;
	int m_countPOISON_SWAMP;

	int m_CSVDateNam;	//CSVデータの合計
	int* m_map;			//マップデータ
	float m_gridNam;	//一列の長さ
	int* m_flagMap;		//フラグマップ
	
	//各オブジェクト
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
	int GetMapDate(int i) { return m_map[i]; }

public://setter
	void SetFlagMap(FLAGMAP_TIP tip, Vector3 pos, int& countDice)
	{ 
		int gritNamHalf = m_gridNam / 2;		//一列当たりのマスの数の半分
		int datapos = gritNamHalf + pos.x + (((gritNamHalf + pos.z)) * m_gridNam);

		//毒沼だったら
		if (m_map[datapos] == POISON_SWAMP)
		{
			countDice--;
		}

		//自陣でない場合
		if (m_flagMap[datapos] == FLAGMAP_TIP::NONE)
		{
			pos.y -= 0.5;
			//m_flagRed[datapos].SetTranslation(pos);
			//m_flagMap[datapos] = tip;

			return;
		}

		countDice++;//自陣なので消費しない
	}
};