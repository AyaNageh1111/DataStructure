#pragma once
#ifndef FREEZER_H
#define FREEZER_H
#include "Enemies/Enemy.h"
#include"Defs.h"
#include "Generic_DS/Queue.h"
#include "Battle.h"
#include "CMUgraphicsLib/CMUgraphics.h"
#include "Castle/Castle.h"
#include <time.h>


int hits;

class Freezer :public Enemy
{
public:
	Freezer();
	Freezer(int id, int reload, int power, double speed, double health, int arrtime);
	int count;

	//fill from the file
	int reload; //1
	int damage; //2
	double speed;  //3
	Castle* CP;

	void Move();
	void Act();
	
	//void AddFreezer(int id, int arrive,int dis);
	//void HalfedSpeed(Freezer& Fr);
	~Freezer();

};
#endif
