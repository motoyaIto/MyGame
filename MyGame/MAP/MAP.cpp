//
//map用
//
//2017/11/06
//Ito Motoya
#include "MAP.h"


#include <fstream>
#include <sstream>
#include <string>

#include <assert.h>
#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

const float MAP::SENTERPOS = 0.5f;

//内部関数============================================================
/// <summary>
/// CSVファイルの読み込み
/// </summary>
/// <param name="fileNumber">ファイルアドレス</param>
void MAP::GetCSVFile(int fileNumber)
{
	//ファイル読み込み
	ifstream* ifs;
	ifs = new ifstream;
	ifs->open("MAP1.csv", ios::in);

	//読み込みなかったら
	if (!ifs)
	{
		//エラー
		MessageBox(0, L"File acquisition failed", NULL, MB_OK);
		return;
	}

	//1行ずつ読み込む
	string str;
	string CSVData;
	int count = 0;
	int countGrid = 0;
	while (getline(*ifs, str))
	{
		string token;
		istringstream stream(str);//文字列読み込み

		while (getline(stream, token, ','))//','までの文字列を取得
		{
			CSVData += token;

			count++;
		}
		countGrid++;
	}
	m_gridNam = countGrid;

	m_map = new int[count];
	for (int i = 0; i < count; i++)
	{
		m_map[i] = CSVData[i] - 48;
	}
}

/// <summary>
/// オブジェクトの作成
/// </summary>
/// <param name="obj">オブジェクト</param>
/// <param name="objFile">オブジェクトファイル</param>
/// <param name="i">for文1</param>
/// <param name="j">for文2</param>
/// <param name="count">オブジェクトカウンター</param>
/// <param name="height">高さ</param>
void MAP::CreateObj(Obj3D* obj, const wchar_t * objFile, int i, int j, int& count, float height)
{
	obj[count].LoadModel(objFile);
	obj[count].SetTranslation(Vector3(j - (m_gridNam / 2 - 0.5f), height, i - (m_gridNam / 2 - 0.5f)));
	obj[count].SetScale(Vector3(1.0f, 1.0f, 1.0f));

	count++;
}

//public関数===========================================================
MAP::MAP()
	: m_countN(0)
	, m_countMount1(0),m_countMount2(0)
	, m_countPOND(0), m_countPOISON_SWAMP(0)

	, m_CSVDateNam(0) , m_map(nullptr), m_gridNam(0)

	, m_mount1(nullptr), m_mount2(nullptr)
	, m_pond(nullptr), m_PoisonSwamp(nullptr)
{
	
}

MAP::~MAP()
{
	delete[] m_map;
	delete[] m_mount1;
	delete[] m_mount2;
	delete[] m_pond;
	delete[] m_PoisonSwamp;
}

/// <summary>
/// 初期化
/// </summary>
void MAP::Initialize()
{
	this->GetCSVFile(1);

	//各数をカウント
	for (int i = 0; i < m_gridNam * m_gridNam; i++)
	{
		switch (m_map[i])
		{
		case N://何もなし
			m_countN++;
			break;

		case MOUNT1://山1
		case MOUNT2://山2
			m_countMount1++;

			if (m_map[i] >= MOUNT2)
			{
				m_countMount2++;
			}
			break;

		case POND://池
			m_countPOND++;
			break;

		case POISON_SWAMP://毒沼
			m_countPOISON_SWAMP++;
			break;
		}
	}

	//オブジェクトの初期化
	m_mount1 = new Obj3D[m_countMount1 + 1];
	m_countMount1 = 0;

	m_mount2 = new Obj3D[m_countMount2];
	m_countMount2 = 0;

	m_pond = new Obj3D[m_countPOND];
	m_countPOND = 0;

	m_PoisonSwamp = new Obj3D[m_countPOISON_SWAMP];
	m_countPOISON_SWAMP = 0;

	//オブジェクトの作成
	for (int i = 0; i < m_gridNam; i++)//縦
	{
		for (int j = 0; j < m_gridNam; j++)//横
		{
			switch (m_map[i * m_gridNam + j])
			{
			case N://何もなし
				m_countN++;
				break;

			case MOUNT1://山1
			case MOUNT2://山2
				this->CreateObj(m_mount1, L"Resources/Mount1.cmo", i, j, m_countMount1, 0.0f);

				if (m_map[i * m_gridNam + j] >= MOUNT2)
				{
					this->CreateObj(m_mount2, L"Resources/Mount2.cmo", i, j, m_countMount2, 0.5f);
				}
				
				break;

			case POND://池
				this->CreateObj(m_pond, L"Resources/Pond.cmo", i, j, m_countPOND, 0.0f);

				break;

			case POISON_SWAMP://毒沼
				this->CreateObj(m_PoisonSwamp, L"Resources/PoisonSwamp.cmo", i, j, m_countPOISON_SWAMP, 0.0f);

				break;
			}
		}
	}

}

/// <summary>
/// 更新
/// </summary>
void MAP::Update()
{
	//山1
	for (int i = 0; i < m_countMount1; i++)
	{
		m_mount1[i].UpdateO();
	}

	//山2
	for (int i = 0; i < m_countMount2; i++)
	{
		m_mount2[i].UpdateO();
	}

	//池
	for (int i = 0; i < m_countPOND; i++)
	{
		m_pond[i].UpdateO();
	}

	//毒沼
	for (int i = 0; i < m_countPOISON_SWAMP; i++)
	{
		m_PoisonSwamp[i].UpdateO();
	}
}

/// <summary>
/// 描画
/// </summary>
void MAP::Render()
{
	//山1
	for (int i = 0; i < m_countMount1; i++)
	{
		m_mount1[i].Render();
	}

	//山2
	for (int i = 0; i < m_countMount2; i++)
	{
		m_mount2[i].Render();
	}

	//池
	for (int i = 0; i < m_countPOND; i++)
	{
		m_pond[i].Render();
	}

	//毒沼
	for (int i = 0; i < m_countPOISON_SWAMP; i++)
	{
		m_PoisonSwamp[i].Render();
	}
}
