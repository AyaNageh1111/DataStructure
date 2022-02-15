#include "Freezer.h"


Freezer::Freezer(int NID, int Reload, int power, double speed, double Healthint, int arrvTime) : Enemy(NID, arrvTime)
{
	this->SetReloadPeriod(Reload);
	this->SetPower(power);
	this->SetSpeed(speed);
	this->SetHealth(Health);

}

void Freezer::Move()
{
	if (status == ACTV)
	{
		if ((time) && (GetDistance() > 2))
			DecrementDist();
	}
}

void Freezer::Act()
{
	double CurrentTime;
	while (status == ACTV)
	{
		int attacktime = ArrvTime;
		if (CurrentTime = (attacktime + ReloadPeriod + 1))
		{
			if (hits < 10)
				hits++;
			else if (hits >= 10)
			{
				CP->SetStatus(FRST);
				hits = 0;
			}
		}
	}
}

Freezer::~Freezer()
{
}



//void Freezer::HalfedSpeed(Freezer& Fr)
//{
//	Freezer F;
//	if (Fr.HealthGetter() <= (F.HealthGetter() / 2))
//	{
//		Fr.SpeedSetter(Fr.SpeedGetter() / 2);
//	}
//}

//void Freezer::AddFreezer(int id, int arrive,int dis)
//{
//	Freezer newFreezer(id, arrive, dis);
//
//	if (freezer.isEmpty())
//	{
//		freezer.enqueue(newFreezer);
//		count++;
//	}
//	else
//	{
//		Freezer F;
//		Queue<Freezer> LnewQueue;
//		Queue<Freezer> SnewQueue;
//		while (!freezer.isEmpty())
//		{
//			freezer.peekFront(F);
//			if (newFreezer.GetArrvTime() <= F.GetArrvTime())
//			{
//				freezer.dequeue(F);
//				LnewQueue.enqueue(F);
//			}
//			else if (newFreezer.GetArrvTime() > F.GetArrvTime())
//			{
//				freezer.dequeue(F);
//				SnewQueue.enqueue(F);
//			}
//		}
//		while (!LnewQueue.isEmpty())
//		{
//			LnewQueue.dequeue(F);
//			freezer.enqueue(F);
//		}
//
//		freezer.enqueue(newFreezer);
//
//		while (!SnewQueue.isEmpty())
//		{
//			SnewQueue.dequeue(F);
//			freezer.enqueue(F);
//		}
//		count++;
//	}
//}