//
//play�V�[��
//
//2017/11/27
//Ito Motoya
#pragma once

#include "..//Scene.h"

#include "..//..//DirectXResourse//Line//Grid//Grid.h"

#include "..//..//Glound//Glound.h"
#include "..//..//MAP//MAP.h"
#include "..//..//Player//Player.h"
#include "..//..//Dice//Dice.h"

#include "..//..//DirectXResourse//Obj3D//Obj3D.h"

class Play : public Scene 
{
private:
	static const int PLAYERNAM;

	static const int DICENAM = 2;

	enum GameManager
	{
		ROLLDICE,//�T�C�R����U��
		MOVESERECT,//�ړ����I��
		MOVE,//�ړ�
		MAPGIMMICK//�M�~�b�N
	};

	struct PlayerState
	{
		bool playing;
		bool RollTwoDice;
	};
	
	enum FLAGMAP_TIP
	{
		NONE,
		RED,	//��
		BLUE,	//��
		GREEN,	//��
		YELLOW,	//���F
	};

	GameManager m_gameManager;//�Q�[���̃R���g���[���[

	MAP m_map;//�}�b�v
	FLAGMAP_TIP* m_flagMAP;
	Grid m_grid;//�O���b�g
	Glound m_glound;//��

	Player* m_player;//�v���C���[
	PlayerState* m_playerState;//�v���C���[�̃R���g���[�����
	
	Dice m_dice[DICENAM];//�T�C�R��
	int m_countDice;//�_�C�X����̈ړ�

	Obj3D* m_RedFlag;
	Obj3D* m_BlueFlag;
	Obj3D* m_GreenFlag;
	Obj3D* m_yerowllFlag;

public:
	Play();
	~Play();

	void Initialize() override;
	void Update() override;
	void Render() override;

};