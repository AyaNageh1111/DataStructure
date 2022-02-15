#include "Fighter.h"
Fighter::Fighter()
{

}

Fighter::Fighter(int NID, int Reload, int power, double speed, double Healthint, int arrvTime) : Enemy(NID, arrvTime)
{
	this->SetReloadPeriod(Reload);
	this->SetPower(power);
	this->SetSpeed(speed);
	this->SetHealth(Health);

}
Fighter::Fighter(int id, int arrTime, int d = MaxDistance)
{
	SetDistance(d);

}


Fighter::~Fighter()
{
}

void Fighter::Move()
{
	int CurrentTimeStep;
	if (Distance <= 60 && Distance >= 2, CurrentTimeStep >= ArrvTime)
	{
		DecrementDist();
	}
}

void Fighter::Act()
{
	Castle Castle, int CurrentTimeStep;
	int k;
	int attacktime = ArrvTime;

	while (Distance <= 60 && Distance >= 2 && (CurrentTimeStep == attacktime))
	{


		if ((Health * 0.5) < FHealth)
		{
			k = 1;
		}
		else if ((Health * 0.5) > FHealth)
		{
			k = 0.5;
		}
		Castle.SetHealth((k / Distance) * Power);
		attacktime = ArrvTime + ReloadPeriod + 1;

	}
}

//void Fighter::Reload()
//{
//	Move();
//}
void Fighter::SetStatusValue()
{
	if (status == INAC || status == KILD)
		StatusValue == 0;
	if (status == ACTV)
		StatusValue == .80;
	if (status == FRST)
		StatusValue == .20;
}
int Fighter::GetStatusValue()
{
	return StatusValue;
}
void Fighter::SetPriority()
{
	Priority = StatusValue * 0.4 + ((MaxDistance - Distance) / 60) * 0.2 + (Health / GetHealth()) * 0.2 + Power * 0.2;
}

double Fighter::GetPriority() const
{
	return Priority;
}


//double Fighter::GetHighestPriority()
//{
//	int max = 0;
//	for (int i = 0; i++; i < count)
//	{
//		if (max < Priority)
//		{
//			max == Priority;
//		}
//	}
//	return max;
//}
