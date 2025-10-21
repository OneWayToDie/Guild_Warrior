#include<iostream>
using namespace std;

#define delimiter "\n-------------------------------------------------------------\n"
#define tab

#define MAIN_HEROES_TAKE_PARAMETERS  const std::string& name, int health, int max_health, double movement_speed, double attack_speed, int armor, int crit_chance, int crit_damage, int physic_resist, int magic_resist, int lvl, int exp, int exp_for_lvl_up
#define MAIN_HEROES_GIVE_PARAMETERS	 name, health, max_health, movement_speed, attack_speed, armor, crit_chance, crit_damage, physic_resist, magic_resist, lvl, exp, exp_for_lvl_up
#define WARRIOR_TAKE_PARAMETERS 	 int physic_attack,	int taunt, int block_chance, int dodge_chance
#define WARRIOR_GIVE_PARAMETERS 	 physic_attack, taunt, block_chance, dodge_chance

//////////////////////////////////////////////////////////////////////////////////////////////
////////////								Damage_Classes					  	  ////////////
//////////////////////////////////////////////////////////////////////////////////////////////
class PhysicalDamage
{
protected:
	int physic_attack;
public:
	virtual int get_physic_attack() const = 0;
	virtual void set_physic_attack(int physic_attack) = 0;
	virtual int calculate_physical_crit(int base_damage) const = 0;
};

class MagicDamage
{
protected:
	int magic_attack;
	int mana;
public:
	virtual int get_magic_attack() const = 0;
	virtual void set_magic_attack(int magic_attack) = 0;
	virtual int get_mana() const = 0;
	virtual void set_mana(int mana) = 0;
	virtual int calculate_magical_crit(int base_damage) const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////
////////////								Main_Heroes						  	  ////////////
//////////////////////////////////////////////////////////////////////////////////////////////
class Main_Heroes	//Реализую абстрактный класс со свойствами персонажа
{
protected:
	std::string name;
	int health;
	int max_health;
	double movement_speed;
	double attack_speed;
	int armor;
	int crit_chance;
	int crit_damage;
	int physic_resist;
	int magic_resist;
	int lvl;
	int exp;
	int exp_for_lvl_up;
public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							get/set methods						  	  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	const std::string& get_name()const
	{
		return name;
	}
	int get_health()const
	{
		return health;
	}
	int get_max_health()const
	{
		return max_health;
	}
	double get_movement_speed()const
	{
		return movement_speed;
	}
	double get_attack_speed()const
	{
		return attack_speed;
	}
	int get_armor()const
	{
		return armor;
	}
	int get_crit_chance()const
	{
		return crit_chance;
	}
	int get_crit_damage()const
	{
		return crit_damage;
	}
	int get_physic_resist()const
	{
		return physic_resist;
	}
	int get_magic_resist()const
	{
		return magic_resist;
	}
	int get_lvl()const
	{
		return lvl;
	}
	int get_exp()const
	{
		return exp;
	}
	int get_exp_for_lvl_up()const
	{
		return exp_for_lvl_up;
	}
	void set_name(const std::string& name)
	{
		this->name = name;
	}
	void set_health(int health)
	{
		this->health = health;
	}
	void set_max_health(int max_health)
	{
		this->max_health = max_health;
	}
	void set_movement_speed(double movement_speed)
	{
		this->movement_speed = movement_speed;
	}
	void set_attack_speed(double attack_speed)
	{
		this->attack_speed = attack_speed;
	}
	void set_armor(int armor)
	{
		this->armor = armor;
	}
	void set_crit_chance(int crit_chance)
	{
		this->crit_chance = crit_chance;
	}
	void set_crit_damage(int crit_damage)
	{
		this->crit_damage = crit_damage;
	}
	void set_lvl(int lvl)
	{
		this->lvl = lvl;
	}
	void set_physic_resist(int physic_resist)
	{
		this->physic_resist = physic_resist;
	}
	void set_magic_resist(int magic_resist)
	{
		this->magic_resist = magic_resist;
	}
	void set_exp(int exp)
	{
		this->exp = exp;
	}
	void set_exp_for_lvl_up(int exp_for_lvl_up)
	{
		this->exp_for_lvl_up = exp_for_lvl_up;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							CONSTRUCTORS						  	  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	Main_Heroes(MAIN_HEROES_TAKE_PARAMETERS)
	{
		set_name(name);
		set_health(health);
		set_max_health(max_health);
		set_movement_speed(movement_speed);
		set_attack_speed(attack_speed);
		set_armor(armor);
		set_crit_chance(crit_chance);
		set_crit_damage(crit_damage);
		set_physic_resist(physic_resist);
		set_magic_resist(magic_resist);
		set_lvl(lvl);
		set_exp(exp);
		set_exp_for_lvl_up(exp_for_lvl_up);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							METHODS						  			  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	void Heroes_name(Main_Heroes* name)
	{
		std::string main_name;
		cout << "Введите имя вашего Персонажа: "; cin >> main_name;
		name->set_name(main_name);
	}
	void gain_exp(int amount)
	{
		exp += amount;
		while(exp >= exp_for_lvl_up)
		{
			level_up();
		}
	}
	virtual void level_up()
	{
		lvl++;
		exp -= exp_for_lvl_up;
		if (lvl >= 1 && lvl < 5)
		{
			exp_for_lvl_up = 150;
		}
		else if (lvl >= 5 && lvl < 10)
		{
			exp_for_lvl_up = 350;
		}
		else if (lvl >= 10 && lvl < 15)
		{
			exp_for_lvl_up = 550;
		}
		else if (lvl >= 15 && lvl < 20)
		{
			exp_for_lvl_up = 1050;
		}
		else if (lvl >= 20 && lvl < 25)
		{
			exp_for_lvl_up = 2050;
		}
		else if (lvl >= 25 && lvl < 30)
		{
			exp_for_lvl_up = 3600;
		}
		else if (lvl == 30)
		{
			cout << "Вы достигли вершины Олимпа, вам некуда стремиться" << endl;
		}
		health_recovery();	//После апа уровня - восстанавливаем потерянное здоровье
		cout << name << " повысил свой уровень до " << lvl << endl;
	}
	void health_recovery()
	{
		health = max_health;
	}
	bool is_alive()
	{
		return health > 0;
	}
	virtual void use_ability_1() const = 0;
	virtual void use_ability_2() const = 0;
	virtual void use_ability_passive() const = 0;
	virtual void use_ability_ultimate()  = 0;
	virtual void take_damage() const = 0;
	virtual void heavy_attack() const = 0;
	virtual void lvl_up_perks() const = 0;
	virtual void info()const = 0;
};

class Warrior :public Main_Heroes, public PhysicalDamage
{
protected:
	int physic_attack;
	int taunt;
	int block_chance;
	int dodge_chance;
public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							get/set methods						  	  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	int get_physic_attack()const
	{
		return physic_attack;
	}
	int get_taunt()const
	{
		return taunt;
	}
	int get_block_chance()const
	{
		return block_chance;
	}
	int get_dodge_chance()const
	{
		return dodge_chance;
	}
	void set_physic_attack(int physic_attack)
	{
		this->physic_attack = physic_attack;
	}
	void set_taunt(int taunt)
	{
		this->taunt = taunt;
	}
	void set_block_chance(int block_chance)
	{
		this->block_chance = block_chance;
	}
	void set_dodge_chance(int dodge_chance)
	{
		this->dodge_chance = dodge_chance;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							CONSTRUCTORS						  	  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	Warrior(MAIN_HEROES_TAKE_PARAMETERS, WARRIOR_TAKE_PARAMETERS) : Main_Heroes(MAIN_HEROES_GIVE_PARAMETERS)
	{
		set_physic_attack(physic_attack);
		set_taunt(taunt);
		set_block_chance(block_chance);
		set_dodge_chance(dodge_chance);
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							Calculate_crit				  			  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	int calculate_physical_crit(int base_damage)const override
	{
		if (rand() % 100 < get_crit_chance())
		{
			return base_damage * get_crit_damage() / 100;
		}
		return base_damage;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////						ABSTRACT_METHODS				  			  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	virtual void use_ability_1() const = 0;
	virtual void use_ability_2() const = 0;
	virtual void use_ability_passive() const = 0;
	virtual void use_ability_ultimate() = 0;
	virtual void take_damage() const = 0;
	virtual void heavy_attack() const = 0;
	virtual void lvl_up_perks() const = 0;
	virtual void info()const = 0;
};

class Paladin :public Warrior, public MagicDamage
{
private:
	int magic_attack;
	int holy_power;
	int mana;
	int max_mana;
	double heal;
	int splash_damage_aura;
	//Переменные для ультимативной способности
	bool is_divine_form_active;   // Активна ли форма(божественная форма)
	double divine_form_timer;     // Таймер способности
	int original_physic_attack;	  // Хранение оригинальных данных
	int original_max_health;
	int original_physic_resist;
	int original_magic_resist;
public:
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							get/set methods						  	  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	int get_magic_attack()const override
	{
		return magic_attack;
	}
	int get_holy_power()const
	{
		return holy_power;
	}
	int get_mana()const override
	{
		return mana;
	}
	double get_heal()const
	{
		return heal;
	}
	int get_splash_damage_aura()const
	{
		return splash_damage_aura;
	}
	void set_magic_attack(int magic_attack) override
	{
		this->magic_attack = magic_attack;
	}
	void set_holy_power(int holy_power)
	{
		this->holy_power = holy_power;
	}
	void set_mana(int mana) override
	{
		this->mana = mana;
	}
	void set_max_mana(int max_mana)
	{
		this->max_mana = max_mana;
	}
	void set_heal(double heal)
	{
		this->heal = heal;
	}
	void set_splash_damage_aura(int splash_damage_aura)
	{
		this->splash_damage_aura = splash_damage_aura;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							CONSTRUCTORS						  	  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	Paladin(MAIN_HEROES_TAKE_PARAMETERS, WARRIOR_TAKE_PARAMETERS, int magic_attack, int holy_power, int mana, int max_mana, double heal, int splash_damage_aura) :Warrior(MAIN_HEROES_GIVE_PARAMETERS, WARRIOR_GIVE_PARAMETERS)
	{
		set_magic_attack(magic_attack);
		set_holy_power(holy_power);
		set_mana(mana);
		set_max_mana(max_mana);
		set_heal(heal);
		set_splash_damage_aura(splash_damage_aura);
	}
	int calculate_magical_crit(int base_damage) const override
	{
		if (rand() % 100 < get_crit_chance())
		{
			int crit_damage = base_damage * (get_crit_damage() + 20) / 100; // 180%
			cout << "Holy Critical! ";
			return crit_damage;
		}
		return base_damage;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////							METHODS						  			  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	static Paladin* initial_charracteristics(const std::string& name)
	{
		return new Paladin(
			name,
			1200,	//Health
			1200,	//Max_health
			2.2,	//Movement_Speed
			1.4,	//Attack_speed
			50,		//Armor
			12,		//Crit_chance
			160,	//Crit_damage
			30,		//Physic_resist
			50,		//Magic_resist
			1,		//lvl
			0,		//exp
			150,	//exp_for_lvl_up
			160,	//Physic_attack
			67,		//taunt
			10,		//block_chance
			5,		//dodge_chance
			160,	//magic_attack
			100,	//holy_power
			200,	//mana
			200,	//max_mana
			0.15,	//heal(вампиризм)
			5		//splash_damage_aura
		);
	}
	void use_ability_1() const override
	{
		double heal_amount = get_max_health() * heal;
		double health;
		health = get_health() + heal_amount;
		cout << "Вы - " << name << " восстановили " << heal_amount << " HP" << endl;
	}
	void use_ability_2() const override	//в 5 крат повышена скорость атаки, на протяжении 7 секунд, урон увеличен на 60%, шанс крита на 25%
	{
		
	}
	void use_ability_passive() const override	//Навсегда увеличивает хп на 25% для текущего максимального здоровья, и при повышении всех следующих уровней, на 30% повышена атака(также, как и здоровье)
	{

	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////				ULTIMATE_ABILITY AND ALL FOR THIS		 			  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	void use_ability_ultimate() override	//Суть ультимативки - увеличить атаку на 50% и сделать её магической с вампиризмом, по 3% от максимального хп за удар, максимальное здоровье на 40%, так ещё и при этом отхилиться до нового максимума, таймер 20 секунд, резисты на 30%
	{
		if (is_divine_form_active == true)
		{
			cout << "Божественная форма активна! У вас есть " << divine_form_timer << " секунд.\n";
			return;
		}
		if (holy_power < 3)
		{
			cout << "Необходима святая сила для активации Божественной формы в количестве 3 штук.\n";
			return;
		}

		//Сохраняем наши значения зафиксированные до божественной формы
		original_physic_attack = get_physic_attack();
		original_max_health = get_max_health();
		original_physic_resist = get_physic_resist();
		original_magic_resist = get_magic_resist();

		is_divine_form_active = true;	//Способность активна
		divine_form_timer = 20.0;		//Активируется на 20 секунд
		holy_power = 0;					//Зануляем святую силу(так как это ультимативка, то и забирать она будет всю энергию под ноль)
		
		set_physic_attack(get_physic_attack() * 1.5);	//баффнули атаку на 50%

		int new_max_health = get_max_health() * 1.4;	//отхилился и увеличил хп на 40%
		set_max_health(new_max_health);	//Сравнял реальное максимальное здоровье с новым
		set_health(new_max_health);		//полное здоровье

		set_physic_resist(get_physic_resist() * 30/100); //Увеличил физическую защиту на 30%
		set_magic_resist(get_magic_resist() * 30/100);	 //Увеличил магическую защиту на 30%
	}
	void vampirism()
	{
		if (is_divine_form_active == false)
		{
			int damage = calculate_physical_crit(get_physic_attack());
			cout << "Атака паладина наносит " << damage << " физического урона.\n";
			return;
		}	//Если форма не активна - по дефолту бьём физическими атаками

		//Если всё же каким-то чудом, мы - нищеброды, смогли накопить три очка святой силы, атаки переходят на новый уровень
		int base_magic_damage = get_physic_attack();	//Создаём базовую магическую атаку, и за основу её харрактеристик берём базовую атаку(чтобы было от чего отталкиваться)
		int magic_damage = calculate_magical_crit(base_magic_damage);	//Ну врооооде... физический урон должен был стать магическим, но так ли это... мы пока не узнаем... и наверное никогда

		
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////					ТАКЕ ДАМАГЕ... ЁЛКИ-ИГОЛКИ...		 			  ////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	void take_damage() const override
	{
		
	}
	void heavy_attack() const override
	{
		
	}
	void lvl_up_perks() const override
	{

	}
	void info() const override
	{
		cout << "Paladin " << get_name() << " - Level " << get_lvl() << "\n";
		cout << "Health: " << get_health() << "/" << get_max_health() << "\n";
		cout << "Mana: " << mana << "/" << max_mana << "\n";
		cout << "Holy Power: " << holy_power << "\n";
		cout << "Physical Attack: " << get_physic_attack() << "\n";
		cout << "Magic Attack: " << magic_attack << "\n";
	}
};














void main()
{
	setlocale(LC_ALL, "");

}