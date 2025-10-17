#pragma once
#include<iostream>
#include"Warrior.h"
using namespace std;

///////////////////////////////////////////////////////////////
//							class Archer					 //
///////////////////////////////////////////////////////////////
class Archer :public Warrior
{
	int quiver;	//колчан со стрелами
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
		if (target->is_alive() == false)	//Проверяем на жизнеспоосбность оппонента
		{
			cout << name << "Враг повержен, это бессмысленно, сударь" << endl;
			return;
		}
		if (quiver > 0)	//Проверяем наличие стрел в колчане, если есть - делаем выстрел и убираем одну стрелу из колчана
		{
			damage = base_attack;
			quiver -= 1;
			cout << name << " произвёл выстрел, стрел осталось: " << quiver << endl;
		}
		else	// если стрел нет, бьём луком по тыкве, но так как это лучник(они как правило доходяги XD) урон будет крайне незначительным :)
		{
			damage = 1;
			cout << name << " бьёт луком по башке" << endl;
		}
		target->take_damage(damage);	// Передаём урон цели
	}
	void use_ability(Warrior* target) override
	{
		if (quiver < 3)	//если стрел в колчане меньеш 3 - мы не можем использовать способность
		{
			cout << "Способность недоступна" << endl;
			return;
		}
		if (target->is_alive() == false) //Проверяем жизнеспособность противника
		{
			cout << "Нельзя атаковать мёртвого врага!" << endl;
			return;
		}
		quiver -= 3;	//Если стрел хватало в колчане - забирали три стрелы, и производили двоёной урон от базовой атаки
		int damage = base_attack * 2;
		cout << name << " Использует способность \"Меткий глаз\" и наносит двойной урон - " << damage << " единиц урона" << endl;
		target->take_damage(damage);	//Передали урон по цели
	}
	virtual void info()const
	{
		Warrior::info();
		cout << ", Стрел в колчане: " << quiver << endl;
	}
};