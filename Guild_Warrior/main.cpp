#include<iostream>
#include<Windows.h>
#include<time.h>
using namespace std;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"
///////////////////////////////////////////////////////////////
//						TAKE/GIVE PARAMETERS				 //
///////////////////////////////////////////////////////////////
#define WARRIOR_TAKE_PARAMETERS const std::string& name, int health, int base_attack
#define WARRIOR_GIVE_PARAMETERS name, health, base_attack
///////////////////////////////////////////////////////////////
//							class Warrior					 //
///////////////////////////////////////////////////////////////
class Warrior
{
protected:
	std::string name;
	int health;
	int base_attack;
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
	///////////////////////////////////////////////////////////////
	//							constructors					 //
	///////////////////////////////////////////////////////////////
	Warrior(WARRIOR_TAKE_PARAMETERS)
	{
		set_name(name);
		set_health(health);
		set_base_attack(base_attack);
	}
	///////////////////////////////////////////////////////////////
	//							Methods							 //
	///////////////////////////////////////////////////////////////
	virtual void attack(Warrior* target) = 0;
	virtual void use_ability(Warrior* target = nullptr) = 0;
	virtual void take_damage(int damage)
	{
		health -= damage;
		if (is_alive() == false)
		{
			cout << name << " пал в бою";
		}
	}
	virtual bool is_alive()
	{
		return health > 0;
	}
	void info()const
	{
		cout << name << "(" << "Здоровье:" << health << ")" << endl;
	}
};
///////////////////////////////////////////////////////////////
//							class Knight					 //
///////////////////////////////////////////////////////////////
class Knight :public Warrior
{
	int armor;
	bool ability_used = false;
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
			cout << name << "Враг повржен, это бессмысленно, сударь" << endl;
			return;
		}
		int damage = base_attack;
		target->take_damage(damage);
	}
	void take_damage(int damage) override
	{
		
		if (ability_used == true)
		{
			int fact_damage = max(damage - armor, 1);
			health -= fact_damage;
			armor -= 5;
			ability_used = false;
		}
		else
		{
			int fact_damage = max(damage - armor, 1);
			health -= fact_damage;
		}

		if (is_alive() == false)
			cout << "Рыцарь мертв, бой окончен" << endl;
	}
	void use_ability(Warrior* target = nullptr) override
	{
		armor += 5;
		ability_used = true;
		cout << name << " усилил свою броню, теперь её значение = " << armor << endl;
	}
};

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
		if (target->is_alive() == false)
		{
			cout << name << "Враг повержен, это бессмысленно, сударь" << endl;
			return;
		}
		if (quiver > 0)
		{
			damage = base_attack;
			quiver -= 1;
			cout << name << " произвёл выстрел, стрел осталось: " << quiver << endl;
		}
		else
		{
			damage = 1;
			cout << name << " бьёт луком по башке" << endl;
		}
		target->take_damage(damage);
	}
	void use_ability(Warrior* target) override
	{
		if (quiver < 3)
		{
			cout << "Способность недоступна" << endl;
			return;
		}
		if (target->is_alive() == false) 
		{
			cout << "Нельзя атаковать мёртвого врага!" << endl;
			return;
		}
		quiver -= 3;
		int damage = base_attack * 2;
		cout << name << "Использует способность \"Меткий глаз\" и наносит двойной урон - " << damage << " единиц урона" << endl;
		target->take_damage(damage);
	}
};

///////////////////////////////////////////////////////////////
//							class Wizard					 //
///////////////////////////////////////////////////////////////

class Wizard :public Warrior
{
	int mana;
public:
	///////////////////////////////////////////////////////////////
	//							get/set methods					 //
	///////////////////////////////////////////////////////////////
	int get_mana()const
	{
		return mana;
	}
	void set_mana(int mana)
	{
		this->mana = mana;
	}
	///////////////////////////////////////////////////////////////
	//							Constructors					 //
	///////////////////////////////////////////////////////////////
	Wizard(WARRIOR_TAKE_PARAMETERS, int mana) :Warrior(WARRIOR_GIVE_PARAMETERS)
	{
		set_mana(mana);
	}
	///////////////////////////////////////////////////////////////
	//							Methods							 //
	///////////////////////////////////////////////////////////////

};


















void main()
{

}
