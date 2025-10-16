#pragma once
#include<iostream>
#include"Warrior.h"
using namespace std;

///////////////////////////////////////////////////////////////
//							class Knight					 //
///////////////////////////////////////////////////////////////
class Knight :public Warrior
{
	int armor;
	bool ability_used = false;	//�������� �� ��, ���� �� ������������ �����������, ��� ����� �� ���� ��� ����� ������� ������ ���� ���
public:
	///////////////////////////////////////////////////////////////
	//							get/set methods					 //
	///////////////////////////////////////////////////////////////
	int get_armor()const
	{
		return armor;
	}
	void set_armor(int armor)
	{
		this->armor = armor;
	}
	///////////////////////////////////////////////////////////////
	//							constructors					 //
	///////////////////////////////////////////////////////////////
	Knight(WARRIOR_TAKE_PARAMETERS, int armor) : Warrior(WARRIOR_GIVE_PARAMETERS)
	{
		set_armor(armor);
	}
	///////////////////////////////////////////////////////////////
	//							Methods							 //
	///////////////////////////////////////////////////////////////
	void attack(Warrior* target)override
	{
		if (target->is_alive() == false)
		{
			cout << name << "���� �������, ��� ������������, ������" << endl;	//�������� �� ��, ��� �� ���������
			return;
		}
		int damage = base_attack;

		cout << name << " ������ ���� ����� �� ��������� ������ ��������� " << endl;
		target->take_damage(damage);		//������� ���� ������ ���������
	}
	void take_damage(int damage) override
	{

		if (ability_used == true)	//���� ����������� ���� ������������ ����� ������� - ��������� �������� ���� ������������ �� �����, � ��������� � ����� ������, ��������� � � ���������� ��������
		{
			int fact_damage = max(damage - armor, 1);
			health -= fact_damage;
			armor -= 5;
			ability_used = false;
		}
		else	// ���� ����������� �� ���� ������������ ����� �������, �� ��� ��� � ��������� �����
		{
			int fact_damage = max(damage - armor, 1);
			health -= fact_damage;
		}
	}
	void use_ability(Warrior* target = nullptr) override	// ���������� ����������� � ����������� �������� �����
	{
		armor += 5;
		ability_used = true;
		cout << name << " ������ ���� �����, ������ � �������� = " << armor << endl;
	}
	virtual void info()const
	{
		Warrior::info();
		cout << ", �����: " << armor << endl;	//����� ��� ������ ���� ��� �����(������)
	}
};