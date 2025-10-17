#pragma once
#include"stdafx.h"
using namespace std;
#define delimiter "\n-----------------------------------------------------\n"

class Knight;
class Archer;
class Wizard;

int RandHealth(const std::string& type);
int RandBaseAttack(const std::string& type);
int RandAbility(const std::string& type);

Warrior* WarriorFactory(const std::string& type, const std::string& name = "", Warrior* level = nullptr, Warrior* exp = nullptr, Warrior* exp_for_level_up = nullptr)	//Использую фабричный паттерн для генерации воинов, смотрел по нашему репозиторию с академией, 
//но нули заменил функциями, которые генерят рандомные числа
{
	if (type == "Knight") return new Knight(name, RandHealth(type), RandBaseAttack(type), 1, 0, 50, RandAbility(type));
	if (type == "Archer") return new Archer(name, RandHealth(type), RandBaseAttack(type), 1, 0, 50, RandAbility(type));
	if (type == "Wizard") return new Wizard(name, RandHealth(type), RandBaseAttack(type), 1, 0, 50, RandAbility(type));
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
	if (type == "Knight") return rand() % 10 + 12;
	if (type == "Archer") return rand() % 20 + 20;
	if (type == "Wizard") return rand() % 15 + 15;
}
int RandAbility(const std::string& type)
{
	if (type == "Knight") return rand() % 5 + 7;
	if (type == "Archer") return rand() % 8 + 7;
	if (type == "Wizard") return rand() % 15 + 20;
}