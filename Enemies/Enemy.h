#pragma once

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class GUI;
// Enemy is the base class of each type of enemy
// Enemy should be an abstract class in next phases
class Enemy
{

protected:
	 int ID;         //Each enemy has a unique ID (sequence number)
	 int ArrvTime;	//arrival time (time it starts to join battle)
	 int FSTime;
	 int KTime;
	ENMY_STATUS status;	    //status of the enemy (inactive, inactive, frosted, killed)
	int Distance;	//Horizontal distance between enemy & the tower of its region
	                //Always positive (ranges from 2 to 60)
	double Health,Hlth;	//Enemy health
	double Speed, spd;
	double Power;
	int ReloadPeriod;
	ENMY_TYPE type;

	//
	// TODO: Add More Data Members As Needed
	//

public:
	Enemy();
	Enemy(int id, int arrTime, int type, double speed, int reloadPersiod, int power, double health, int d = MaxDistance);
	Enemy(int id, int arrTime, int d = MaxDistance);
	virtual ~Enemy();

	int Enemy::GetID() const;
	ENMY_STATUS GetStatus() const;
	void SetStatus(ENMY_STATUS);
	
	void DecrementDist();

	void SetDistance(int );
	int GetDistance() const;

	int GetArrvTime() const;

	int GetFSTime() const;
	void SetFSTime(int time);

	int GetKTime() const;
	void SetKTime(int time);

	// Virtual Functions: ----------------

	//virtual void Move() = 0;	//All enemies can move
	//virtual void Act() = 0;	//Acting means fighting or healing

	//
	// TODO: Add More Member Functions As Needed
	//
	double GetHealth() const;
	double GetFullHealth() const;
	double GetFullSpeed() const;
	//void HalfSpeed();
	void SetSpeed(int);
	int GetSpeed() const;
	void SetPower(int);
	int GetPower() const;
	void SetReloadPeriod(int);
	int GetReloadPeriod() const;
	void SetID(int IDSetter);
	void SetHealth(double HealthSetter);
	void ActiveEnm();

	//static bool INChangeSpeed;

};

