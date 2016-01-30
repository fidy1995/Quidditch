#include "tvector.h"

void TVector::rotate(double theta) 
{
	double xtemp, ztemp;
	xtemp = x * cos(theta) - z * sin(theta);
	ztemp = z * cos(theta) + x * sin(theta);
	x = xtemp; z = ztemp;
}

void TVector::toPolar() 
{
	double r, theta, fi;
	r = sqrt(x * x + y * y + z * z);
	theta = acos(z / r);
	fi = atan(y / x);
	x = r; y = theta; z = fi;
}

void TVector::toRect()
{
	double r = x, theta = y, fi = z;
	x = r * sin(theta) * cos(fi);
	y = r * sin(theta) * sin(fi);
	z = r * cos(theta);
}

// plus
TVector operator + (TVector a, TVector b) 
{
	return TVector(a.x + b.x, a.y + b.y, a.z + b.z);
}

// minus
TVector operator - (TVector a, TVector b) 
{
	return TVector(a.x - b.x, a.y - b.y, a.z - b.z);
}

// negative
TVector operator - (TVector a)
{
	return TVector(-a.x, -a.y, -a.z);
}

// number multiply
TVector operator * (double d, TVector t)
{
	return TVector(d * t.x, d * t.y, d * t.z);
}

// number multiply(divide)
TVector operator / (TVector t, double d)
{
	return (1 / d) * t;
}

// inner multiply
double operator * (TVector a, TVector b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

// outer multiply
TVector operator & (TVector a, TVector b)
{
	return TVector(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

// equal
bool operator ==(TVector a, TVector b)
{
	return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

// non-equal
bool operator !=(TVector a, TVector b)
{
	return !(a == b);
}

// same as TVector::model()
double abs(TVector t)
{
	return t.model();
}

// same as TVector::rotate(theta)
TVector rot(TVector t, double theta)
{
	return TVector(t.x * cos(theta) - t.z * sin(theta), 
		t.y,
		t.z * cos(theta) + t.x * sin(theta));
}

TVector makeUnit(TVector t)
{
	double model = t.model();
	if (model == 0) {
		return TVector();
	}
	return TVector(t.x / model, t.y / model, t.z / model);
}