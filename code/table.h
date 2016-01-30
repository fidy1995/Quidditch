#ifndef _TABLE_
#define _TABLE_

#include "sphere.h"

int const tableLength = 256;
int const tableWidth = 128;

class Table {
	double length;
	double width;

public:
	Table() :length(0.0f), width(0.0f) {}
	Table(double l, double w) :length(l), width(w) {}

	void bump(Sphere &s);

	void setLength(double l);
	void setWidth(double w);

	double const getLength() const { return length; }
	double const getWidth() const { return width; }
};

#endif // _TABLE_