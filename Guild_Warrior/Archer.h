#pragma once
#include<iostream>
#include"Warrior.h"
using namespace std;

///////////////////////////////////////////////////////////////
//							class Archer					 //
///////////////////////////////////////////////////////////////
class Archer :public Warrior
{
	int quiver;	//������ �� ��������
public:
	///////////////////////////////////////////////////////////////
	//							get/set methods					 //
	///////////////////////////////////////////////////////////////
	int get_quiver()const
	{
		return quiver;
	}
	void set_quiver(int quiver)
	{
		this->quiver = quiver;
	}
	///////////////////////////////////////////////////////////////
	//							constructors					 //
	///////////////////////////////////////////////////////////////
	Archer(WARRIOR_TAKE_PARAMETERS, int quiver) : Warrior(WARRIOR_GIVE_PARAMETERS)
	{
		set_quiver(quiver);
	}
	///////////////////////////////////////////////////////////////
	//							Methods							 //
	///////////////////////////////////////////////////////////////
	void attack(Warrior* target) override
	{
		int damage;
		if (target->is_alive() == false)	//��������� �� ���������������� ���������
		{
			cout << name << "���� ��������, ��� ������������, ������" << endl;
			return;
		}
		if (quiver > 0)	//��������� ������� ����� � �������, ���� ���� - ������ ������� � ������� ���� ������ �� �������
		{
			damage = base_attack;
			quiver -= 1;
			cout << name << " ������� �������, ����� ��������: " << quiver << endl;
		}
		else	// ���� ����� ���, ���� ����� �� �����, �� ��� ��� ��� ������(��� ��� ������� �������� XD) ���� ����� ������ �������������� :)
		{
			damage = 1;
			cout << name << " ���� ����� �� �����" << endl;
		}
		target->take_damage(damage);	// ������� ���� ����
	}
	void use_ability(Warrior* target) override
	{
		if (quiver < 3)	//���� ����� � ������� ������ 3 - �� �� ����� ������������ �����������
		{
			cout << "����������� ����������" << endl;
			return;
		}
		if (target->is_alive() == false) //��������� ���������������� ����������
		{
			cout << "������ ��������� ������� �����!" << endl;
			return;
		}
		quiver -= 3;	//���� ����� ������� � ������� - �������� ��� ������, � ����������� ������ ���� �� ������� �����
		int damage = base_attack * 2;
		cout << name << " ���������� ����������� \"������ ����\" � ������� ������� ���� - " << damage << " ������ �����" << endl;
		target->take_damage(damage);	//�������� ���� �� ����
	}
	virtual void info()const
	{
		Warrior::info();
		cout << ", ����� � �������: " << quiver << endl;
	}
};