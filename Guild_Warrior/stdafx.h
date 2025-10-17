#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include"Warrior.h"
#include"Knight.h"
#include"Archer.h"
#include"Wizard.h"
#include"Battle.h"
using namespace std;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"


///////////////////////////////////////////////////////////////
//							Initializations					 //
///////////////////////////////////////////////////////////////
int RandHealth(const std::string& type);
int RandBaseAttack(const std::string& type);
int RandAbility(const std::string& type);