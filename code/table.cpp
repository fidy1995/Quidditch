#include "table.h"
#include <iostream>

using namespace std;

void Table::bump(Sphere &s) 
{
	TVector pos = s.getPosition();
	TVector vel = s.getVelocity();
	double range = s.getRange();
	if (pos.x + range >= width / 2 || pos.x - range <= -width / 2) {
		vel.x = -vel.x;
		s.setVelocity(vel);
		if (pos.x > 0) {
			pos.x = width / 2 - range - 0.01f;
		}
		else {
			pos.x = -width / 2 + range + 0.01f;
		}
		s.setPosition(pos);
	}
	if (pos.z + range >= length / 2 || pos.z - range <= -length / 2) {
		vel.z = -vel.z;
		s.setVelocity(vel);
		if (pos.z > 0) {
			pos.z = length / 2 - range - 0.01f;
		}
		else {
			pos.z = -length / 2 + range + 0.01f;
		}
		s.setPosition(pos);
	}
}

void Table::setLength(double l)
{
	if (l <= 0) {
		cout << "setLength: l <= 0\n";
		return;
	}
	length = l;
}

void Table::setWidth(double w)
{
	if (w <= 0) {
		cout << "setWidth: w <= 0\n";
		return;
	}
	width = w;
}