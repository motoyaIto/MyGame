//
//map�p
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
		N,			//�����Ȃ�
		MOUNT1,		//�R1
		MOUNT2,
		POND = 5,	//�r
		POISON_SWAMP//�ŏ�

	};

	

private:
	//�e�I�u�W�F�N�g�̐�
	int m_countN;
	int m_countMount1;
	int m_countMount2;
	int m_countPOND;
	int m_countPOISON_SWAMP;

	int m_CSVDateNam;	//CSV�f�[�^�̍��v
	int* m_map;			//�}�b�v�f�[�^
	float m_gridNam;	//���̒���
	int* m_flagMap;		//�t���O�}�b�v
	
	//�e�I�u�W�F�N�g
	Obj3D* m_mount1;
	Obj3D* m_mount2;
	Obj3D* m_pond;
	Obj3D* m_PoisonSwamp;

private://�����֐�
	void GetCSVFile(int fileNumber);// CSV�t�@�C���̓ǂݍ���

	// �I�u�W�F�N�g�̍쐬
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
		int gritNamHalf = m_gridNam / 2;		//��񓖂���̃}�X�̐��̔���
		int datapos = gritNamHalf + pos.x + (((gritNamHalf + pos.z)) * m_gridNam);

		//�ŏ���������
		if (m_map[datapos] == POISON_SWAMP)
		{
			countDice--;
		}

		//���w�łȂ��ꍇ
		if (m_flagMap[datapos] == FLAGMAP_TIP::NONE)
		{
			pos.y -= 0.5;
			//m_flagRed[datapos].SetTranslation(pos);
			//m_flagMap[datapos] = tip;

			return;
		}

		countDice++;//���w�Ȃ̂ŏ���Ȃ�
	}
};