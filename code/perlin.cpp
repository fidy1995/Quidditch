#include "perlin.h"

void Perlin::perlin(){
	float step = 1.0f / 64.0f;
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 64; y++) {
			values[x][y] = generatePerlin(step * x, step * y);
			if (values[x][y] < 0) {
				values[x][y] = -values[x][y];
			}
		}
	}
}

float Perlin::generatePerlin(float x, float y) {
	float ret = 0.0f;
	float persist = 0.5f;
	int iterTime = 8;

	for (int i = 0; i < iterTime; i++) {
		float freq = pow(2.0, i);
		float amplitude = pow(persist, i);
		ret += generateInterpolateNoise(x * freq, y * freq) * amplitude;
	}
	return ret;
}

float Perlin::generateInterpolateNoise(float x, float y) {
	int xint = x * 64.0f;
	int yint = y * 64.0f;

	float v1 = smoothing(xint, yint);
	float v2 = smoothing(xint + 1, yint);
	float v3 = smoothing(xint, yint + 1);
	float v4 = smoothing(xint + 1, yint + 1);

	float i1 = interpolate(v1, v2, x);
	float i2 = interpolate(v3, v4, x);

	return interpolate(i1, i2, y);
}

float Perlin::smoothing(float x, float y) {
	float corners = (noise(x - 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y - 1) + noise(x + 1, y + 1)) / 16;
	float sides = (noise(x - 1, y) + noise(x, y - 1) + noise(x + 1, y) + noise(x, y + 1)) / 8;
	float center = noise(x, y) / 4;
	return corners + sides + center;
}

float Perlin::interpolate(float a, float b, float x) {
	float ft = x * PI;
	float f = (1 - cos(ft)) * 0.5f;
	return a * (1 - f) + b * f;
}

float Perlin::noise(int x, int y) {
	int n;
	n = x + y * 17;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}