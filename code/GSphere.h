#ifndef _G_SPHERE_
#define _G_SPHERE_

#include "sphere.h"
#include "GTex.h"

class GSphere {
	Sphere *sphere;
public:
	GSphere() :sphere(NULL) {}
	GSphere(Sphere s) {
		sphere = new Sphere(s.getType(), s.getMass(), s.getRange(), s.getPosition(), s.getVelocity());
	}

	void GDrawSphere(GTex *g);
};

#endif // _G_SPHERE_