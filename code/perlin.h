#ifndef _PERLIN_
#define _PERLIN_

#include "tvector.h"

class Perlin {
	float values[64][64];

	void perlin();

	float generatePerlin(float x, float y);
	float generateInterpolateNoise(float x, float y);
	float smoothing(float x, float y);
	float interpolate(float a, float b, float x);
	float noise(int x, int y);

public:
	Perlin() { perlin(); }

	float const getValue(int x, int y) const { return (x >= 0 && y >= 0 && x < 64 && y < 64) ? values[x][y] : 0.0f; }
};

#endif // _PERLIN_