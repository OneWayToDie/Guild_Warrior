#include"stdafx.h"
#include"Factory.h"


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
		Human->gain_exp(100);
		cout << "\nПобедил воин фракции Human, под ником " << Human->get_name() << "!" << endl;
		Human->info();
	}
	else
	{
		Goblin->gain_exp(100);
		cout << "\nПобедил воин фракции Goblin под ником " << Goblin->get_name() << "!" << endl;
		Goblin->info();
	}
	if (Human->is_alive() == false)	//Делаю проверку на жизнь в конце каждого цикла, и если один из них мёртв - вывожу победителя
	{
		Human->gain_exp(50);
		cout << "\nВоин фракции Human, под ником " << Human->get_name() << " прогирал!" << endl;
		Human->health_recovery();
		Human->info();
	}
	else
	{
		Goblin->gain_exp(50);
		cout << "\nВоин фракции Goblin под ником " << Goblin->get_name() << " Проиграл!" << endl;
		Goblin->health_recovery();
		Goblin->info();
	}
}

void Duel_realization()
{
	Warrior* Human = WarriorFactory("Knight", "Asphodel");	//Инициализирую двух бойцов для дуэли между ними, и вызываю функцию для её генерации
	Warrior* Goblin = WarriorFactory("Archer", "Ak1zaura");
	cout << "Фракция - человек, ник:\t";
	Human->info();
	cout << "Фракция - гоблин, ник:\t";
	Goblin->info();
	Duel(Human, Goblin);
	delete Human;
	delete Goblin;
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
	Duel_realization();
#endif // DUEL

}
// Это первая моя работа, которой я сам доволен...