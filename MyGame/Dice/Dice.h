#pragma once

class Dice
{
private:
	int m_number;		//�T�C�R���̏o�Ă��
	int m_numsize;		//�T�C�R���̖ʂ̐�
public:
	//�R���X�g���N�^
	Dice();

	//�f�X�g���N�^
	~Dice();

	//�]����
	int roll();

	//�ڂ̎擾
	int getNumber();
};