#include "sphere.h"
#include <iostream>

using namespace std;

void Sphere::move(vector<Sphere *> &spheres, double timeDelta)
{
	// if it is a Noisy ball
	if (type == NOISE) {
		// naive move
		moving(position, velocity, timeDelta);
		// detect upcoming bumps
		for (int i = 0; i < spheres.size(); i++) {
			if (abs(position - spheres[i]->position) <= 4 * range
				&& position != spheres[i]->position) {
				TVector temp = position - spheres[i]->position;
				temp.y = 0;
				accelerate(velocity,
					defaultFriction * makeUnit(temp),
					timeDelta);
			}
		}
		// speed down
		if (abs(velocity) > defaultVelocity) {
			accelerate(velocity,
				defaultFriction * makeUnit(-velocity), timeDelta);
			if (abs(velocity) < defaultVelocity) {
				velocity = defaultVelocity * makeUnit(velocity);
			}
		}
		// speed up
		else if (abs(velocity) < defaultVelocity) {
			accelerate(velocity,
				defaultFriction * makeUnit(velocity), timeDelta);
			if (abs(velocity) > defaultVelocity) {
				velocity = defaultVelocity * makeUnit(velocity);
			}
		}
	}
	else if (type == GOLD) {
		static int tsec = 0;
		static bool gotoTable = false;
		if (tsec >= 5000) {
			// go to the table
			gotoTable = true;
			velocity = TVector(0.0, -0.5f, 0.0);
		}
		if (gotoTable == true) {
			moving(position, velocity, timeDelta);
			if (tsec >= 0 && position.y <= range) {
				velocity = TVector();
				position.y = range;
			}
			if (tsec == 1500) {
				velocity = TVector(0.0, 0.5f, 0.0);
			}
			tsec -= 3;
			if (tsec <= 0 || position.y >= defaultHeight) {
				tsec = 0;
				position.y = defaultHeight;
				velocity = TVector(0.75, 0.0, 1.15);
				gotoTable = false;
			}
		}
		else {
			TVector posTemp;
			if (position.z > 0) {
				posTemp = position - defaultDownCenter;
			}
			else {
				posTemp = position - defaultUpCenter;
			}
			accelerate(velocity, 
				TVector((double)(rand() % 100) / 100, 0, double (rand() % 100) / 100),
				timeDelta);
			moving(position, velocity, timeDelta);
		}
		tsec = tsec + 1;
	}
	else {
		moving(position, velocity, timeDelta);
		TVector vtemp = velocity;
		accelerate(velocity,
			defaultFriction * makeUnit(-velocity), timeDelta);
		if (vtemp * velocity < 0) {
			velocity = TVector();
		}
	}
}

int Sphere::bump(Sphere &s)
{
	TVector dist = s.position - position;
	if (abs(dist) <= 2.0f * range
		&& dist * velocity > dist * s.velocity) {
		if (s.getType() != GOLD) {
			crush(position, s.position,
				velocity, s.velocity);
			return 1;
		}
		else {
			s.setType(DEFAULT);
			return 15;
		}
	}
	return 0;
}

void Sphere::setType(Type t)
{
	type = t;
}

void Sphere::setMass(double m)
{
	if (m <= 0) {
		cout << "setMass: m < 0\n";
		return;
	}
	mass = m;
}

void Sphere::setRange(double r)
{
	if (r <= 0) {
		cout << "setRange: r < 0\n";
		return;
	}
	range = r;
}

void Sphere::setPosition(TVector p)
{
	position = p;
}

void Sphere::setVelocity(TVector v)
{
	velocity = v;
}