#pragma once
#include"stdafx.h"
#include"Factory.h"
using namespace std;

void Tournament_Grid(std::map<std::string, std::list<Warrior*>>& Tournament_grid)	//функция с задачей турнирной сетки
{
	Tournament_grid["Human"].push_back(WarriorFactory("Knight", "Asphodel"));
	Tournament_grid["Human"].push_back(WarriorFactory("Wizard", "DoNotEnter"));
	Tournament_grid["Human"].push_back(WarriorFactory("Knight", "Without_Fear"));
	Tournament_grid["Human"].push_back(WarriorFactory("Archer", "Tulskiy_Ghoul"));
	Tournament_grid["Elf"].push_back(WarriorFactory("Archer", "OneWayToDie"));
	Tournament_grid["Elf"].push_back(WarriorFactory("Archer", "Remember_My_Memory"));
	Tournament_grid["Elf"].push_back(WarriorFactory("Wizard", "Always_Wet_Eyes"));
	Tournament_grid["Goblin"].push_back(WarriorFactory("Archer", "Ak1zaura"));
	Tournament_grid["Goblin"].push_back(WarriorFactory("Knight", "ZXC_Ghost_Kid"));
	Tournament_grid["Goblin"].push_back(WarriorFactory("Knight", "Angel_Slayer"));
}

class Tournament :public Warrior
{
		
};