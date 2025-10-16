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
	bool ability_used = false;	//Проверка на то, была ли использована способность, ибо броню за весь бой можно усилить только один раз
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
			cout << name << "Враг повржен, это бессмысленно, сударь" << endl;	//Проверка на то, жив ли противник
			return;
		}
		int damage = base_attack;

		cout << name << " Делает удар мечом по головушке своего оппонента " << endl;
		target->take_damage(damage);		//Передаём урон нашему оппоненту
	}
	void take_damage(int damage) override
	{

		if (ability_used == true)	//Если способность была использована перед раундом - уменьшаем входящий урон взависимости от брони, и уменьшаем её после раунда, возвращая её к начальному значению
		{
			int fact_damage = max(damage - armor, 1);
			health -= fact_damage;
			armor -= 5;
			ability_used = false;
		}
		else	// если способность не была использована перед раундом, то бой идёт в привычном темпе
		{
			int fact_damage = max(damage - armor, 1);
			health -= fact_damage;
		}
	}
	void use_ability(Warrior* target = nullptr) override	// Используем способность и увеличиваем значение брони
	{
		armor += 5;
		ability_used = true;
		cout << name << " усилил свою броню, теперь её значение = " << armor << endl;
	}
	virtual void info()const
	{
		Warrior::info();
		cout << ", Броня: " << armor << endl;	//Метод для вывода инфы для танка(рыцаря)
	}
};