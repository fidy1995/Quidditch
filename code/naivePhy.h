#ifndef _NAIVE_PHY_
#define _NAIVE_PHY_

#include "tvector.h"

const TVector gravity(0.0f, 0.1f / RATIO, 0.0f);

void crush(TVector &pos1, TVector &pos2,
	TVector &speed1, TVector &speed2);

// advanced crush: with palstance
// not implemented this iteration
/* void crush(TVector &pos1, TVector &pos2,
	TVector &velo1, TVector &velo2, 
	double &pals1, double pals2);
*/

void moving(TVector &pos, const TVector &velo, double timeDelta);
void accelerate(TVector &velo, const TVector &acc, double timeDelta);
TVector newtonSecond(double mass, TVector force);

#endif // _NAIVE_PHY_