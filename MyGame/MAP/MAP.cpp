//
//map�p
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

//�����֐�============================================================
/// <summary>
/// CSV�t�@�C���̓ǂݍ���
/// </summary>
/// <param name="fileNumber">�t�@�C���A�h���X</param>
void MAP::GetCSVFile(int fileNumber)
{
	//�t�@�C���ǂݍ���
	ifstream* ifs;
	ifs = new ifstream;
	ifs->open("MAP1.csv", ios::in);

	//�ǂݍ��݂Ȃ�������
	if (!ifs)
	{
		//�G���[
		MessageBox(0, L"File acquisition failed", NULL, MB_OK);
		return;
	}

	//1�s���ǂݍ���
	string str;
	string CSVData;
	int count = 0;
	int countGrid = 0;
	while (getline(*ifs, str))
	{
		string token;
		istringstream stream(str);//������ǂݍ���

		while (getline(stream, token, ','))//','�܂ł̕�������擾
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
/// �I�u�W�F�N�g�̍쐬
/// </summary>
/// <param name="obj">�I�u�W�F�N�g</param>
/// <param name="objFile">�I�u�W�F�N�g�t�@�C��</param>
/// <param name="i">for��1</param>
/// <param name="j">for��2</param>
/// <param name="count">�I�u�W�F�N�g�J�E���^�[</param>
/// <param name="height">����</param>
void MAP::CreateObj(Obj3D* obj, const wchar_t * objFile, int i, int j, int& count, float height)
{
	obj[count].LoadModel(objFile);
	obj[count].SetTranslation(Vector3(j - (m_gridNam / 2 - 0.5f), height, i - (m_gridNam / 2 - 0.5f)));
	obj[count].SetScale(Vector3(1.0f, 1.0f, 1.0f));

	count++;
}

//public�֐�===========================================================
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
/// ������
/// </summary>
void MAP::Initialize()
{
	this->GetCSVFile(1);

	//�e�����J�E���g
	for (int i = 0; i < m_gridNam * m_gridNam; i++)
	{
		switch (m_map[i])
		{
		case N://�����Ȃ�
			m_countN++;
			break;

		case MOUNT1://�R1
		case MOUNT2://�R2
			m_countMount1++;

			if (m_map[i] >= MOUNT2)
			{
				m_countMount2++;
			}
			break;

		case POND://�r
			m_countPOND++;
			break;

		case POISON_SWAMP://�ŏ�
			m_countPOISON_SWAMP++;
			break;
		}
	}

	//�I�u�W�F�N�g�̏�����
	m_mount1 = new Obj3D[m_countMount1 + 1];
	m_countMount1 = 0;

	m_mount2 = new Obj3D[m_countMount2];
	m_countMount2 = 0;

	m_pond = new Obj3D[m_countPOND];
	m_countPOND = 0;

	m_PoisonSwamp = new Obj3D[m_countPOISON_SWAMP];
	m_countPOISON_SWAMP = 0;

	//�I�u�W�F�N�g�̍쐬
	for (int i = 0; i < m_gridNam; i++)//�c
	{
		for (int j = 0; j < m_gridNam; j++)//��
		{
			switch (m_map[i * m_gridNam + j])
			{
			case N://�����Ȃ�
				m_countN++;
				break;

			case MOUNT1://�R1
			case MOUNT2://�R2
				this->CreateObj(m_mount1, L"Resources/Mount1.cmo", i, j, m_countMount1, 0.0f);

				if (m_map[i * m_gridNam + j] >= MOUNT2)
				{
					this->CreateObj(m_mount2, L"Resources/Mount2.cmo", i, j, m_countMount2, 0.5f);
				}
				
				break;

			case POND://�r
				this->CreateObj(m_pond, L"Resources/Pond.cmo", i, j, m_countPOND, 0.0f);

				break;

			case POISON_SWAMP://�ŏ�
				this->CreateObj(m_PoisonSwamp, L"Resources/PoisonSwamp.cmo", i, j, m_countPOISON_SWAMP, 0.0f);

				break;
			}
		}
	}

}

/// <summary>
/// �X�V
/// </summary>
void MAP::Update()
{
	//�R1
	for (int i = 0; i < m_countMount1; i++)
	{
		m_mount1[i].UpdateO();
	}

	//�R2
	for (int i = 0; i < m_countMount2; i++)
	{
		m_mount2[i].UpdateO();
	}

	//�r
	for (int i = 0; i < m_countPOND; i++)
	{
		m_pond[i].UpdateO();
	}

	//�ŏ�
	for (int i = 0; i < m_countPOISON_SWAMP; i++)
	{
		m_PoisonSwamp[i].UpdateO();
	}
}

/// <summary>
/// �`��
/// </summary>
void MAP::Render()
{
	//�R1
	for (int i = 0; i < m_countMount1; i++)
	{
		m_mount1[i].Render();
	}

	//�R2
	for (int i = 0; i < m_countMount2; i++)
	{
		m_mount2[i].Render();
	}

	//�r
	for (int i = 0; i < m_countPOND; i++)
	{
		m_pond[i].Render();
	}

	//�ŏ�
	for (int i = 0; i < m_countPOISON_SWAMP; i++)
	{
		m_PoisonSwamp[i].Render();
	}
}
