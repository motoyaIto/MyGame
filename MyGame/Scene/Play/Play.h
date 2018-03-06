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
#include "..//..//Flag//Flag.h"

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
	
	
	

	GameManager m_gameManager;//�Q�[���̃R���g���[���[

	MAP m_map;//�}�b�v
	Flag* m_flag;
	Grid m_grid;//�O���b�g
	Glound m_glound;//��

	Player* m_player;//�v���C���[
	PlayerState* m_playerState;//�v���C���[�̃R���g���[�����
	
	Dice m_dice[DICENAM];//�T�C�R��
	int m_countDice;//�_�C�X����̈ړ�

	//Obj3D* m_RedFlag;		//�t���O(��)
	//Obj3D* m_BlueFlag;		//�t���O(��)
	//Obj3D* m_GreenFlag;		//�t���O(��)
	//Obj3D* m_yerowllFlag;	//�t���O(���F)

public:
	Play();
	~Play();

	void Initialize() override;
	void Update() override;
	void Render() override;

};