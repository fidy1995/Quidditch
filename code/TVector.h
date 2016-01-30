#ifndef _TVECTOR_
#define _TVECTOR_

// I will realize a naive math lib when I have time
#include <math.h>

using namespace std;

// const pi, finite base-2 decimal, about 3.1416
const double PI = (double)3217 / 1024;
// the ratio of it is 1:32
const int RATIO = 32;

// a simple three-dimensioned vector/position
struct TVector {
	double x, y, z;

	TVector() :x(0.0f), y(0.0f), z(0.0f) {}
	TVector(double xx, double yy, double zz)
		:x(xx), y(yy), z(zz) {}
	TVector(double r, double theta, double fi, int i)
		:x(r * sin(theta) * cos(fi)),
		y(r * sin(theta) * sin(fi)),
		z(r * cos(theta)) {}

	// the model of the vector
	double const model() const {
		return sqrt(x * x + y * y + z * z);
	}
	// rotate anticlockwise
	void rotate(double theta);
	void toPolar();
	void toRect();
};

TVector operator + (TVector a, TVector b); // plus
TVector operator - (TVector a, TVector b); // minus
TVector operator - (TVector a);			   // negative
TVector operator * (double d, TVector t);  // number multiply
TVector operator / (TVector t, double d);  // number multiply(divide)
double  operator * (TVector a, TVector b); // inner multiply
TVector operator & (TVector a, TVector b); // outer multiply
bool    operator ==(TVector a, TVector b); // equal
bool    operator !=(TVector a, TVector b); // non-equal

double  abs(TVector t);                    // same as TVector::model()
TVector rot(TVector t, double theta);      // same as TVector::rotate(theta)
TVector makeUnit(TVector t);			   // make unit vector

#endif // _TVECTOR_