#ifndef _G_BAT_
#define _G_BAT_

#include "bat.h"
#include "GTex.h"

class GBat {
	Bat *bat;

public:
	GBat() :bat(NULL) {}
	GBat(Bat s) {
		bat = new Bat(s.getForce());
	}
	void GDrawBat(Sphere s, double force, double angle, GTex *g);
};

#endif // _G_BAT_