#ifndef _BAT_
#define _BAT_

#include "sphere.h"
#include "tvector.h"
#include "naivePhy.h"

double const FORCE_TO_VELO = 1.0f;

class Bat {
	TVector force;
public:
	Bat() :force(TVector()) {}
	Bat(TVector f) :force(f) {}

	void hit(Sphere &s);

	void setForce(TVector f) { force = f; }
	
	TVector const getForce() const { return force; }
};

#endif // _BAT_