#include<iostream>
#include <algorithm> 
using namespace std;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"
///////////////////////////////////////////////////////////////
//						TAKE/GIVE PARAMETERS				 //
///////////////////////////////////////////////////////////////
#define WARRIOR_TAKE_PARAMETERS const std::string& name, int health, int base_attack
#define WARRIOR_GIVE_PARAMETERS name, health, base_attack
///////////////////////////////////////////////////////////////
//							Initializations					 //
///////////////////////////////////////////////////////////////
int RandHealth(const std::string& type);
int RandBaseAttack(const std::string& type);
int RandAbility(const std::string& type);
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
	virtual void attack(Warrior* target) = 0;	// Чисто виртуальные функции, которые я с нуля буду реализовывать в других классах
	virtual void use_ability(Warrior* target = nullptr) = 0;
	virtual void take_damage(int damage)	//Метод получения урона по умолчанию для всех, кроме война, так как у него есть броня, от которой и исходит получаемый урон
	{
		health -= damage;
		if (is_alive() == false)
		{
			cout << name << " пал в бою";
		}
	}
	virtual bool is_alive()	//Метод проверки на жизнеспособность бойцов
	{
		return health > 0;
	}
	virtual void info()const
	{
		cout << name << "(" << "Здоровье: " << health << ", " << "атака: " << base_attack << ")" << endl;
	}
};
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
		cout << name << "(" << "Здоровье: " << health << ", " << "атака: " << base_attack << ", " << "Броня: " << armor << ")" << endl;	//Метод для вывода инфы для танка(рыцаря)
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
		cout << name << "(" << "Здоровье: " << health << ", " << "атака: " << base_attack << ", " << "Стрел в колчане: " << quiver << ")" << endl;
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
	void attack(Warrior* target) override
	{
		int damage = base_attack;	//Волшебник бьёт базовой атакой, но имеет возможность восстанавливать здоровье за счёт вампиризма, так как наносит энергоурон
		if (mana > 0)
		{
			health += 1;	//Восстанавливаем хэпэшку, и забираем ману
			mana -= 1;
			cout << " Волшебник пускает магическую стрелу! 1HP восстановлено." << endl;
		}
		else	// В противном случае волшебник бьёт посохом, хп не регенирирует, ну и он будет понакаченее лучника, поэтому урона даже голым посохом будет столько же, 
			//для баланса у него сделаю меньше хп в сравнении с лучником
		{
			cout << " Волшебник атакует посохом." << endl;
		}
		target->take_damage(damage);	//Передал урон оппоненту
	}
	void use_ability(Warrior* target)override
	{
		int damage;
		if (target->is_alive() == false)	//Проверяем работоспособность врага
		{
			cout << "Нельзя атаковать мёртвого врага!" << endl;
			return;
		}
		if (mana >= 10)	//Если маны 10 и больше, то есть шанс на использование способности(вероятность реализую в функции дуэлей), 
			//после использования - забираю 10 маны у мага и исцеляю его на 10 очков здоровья('rdbdfktyn 1 мана = 1 хп)
		{
			damage = base_attack * 2;
			health += 10;
			mana -= 10;
			cout << " Волшебник использует заклинание \"Огненный шар\"! 10HP Восстановлено. Нанесён удвоенный урон." << endl;
		}
		else	//В противном случае - используем простую базовую атаку с физ уроном и никакого вампиризма
		{
			damage = base_attack;
			cout << "Недостаточно маны для заклинания." << endl;
		}
		target->take_damage(damage);	//Передаём урон цели
	}
	virtual void info()const
	{
		cout << name << "(" << "Здоровье: " << health << ", " << "атака: " << base_attack << ", " << "мана: " << mana << ")" << endl;
	}
};

Warrior* WarriorFactory(const std::string& type, const std::string& name = "")	//Использую фабричный паттерн для генерации воинов
{
	if (type == "Knight") return new Knight(name, RandHealth(type), RandBaseAttack(type), RandAbility(type));
	if (type == "Archer") return new Archer(name, RandHealth(type), RandBaseAttack(type), RandAbility(type));
	if (type == "Wizard") return new Wizard(name, RandHealth(type), RandBaseAttack(type), RandAbility(type));
	cout << "\nНеизвестный тип воина '" << type << "', игровой ник: '" << name << "'" << endl;	//Описание неизвестного типа воина
	cout << delimiter << endl;
	return nullptr;	//Если тип неизвестен
}
int RandHealth(const std::string& type)	//создаю функцию, которая будет рандомить хпшку нашим классам, а также базовую атаку и их абилки
{
	if (type == "Knight") return rand() % 50 + 100;
	if (type == "Archer") return rand() % 30 + 80;
	if (type == "Wizard") return rand() % 25 + 65;
}
int RandBaseAttack(const std::string& type)
{
	if (type == "Knight") return rand() % 10 + 15;
	if (type == "Archer") return rand() % 20 + 20;
	if (type == "Wizard") return rand() % 15 + 15;
}
int RandAbility(const std::string& type)
{
	if (type == "Knight") return rand() % 5 + 7;
	if (type == "Archer") return rand() % 8 + 7;
	if (type == "Wizard") return rand() % 15 + 20;
}

void Duel(Warrior* Human, Warrior* Goblin)	//Функция с генерацией дуэлей
{
	int round = 1;
	cout << "Дуэль началась: " << endl;
	cout << Human->get_name() << " vs " << Goblin->get_name() << endl;	//Передаю их ники в заголовок
	while (Human->is_alive() && Goblin->is_alive())
	{
		cout << "Round: " << round << " - fight" << endl;	//Вывожу на экран номер раунда
		if (rand() % 100 < 30)	//Задаю вероятность использования абилки
		{
			Human->use_ability(Goblin);
		}
		else	//В противном случае базовая атака
		{
			Human->attack(Goblin);
		}
		if (Goblin->is_alive() == false) break;	//Проверяю жив противник или нет

		if (rand() % 100 < 30)	//Всё то же самое, но уже для гоблина
		{
			Goblin->use_ability(Human);
		}
		else
		{
			Goblin->attack(Human);
		}
		if (Human->is_alive() == false) break;
		round++;
		cout << Human->get_name() << " HP: " << Human->get_health() << endl;	//Вывожу на экран хп бойцов
		cout << Goblin->get_name() << " HP: " << Goblin->get_health() << endl;
		system("pause");
		system("CLS");
	}
	if (Human->is_alive())	//Делаю проверку на жизнь в конце каждого цикла, и если один из них мёртв - вывожу победителя
	{
		cout << "\nПобедил воин фракции Human, под ником " << Human->get_name() << "!" << endl;
	}
	else
	{
		cout << "\nПобедил воин фракции Goblin под ником " << Goblin->get_name() << "!" << endl;
	}
}

//#define info
#define DUEL

void main()
{
	setlocale(LC_ALL, "");
#ifdef info
	Warrior* group[] =
	{
		WarriorFactory("Knight", "OneWayToDie"),
		WarriorFactory("Archer", "Asphodel"),
		WarriorFactory("Wizard", "Ak1zaura"),
		WarriorFactory("Knight", "Dystopian_Paradise"),
		WarriorFactory("Rand_Dura40k_zashel_ne_v_tu_igru", "Apathy_warrior")
	};	//Создаю группу, одного целенаправленно делаю "неправильным", чтоб были разные примеры
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		if (group[i] != nullptr)	//Делаю проверку, и если кто-то из воинов её не проходит, то через else вывожу этого бойца на консоль по индексу
		{
			group[i]->info();
			cout << delimiter << endl;
		}
		else
		{
			cout << "Не удалось создать воина с индексом: " << i << endl;
		}
	}
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)	//Чищу память группы
	{
		if (group[i] != nullptr) delete group[i];
	}
#endif // info


#ifdef DUEL
	Warrior* Human = WarriorFactory("Knight", "Asphodel");	//Инициализирую двух бойцов для дуэли между ними, и вызываю функцию для её генерации
	Warrior* Goblin = WarriorFactory("Archer", "Ak1zaura");
	Duel(Human, Goblin);

	delete Human;
	delete Goblin;
#endif // DUEL
}
// Это первая моя работа, которой я сам доволен...