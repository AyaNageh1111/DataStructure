#include "Castle.h"


Castle::Castle()
{

}
Castle::Castle(double Health, int N, double Power)
{

	this->Health = Health;
	this->N = N;
	this->Power = Power;
}
void Castle::SetPower(double P)
{
	Power = P;
}
double Castle::GetPower() const
{
	return Power;
}

void Castle::SetHealth(double h)
{
	if (h > 0)
		Health = h;
	else
		Health = 0; // killed
}

double Castle::GetHealth() const
{
	return Health;
}
void Castle::SetStatus(ENMY_STATUS s)
{
	status = s;
}
ENMY_STATUS Castle::GetStatus() const
{
	return status;
}
int Castle::GetNumberOfEnemies() const
{
	return N;
}

