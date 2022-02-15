
//#include "Enemies\Enemy.h"
#include "Castle\Castle.h"
#include "PriorityQueue.h"
#include <time.h>
#include"Battle.h"
#include"Enemies/Enemy.h"
class Fighter : public Enemy
{
	double Priority;
	int FID;
public:
	Fighter();
	Fighter(int NID, int Reload, int power, double speed, double Healthint, int arrvTime);
	Fighter(int id, int arrTime, int d = MaxDistance);
	~Fighter();
	void Move();
	void Act();
	Castle F_Castle;
	//void Reload();
	int count;
	void SetPriority();
	double GetPriority() const;

	int StatusValue;

	void SetStatusValue();
	int GetStatusValue();

	//Priority Queue Implementation


	//double GetHighestPriority();

	Battle Manage;







	ENMY_STATUS Fstatus;	    //status of the enemy (inactive, inactive, frosted, killed)
	int FDistance;	//Horizontal distance between enemy & the tower of its region
					//Always positive (ranges from 2 to 60)
	double FHealth;	//Enemy health
};
