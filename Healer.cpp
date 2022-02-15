#include"Healer.h"
#include"Stack.h"
#include"Freezer.h"

Healer::Healer()
{

	ID = 0;
	Arrival_time = 0;

}
Healer::Healer(int id, int arrTime, int d) :ID(id), Arrival_time(arrTime)
{
	SetDistance(d);
}
Healer::Healer(int NID, int Reload, int power, double speed, double Healthint, int arrvTime) : Enemy(NID, arrvTime)
{
	this->SetReloadPeriod(Reload);
	this->SetPower(power);
	this->SetSpeed(speed);
	this->SetHealth(Health);
}

Healer::~Healer()
{
}

int Healer::GetID() const
{
	return ID;
}


void Healer::SetStatus(ENMY_STATUS s)
{
	status = s;
}


ENMY_STATUS Healer::GetStatus() const
{
	return status;
}


void Healer::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}
void Healer::IncrementDist()
{
	if (Distance < MaxDistance)
	{
		Distance++;
	}
}

void Healer::SetHealerDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}

int Healer::GetHealerDistance() const
{
	return Distance;
}

void Healer::Move()
{
	if ((time) && (GetDistance() > 2))
		DecrementDist();
	else if ((time) && (GetDistance()) < 60)
		IncrementDist();
}
void Healer::Act()
{
	Battle oB;
	Enemy* pE;
	Healer* pH;
	while (Arrival_time > oB.FunctionCurrentTimeStep())
	{
		if (abs(pE->GetDistance() - pH->GetDistance() <= 2)) //Think of the formula later
			pE->SetHealth(Health + 1);
	}

}

int Healer::GetArrvTime() const
{
	return ArrvTime;
}




void Healer::kill_Healer(int arrivalTime)  //(Last come, first serve) "Stack"
{
	Healer* pH;
	if (arrivalTime < Arrival_time)
	{
		ENMY_STATUS k = KILD;
		pH->SetStatus(k);
	}
	Stack <Healer*> sG;
	Healer* sH;
	if (sH->ArrvTime < arrivalTime)
	{
		sG.pop(sH);
	}


}