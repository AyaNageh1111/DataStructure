#include "Battle.h"
#include <time.h>
#include <fstream>


Battle::Battle()
{
	EnemyCount = 0;
	KilledCount = 0;
	ActiveCount = 0;
	FrostedCount = 0;
	DemoListCount = 0;
	CurrentTimeStep = 0;
	pGUI = NULL;
}

void Battle::AddtoDemoList(Enemy* Ptr)
{
	DemoList[DemoListCount++] = Ptr;

	// Note that this function doesn't allocate any enemy objects
	// It just enqueue a pointer that is already allocated into the queue
}


Castle* Battle::GetCastle()
{
	return &BCastle;
}


void Battle::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();

	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	}

	delete pGUI;

}


//This is just a demo function for project introductory phase
//It should be removed in phases 1&2
void Battle::Just_A_Demo()
{

	pGUI->PrintMessage("Just a Demo. Enter Enemies Count(next phases should read I/P filename):");
	EnemyCount = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->PrintMessage("Generating Enemies randomly... In next phases, Enemies should be loaded from a file...CLICK to continue");
	pGUI->waitForClick();

	CurrentTimeStep = 0;
	//
	// THIS IS JUST A DEMO Function
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	//

	srand(time(NULL));
	int Enemy_id = 0;
	int ArrivalTime = 1;
	Enemy* pE = NULL;
	//Create Random enemies and add them all to inactive queue
	for (int i = 0; i < EnemyCount; i++)
	{
		ArrivalTime += (rand() % 3);	//Randomize arrival time
		pE = new Enemy(++Enemy_id, ArrivalTime);
		pE->SetStatus(INAC); //initiall all enemies are inactive
		Q_Inactive.enqueue(pE);		//Add created enemy to inactive Queue
	}

	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);	//upadte interface to show the initial case where all enemies are still inactive

	pGUI->waitForClick();

	while (KilledCount < EnemyCount)	//as long as some enemies are alive (should be updated in next phases)
	{
		CurrentTimeStep++;
		ActivateEnemies();

		Demo_UpdateEnemies();	//Randomly update enemies distance/status (for demo purposes only)

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);
		Sleep(250);
	}
}

//Add enemy lists (inactive, active,.....) to drawing list to be displayed on user interface
void Battle::AddAllListsToDrawingList()
{
	//Add inactive queue to drawing list
	int InactiveCount;
	Enemy* const* EnemyList = Q_Inactive.toArray(InactiveCount);
	for (int i = 0; i < InactiveCount; i++)
		pGUI->AddToDrawingList(EnemyList[i]);

	//Add other lists to drawing list
	//TO DO
	//In next phases, you should add enemies from different lists to the drawing list
	//For the sake of demo, we will use DemoList
	for (int i = 0; i < DemoListCount; i++)
		pGUI->AddToDrawingList(DemoList[i]);
}

//check the inactive list and activate all enemies that has arrived
void Battle::ActivateEnemies()
{
	Enemy* pE;
	while (Q_Inactive.peekFront(pE))	//as long as there are more inactive enemies
	{
		if (pE->GetArrvTime() > CurrentTimeStep)	//no more arrivals at current time
			return;

		Q_Inactive.dequeue(pE);	//remove enemy from the queue
		pE->SetStatus(ACTV);	//make status active
		Q_Active.enqueue(pE);
		AddtoDemoList(pE);		//move it to demo list (for demo purposes)
	}
}


//Randomly update enemies distance/status (for demo purposes)
void Battle::Demo_UpdateEnemies()
{
	Enemy* pE;
	int Prop;
	//Freeze, activate, and kill propablities (for sake of demo)
	int FreezProp = 5, ActvProp = 10, KillProp = 1;
	srand(time(0));
	for (int i = 0; i < DemoListCount; i++)
	{
		pE = DemoList[i];
		switch (pE->GetStatus())
		{
		case ACTV:
			pE->DecrementDist();	//move the enemy towards the castle
			Prop = rand() % 100;
			if (Prop < FreezProp)		//with Freeze propablity, change some active enemies to be frosted
			{
				pE->SetStatus(FRST);
				ActiveCount--;
				FrostedCount++;
			}
			else	if (Prop < (FreezProp + KillProp))	//with kill propablity, kill some active enemies
			{
				pE->SetStatus(KILD);
				ActiveCount--;
				KilledCount++;
			}

			break;
		case FRST:
			Prop = rand() % 100;
			if (Prop < ActvProp)			//with activation propablity, change restore some frosted enemies to be active again
			{
				pE->SetStatus(ACTV);
				ActiveCount++;
				FrostedCount--;
			}

			else	if (Prop < (ActvProp + KillProp))			//with kill propablity, kill some frosted enemies
			{
				pE->SetStatus(KILD);
				FrostedCount--;
				KilledCount++;
			}

			break;
		}
	}
}



//////////////////////////////////////////////////////


//////Functions added by the TEAM
bool Battle::dequeueBySearch(Enemy*& var)  //done vero
{	
		int flag = 0;
		Enemy* peeker;
		Enemy* arranger;
		Queue<Enemy*> Nomatch;
	while (!Q_Active.isEmpty())
	{
		Q_Active.peekFront(peeker);
		if (var->GetID() == peeker->GetID())
		{
			Q_Active.dequeue(var);
			ActiveCount--;
			flag = 1;
		}
		else
		{
			Q_Active.dequeue(arranger);
			Nomatch.enqueue(arranger);
		}
	}
		while (!Nomatch.isEmpty())
		{
			Nomatch.dequeue(arranger);
			Q_Active.enqueue(arranger);
		}

		if (flag = 1)
			return true;
		else
			return false;

}
bool Battle::IsChangeSpeed(Enemy* PE) //done vero
{
	if (PE->GetSpeed() <= (PE->GetFullSpeed() / 2))
		return true;
	else
		return false;
}
void Battle::Killed()   //done vero
{
	while (PQ_fighter.GetCount()!=0)
	{
		Fighter* FP;
		PQ_fighter.peek(FP);

		if (FP->GetHealth()==FP->GetFullHealth())
		{
			FP->SetFSTime(CurrentTimeStep);
		}

		if (FP->GetHealth() > BCastle.GetPower()) //Only shooted case
		{
			FP->SetHealth(FP->GetHealth() - ((1 / FP->GetDistance()) * BCastle.GetPower()));
			if ((FP->GetHealth() <= (FP->GetFullHealth() / 2)) && (!IsChangeSpeed(FP)))
			{
				FP->SetSpeed(FP->GetSpeed() / 2);

			}
		}

		else  //Killed case
		{
			FP->SetHealth(0);
			FP->SetKTime(CurrentTimeStep);
			PQ_fighter.Dequeue(FP);
			Enemy* pe;
			FP->SetStatus(KILD);	//make status Ki
		
			dequeueBySearch(pe);	//remove enemy from the queue
			Q_Killed.enqueue(pe);
			KilledCount++;

		}
	}

	while (!S_healer.isEmpty())
	{
		Healer* HP;
		S_healer.peek(HP);

		if (HP->GetHealth() == HP->GetFullHealth())
		{
			HP->SetFSTime(CurrentTimeStep);
		}

		if (HP->GetHealth() > BCastle.GetPower()) //Only shooted case
		{
			HP->SetHealth(HP->GetHealth() - ((1 / HP->GetDistance()) * BCastle.GetPower()));
			if ((HP->GetHealth() <= (HP->GetFullHealth() / 2)) && (!IsChangeSpeed(HP)))
			{
				HP->SetSpeed(HP->GetSpeed() / 2);

			}
		}

		else  //Killed case
		{
			HP->SetHealth(0);
			HP->SetKTime(CurrentTimeStep);
			S_healer.pop(HP);
			Enemy* pe;
			HP->SetStatus(KILD);	//make status Ki
			dequeueBySearch(pe);	//remove enemy from the queue
			Q_Killed.enqueue(pe);
			KilledCount++;

		}
	}

	while (!Q_freezer.isEmpty())
	{
		Freezer* FP;
		Q_freezer.peekFront(FP);

		if (FP->GetHealth() == FP->GetFullHealth())
		{
			FP->SetFSTime(CurrentTimeStep);
		}

		if (FP->GetHealth() > BCastle.GetPower()) //Only shooted case
		{
			FP->SetHealth(FP->GetHealth() - ((1 / FP->GetDistance()) * BCastle.GetPower()));
			if ((FP->GetHealth() <= (FP->GetFullHealth() / 2)) && (!IsChangeSpeed(FP)))
			{
				FP->SetSpeed(FP->GetSpeed() / 2);

			}
		}

		else  //Killed case
		{
			FP->SetHealth(0);
			FP->SetKTime(CurrentTimeStep);
			Q_freezer.dequeue(FP);
			Enemy* pe;
			FP->SetStatus(KILD);	//make status Ki
			dequeueBySearch(pe);	//remove enemy from the queue
			Q_Killed.enqueue(pe);
			KilledCount++;

		}
	}

}
//Create enemies and add them all to inactive queue
void Battle::Create()  //done vero
{
	
	for (int i = 0; i < EnemyCount; i++)
	{
		int Enemy_id = 0;
		int ArrivalTime = 1;
		int type;
		double speed;
		int reloadPersiod;
		int power;
		double health;


		switch (type)
		{

		case 0:
			Fighter * NFighter = new Fighter(Enemy_id, reloadPersiod, power, speed, health, ArrivalTime);
			NFighter->SetStatus(INAC);
			Q_Inactive.enqueue(NFighter);
			PQ_fighter.insert(NFighter, NFighter->GetPriority());
			FighterCount++;
			InactiveCount++;
			break;
		case 1:
			Healer * NHealer = new Healer(Enemy_id, reloadPersiod, power, speed, health, ArrivalTime);
			NHealer->SetStatus(INAC);
			Q_Inactive.enqueue(NHealer);
			S_healer.push(NHealer);
			HealerCount++;
			InactiveCount++;
			break;
		case 2:
			Freezer * Nfreezer = new Freezer(Enemy_id, reloadPersiod, power, speed, health, ArrivalTime);
			Nfreezer->SetStatus(INAC); //initiall all enemies are inactive
			Q_Inactive.enqueue(Nfreezer);	//Add created enemy to inactive Queue
			Q_freezer.enqueue(Nfreezer);
			FreezerCount++;
			InactiveCount++;
			break;
		default:
			break;
		}

	}

}
//arrange enemies and add them all to inactive queue
void Battle::Arrange(Enemy* EP) //done vero
{
	if (Q_Inactive.isEmpty())
	{
		Q_Inactive.enqueue(EP);
		InactiveCount++;
	}
	else
	{
		Enemy* test;
		Queue<Enemy*> LnewQueue;
		Queue<Enemy*> SnewQueue;
		while (!Q_Inactive.isEmpty())
		{
			Q_Inactive.peekFront(test);
			if (EP->GetArrvTime() <= test->GetArrvTime())
			{
				Q_Inactive.dequeue(test);
				LnewQueue.enqueue(test);
			}
			else if (EP->GetArrvTime() > test->GetArrvTime())
			{
				Q_Inactive.dequeue(test);
				SnewQueue.enqueue(test);
			}
		}
		while (!LnewQueue.isEmpty())
		{
			LnewQueue.dequeue(test);
			Q_Inactive.enqueue(test);
		}

		Q_Inactive.enqueue(EP);

		while (!SnewQueue.isEmpty())
		{
			SnewQueue.dequeue(test);
			Q_Inactive.enqueue(test);
		}
	}
	InactiveCount++;
}


// done Shrouk
void Battle::DamageCastle_Fighter() //Damgae cause to the castle by the fighter
{
	Fighter Fo;
	double damage = (Fo.GetHealth() / Fo.GetDistance()) * Fo.GetPower();
}
void Battle::FreezeCastle_Freezer()
{
	Healer Ho;
	Fighter Fo;
	Freezer FRo;
	Castle Co;
	Ho.SetHealth(2); //Setting the healer health by 2
	double healerHealth = Ho.GetHealth();
	double damage_Healer = healerHealth / (Ho.GetDistance() * Co.GetHealth());
	Fo.SetHealth(1); //Setting the fighter health by 1
	double fighterHealth = Fo.GetHealth();
	double damage_Fighter = fighterHealth / (Fo.GetDistance() * Co.GetHealth());
	FRo.SetHealth(1); //Setting the freezer health by 1
	double freezerHealth = FRo.GetHealth();
	double damage_Freezer = freezerHealth / (FRo.GetDistance() * Co.GetHealth());
}
void Battle::DamageEnemy_Castle() ////The damage is caused by enemies through the bullets
{
	Fighter Fo;
	Castle Co;
	Healer Ho;
	Freezer FRo;
	Ho.SetHealth(2); //Setting the healer health by 2
	double healerHealth = Ho.GetHealth();
	double damageHealer = (Co.GetPower()) / (Ho.GetDistance() * healerHealth);//Damage Healer
	Fo.SetHealth(1); //Setting the fighter health by 1
	double fighterHealth = Fo.GetHealth();
	double damageFighter = (Co.GetPower()) / (Fo.GetDistance() * fighterHealth);//Damage Fighter
	FRo.SetHealth(1); //Setting the freezer health by 1
	double freezerHealth = FRo.GetHealth();
	double damageFreezer = (Co.GetPower()) / (FRo.GetDistance() * freezerHealth);//Damage Freezer

}
void Battle::Heal_Enemies(Priority_Queue<Fighter> figherList, Queue<Freezer> freezerList)
{
	Fighter Fo;
	Freezer FRo;
	Healer Ho;
	freezerList.dequeue(FRo);
	figherList.Dequeue(Fo);
	if ((Fo.GetDistance() - Ho.GetHealerDistance() == 2) || (Fo.GetDistance() - Ho.GetHealerDistance() < 2))
	{
		Fo.SetHealth(Fo.GetHealth() + 1);
	}

}
double Battle::isHealed(Healer* Hp, Enemy* Ep)
{

	double dist = abs(Hp->GetDistance() - Ep->GetDistance());
	if ((Ep->GetStatus() == FRST) && (Ep->GetStatus() == KILD))
	{
		return;
	}
	else
	{
		double Health_Healer = (1 / dist) * (1 / Ep->GetHealth());
		return Health_Healer;

	}

}
void Battle::IceTimeStep() ////The damage is caused to the enemies by the castle ice
{
	Fighter Fo;
	Castle Co;
	Healer Ho;
	Freezer FRo;
	Ho.SetHealth(2); //Setting the healer health by 2
	double healerHealth = Ho.GetHealth();
	double damageHealer = (Co.GetPower()) / (Ho.GetDistance() * healerHealth);//Damage Healer
	Fo.SetHealth(1); //Setting the fighter health by 1
	double fighterHealth = Fo.GetHealth();
	double damageFighter = (Co.GetPower()) / (Fo.GetDistance() * fighterHealth);//Damage Fighter
	FRo.SetHealth(1); //Setting the freezer health by 1
	double freezerHealth = FRo.GetHealth();
	double damageFreezer = (Co.GetPower()) / (FRo.GetDistance() * freezerHealth);//Damage Freezer
}

// Done Aya
int Battle::CollectAvr(int Time)
{
	int Tottime = CollectFirstTime(Time);
	return (Tottime / (FighterCount + HealerCount + FreezerCount));

}
int Battle::CollectFirstTime(int time, Queue<Enemy*> Q_enm)
{
	int Count;

	Enemy* const* EnemyList = Q_enm.toArray(Count);
	for (int i = 0; i < Count; i++)
	{
		time = time + (EnemyList[i]->GetArrvTime()) - (EnemyList[i]->GetFSTime());
	}
	return time;
}
GAME_STATUS Battle::BattleStatus()
{
	if (BCastle.GetHealth() <= 0)	// the castle has fallen and it can be either loss or drawn
		if (KilledCount == EnemyCount)	// all enemies fall too, so it's drawn
			return DRAWN;
		else	// there still some enemies, then its loss
			return LOSS;
	else		// the castle is still standing, so it's win
		return WIN;

}
void Battle::StepByStepMode()
{
	CurrentTimeStep = 0;
	LoadingFunction();
	AddAllListsToDrawingList();
	pGUI->UpdateInterface(CurrentTimeStep);

	while (KilledCount < EnemyCount)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		Create();

		pGUI->ResetDrawingList();
		AddAllListsToDrawingList();
		pGUI->UpdateInterface(CurrentTimeStep);

		Sleep(700);		// Action of proceeding
	}
	//outputfile
}
void Battle::SilentMode()
{
	CurrentTimeStep = 0;
	LoadingFunction();
	AddAllListsToDrawingList();

	while (KilledCount < EnemyCount)
	{
		CurrentTimeStep++;
		ActivateEnemies();
		Create();
	}
	LoadingFunction();
}
void Battle::LoadingFunction()
{
	ofstream outputfile;
	outputfile.open("Output.txt");
	Enemy* e;
	int FD = 0, KD = 0, LT = 0;
	int AvrFD = 0, AVRKD = 0;

	if (KilledCount < EnemyCount)	//for not killed enemies
	{
		while (FighterCount != 0 || FreezerCount != 0 || HealerCount != 0 || FrostedCount != 0)
		{
			FD = CollectFirstTime(FD, Q_Active);

			KD = 0;		//not killed
			LT = CurrentTimeStep - e->GetArrvTime();	// since he's still alive
			outputfile << KD << e->GetID() << FD << KD << LT << "\n";
			AvrFD += FD;		//will divide on count in next step
			AVRKD += KD;
		}

	}
	while (KilledCount != 0)
	{
		Q_Killed.dequeue(e);
		KilledCount--;
		FD = e->GetFSTime() + e->GetArrvTime();
		KD = e->GetKTime() + e->GetFSTime();
		LT = FD + KD;
		outputfile << e->GetKTime() << " " << e->GetID() << "     "
			<< FD << " " << KD << " " << LT << "\n";

		AvrFD += FD;		//will divide on count in next step
		AVRKD += KD;
	}

	outputfile << "Total Enemies" << EnemyCount << "\n";

	outputfile << "Average First-Shot Delay" << CollectAvr(FD) << "\n";

	outputfile << "Average Kill Delay" << CollectAvr(KD) << "\n";

	outputfile.close();

	delete e;
}
int Battle::CollectFirstTime(int time)
{
	int ActiveCount;

	Enemy* const* EnemyList = Q_Active.toArray(ActiveCount);
	for (int i = 0; i < ActiveCount; i++)
	{
		time = time + (EnemyList[i]->GetArrvTime()) - (EnemyList[i]->GetFSTime());
	}
	return time;
}
int Battle::CollectAvr(int Time)
{
	int Tottime = CollectFirstTime(Time);
	return (Tottime / (FighterCount + HealerCount + FreezerCount));
}
