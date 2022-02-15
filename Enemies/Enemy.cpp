#include "Enemy.h"

Enemy::Enemy()
{
	 int ID = 0;
	 int ArrvTime = 0;
}
Enemy::Enemy(int id, int arrTime, int type, double speed, int reloadPeriod, int power, double health, int d) :ID(id), ArrvTime(arrTime)
{
	SetDistance(d);
	SetID(id);
	SetPower(power);
	SetHealth(health);
	SetReloadPeriod(reloadPeriod);
	SetSpeed(speed);

}
Enemy::Enemy(int id, int arrTime, int d):ID(id),ArrvTime(arrTime)
{
	SetDistance(d);
}

Enemy::~Enemy()
{
}



void Enemy::SetStatus(ENMY_STATUS s)
{
	status = s;
}
ENMY_STATUS Enemy::GetStatus() const
{
	return status;
}


void Enemy::DecrementDist()
{
	if (Distance > MinDistance)
		Distance--;
}

void Enemy::SetDistance(int d)
{
	if (d >= MinDistance && d <= MaxDistance)
		Distance = d;
	else
		Distance = MaxDistance;
}
int Enemy::GetDistance() const
{
	return Distance;
}

int Enemy::GetArrvTime() const
{
	return ArrvTime;
}

int Enemy::GetFSTime() const
{
	return FSTime;
}
void Enemy::SetFSTime(int time)
{
	FSTime = time;
}

int Enemy::GetKTime() const
{
	return KTime;
}
void Enemy::SetKTime(int time)
{
	KTime = time;
}


void Enemy::SetHealth(double HealthSetter)
{
	Health = HealthSetter;
	Hlth = Health;
}
double Enemy::GetHealth() const
{
	return Health;
}
double Enemy::GetFullHealth() const
{
	return Hlth;
}

/*void Enemy::HalfSpeed()
{
	if (!INChangeSpeed)
	{
		INChangeSpeed = true;
		if (Health < GetHealth())
		{
			Speed = Speed / 2;
		}
	}
}*/

void Enemy::SetPower(int d)
{
	if (d > 0)
		Power = d;
	else
		Power = 0;
}
int Enemy::GetPower() const
{
	return Power;
}

void Enemy::SetSpeed(int d)
{
	if (d > 0)
	{
		Speed = d;
		spd = d;
	}
	else
		Speed = 0;
}
double Enemy::GetFullSpeed() const
{
	return spd;
}
int Enemy::GetSpeed() const
{
	return Speed;
}

void Enemy::SetReloadPeriod(int d)
{
	if (d > 0)
		ReloadPeriod = d;
	else
		ReloadPeriod = 0;
}
int Enemy::GetReloadPeriod() const
{
	return ReloadPeriod;
}

void Enemy::SetID(int IDSetter)
{
	ID = IDSetter;
}
int Enemy::GetID() const
{
	return ID;
}

void Enemy::ActiveEnm()
{
	if (type == FIGHTER)
	{
		/*Fighter* F;
		F->count++;
		BST Afighter;
		add(arrivaltime, *F, *node);*/
	}

	if (type == HEALER)
	{
			/*Healer* H;
			H->count++;
			BST Ahealer;
			add(arrivaltime, *H, *node);*/
	}

	if (type == FREEZER)
	{
		/*Freezer* FR;
		FR->count++;
		BST Afrezer;
		add(arrivaltime, *FR, *node);*/
	}
}