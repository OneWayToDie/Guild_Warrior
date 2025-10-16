#pragma once
#include<iostream>
using namespace std;

///////////////////////////////////////////////////////////////
//						TAKE/GIVE PARAMETERS				 //
///////////////////////////////////////////////////////////////
#define WARRIOR_TAKE_PARAMETERS const std::string& name, int health, int base_attack, int level, int exp, int exp_for_level_up
#define WARRIOR_GIVE_PARAMETERS name, health, base_attack, level, exp, exp_for_level_up
///////////////////////////////////////////////////////////////
//							class Warrior					 //
///////////////////////////////////////////////////////////////
class Warrior
{
protected:
	std::string name;
	int health;
	int base_attack;
	int level = 1;			//Уровень
	int exp;				//опыт
	int exp_for_level_up;	//Опыт для повышения уровня
	int max_health;
public:
	///////////////////////////////////////////////////////////////
	//							get/set methods					 //
	///////////////////////////////////////////////////////////////
	const std::string& get_name()const
	{
		return name;
	}
	int get_health()const
	{
		return health;
	}
	int get_base_attack()const
	{
		return base_attack;
	}
	int get_level()const
	{
		return level;
	}
	int get_exp()const
	{
		return exp;
	}
	int get_exp_for_level_up()const
	{
		return exp_for_level_up;
	}
	int get_max_health()const
	{
		return max_health;
	}
	void set_name(const std::string& name)
	{
		this->name = name;
	}
	void set_health(int health)
	{
		this->health = health;
	}
	void set_base_attack(int base_attack)
	{
		this->base_attack = base_attack;
	}
	void set_level(int level)
	{
		this->level = level;
	}
	void set_exp(int exp)
	{
		this->exp = exp;
	}
	void set_exp_for_level_up(int exp_for_level_up)
	{
		this->exp_for_level_up = exp_for_level_up;
	}
	void set_max_health(int max_health)
	{
		this->max_health = max_health;
	}
	///////////////////////////////////////////////////////////////
	//							constructors					 //
	///////////////////////////////////////////////////////////////
	Warrior(WARRIOR_TAKE_PARAMETERS)
	{
		set_name(name);
		set_health(health);
		set_base_attack(base_attack);
		set_level(level);
		set_exp(exp);
		set_exp_for_level_up(exp_for_level_up);
		this->max_health = health;
	}
	///////////////////////////////////////////////////////////////
	//							Methods							 //
	///////////////////////////////////////////////////////////////
	void gain_exp(int amount)
	{
		exp += amount;
		while (exp >= exp_for_level_up && level < 60)
		{
			level_up();
		}
	}
	void level_up()
	{

		int old_level = level;
		int old_health = health;
		int old_max_health = max_health;
		int old_attack = base_attack;
		level++;
		exp -= exp_for_level_up;
		if (level < 5)
		{
			exp_for_level_up = 50;
			max_health += 8;
			base_attack += 3;
		}
		else if (level >= 5 && level < 10)
		{
			exp_for_level_up = 150;
			max_health += 16;
			base_attack += 6;
		}
		else if (level >= 10 && level < 15)
		{
			exp_for_level_up = 250;
			max_health += 32;
			base_attack += 12;
		}
		else if (level >= 15 && level < 20)
		{
			exp_for_level_up = 400;
			max_health += 64;
			base_attack += 24;
		}
		else if (level >= 20 && level < 25)
		{
			exp_for_level_up = 600;
			max_health += 128;
			base_attack += 48;
		}
		else if (level >= 25 && level < 30)
		{
			exp_for_level_up = 800;
			max_health += 256;
			base_attack += 96;
		}
		else if (level >= 30 && level < 40)
		{
			exp_for_level_up = 1400;
			max_health += 512;
			base_attack += 192;
		}
		else if (level >= 40 && level < 50)
		{
			exp_for_level_up = 2500;
			max_health += 768;
			base_attack += 288;
		}
		else if (level >= 50 && level < 60)
		{
			exp_for_level_up = 10000;
			max_health += 1024;
			base_attack += 384;
		}
		else
		{
			level = 60;
			exp_for_level_up = 0;
			cout << name << " повышен до максимального уровня" << endl;
			return;
		}
		health = max_health;
		cout << name << " повысил свой уровень до " << level << endl;
	}
	virtual void attack(Warrior* target) = 0;	// Чисто виртуальные функции, которые я с нуля буду реализовывать в других классах
	virtual void use_ability(Warrior* target = nullptr) = 0;
	virtual void take_damage(int damage)	//Метод получения урона по умолчанию для всех, кроме война, так как у него есть броня, от которой и исходит получаемый урон
	{
		health -= damage;
		if (is_alive() == false)
		{
			cout << name << " пал в бою" << endl;
		}
	}
	virtual bool is_alive()	//Метод проверки на жизнеспособность бойцов
	{
		return health > 0;
	}
	virtual void info()const
	{
		cout << name << "(Ур." << level << " Здоровье: " << health << "/" << max_health << ", Атака: " << base_attack << ", Опыт: " << exp << "/" << exp_for_level_up << ")";
	}
};