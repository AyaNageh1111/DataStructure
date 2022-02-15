#pragma once
#include "..\Defs.h"
class Castle
{
	double Health;
	double Power;
	ENMY_STATUS status;
	//
	// TODO: Add More Data Members As Needed
	//

public:
	Castle();

	void SetHealth(double h);
	double GetHealth() const;

	void SetStatus(ENMY_STATUS);
	int GetNumberOfEnemies() const;
	ENMY_STATUS GetStatus() const;

	int N; // the maximum number of enemies a castle can attack at any time stepand
	Castle(double Health, int N, double Power);
	//
	// TODO: Add More Member Functions As Needed
	//
	//Damge(Fighter->Castle)
	void DamageCastle_Fighter();
	void FreezeCastle_Freezer();
	void DamageEnemy_Castle();

	void SetPower(double P);
	double GetPower() const;

	

	//
	// TODO: Add More Member Functions As Needed
	//

};

