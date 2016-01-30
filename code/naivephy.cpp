#include "naivePhy.h"

void crush(TVector &pos1, TVector &pos2,
	TVector &speed1, TVector &speed2)
{
	TVector axis = pos2 - pos1;
	TVector zUnit(0.0f, 0.0f, 1.0f);
	double theta = acos((axis * zUnit) / axis.model());
	if (axis.x < 0) {
		theta = 2 * PI - theta;
	}
	speed1.rotate(theta);
	speed2.rotate(theta);
	double temp = speed1.z;
	speed1.z = speed2.z;
	speed2.z = temp;
	speed1.rotate(2 * PI - theta);
	speed2.rotate(2 * PI - theta);
}

void moving(TVector &pos, const TVector &velo, double timeDelta)
{
	pos = pos + (timeDelta * velo);
}

void accelerate(TVector &velo, const TVector &acc, double timeDelta)
{
	velo = velo + (timeDelta * acc);
}

TVector newtonSecond(double mass, TVector force)
{
	return force / mass;
}