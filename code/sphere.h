#ifndef _SPHERE_
#define _SPHERE_

#include "tvector.h"
#include "naivePhy.h"
#include <vector>

using namespace std;

enum Type {
	DEFAULT = 0, CUE, QUIET, NOISE, GOLD 
};

const double defaultMass = 2.0f;
const double defaultRange = 4.0f / RATIO;

const double defaultFriction = 0.75f;
const double defaultVelocity = 4.0f / RATIO;

const double defaultHeight = 1.0f;

const double defaultMovingRadius = 120.0f / RATIO;
const double defaultAcc = defaultVelocity * defaultVelocity
							/ defaultMovingRadius;

const TVector defaultDownCenter(0.0f, defaultHeight, 2.0f);
const TVector defaultUpCenter(0.0f, defaultHeight, -2.0f);

class Sphere {
	Type type;

	double mass;
	double range;

	TVector position;
	TVector velocity;

	TVector originalPosition;

	//TVector motivation;

public:
	Sphere() :type(DEFAULT), mass(0.0),range(0.0), position(TVector()),
		velocity(TVector()) {}
	Sphere(Type t, double m = defaultMass,double r = defaultRange,
		TVector p = TVector(), TVector v = TVector())
		:type(t), mass(m), range(r), position(p), 
		velocity(v), originalPosition(p) {}

	void move(vector<Sphere *> &spheres, double timeDelta);
	int bump(Sphere &s);

	void setType(Type t);
	void setMass(double m);
	void setRange(double r);
	void setPosition(TVector p);
	void setVelocity(TVector v);

	Type const getType() const { return type; }
	double const getMass() const { return mass; }
	double const getRange() const { return range; }
	TVector const getPosition() const { return position; }
	TVector const getVelocity() const { return velocity; }
	TVector const getOriginalPosition() const { return originalPosition; }
};

#endif // _SPHERE_