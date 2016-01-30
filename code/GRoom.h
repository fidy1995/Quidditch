#ifndef _G_ROOM_
#define _G_ROOM_

#include "GTex.h"
#include "tvector.h"
#include "perlin.h"

class GRoom {
	TVector points[64][64];

	void GDrawWall();

	/*void perlin();

	GLfloat generatePerlin(GLfloat x, GLfloat y);
	GLfloat generateInterpolateNoise(GLfloat x, GLfloat y);
	GLfloat smoothing(GLfloat x, GLfloat y);
	GLfloat interpolate(GLfloat a, GLfloat b, GLfloat x);
	GLfloat noise(int x, int y);*/

public:
	GRoom() {}
	GRoom(Perlin *perlin) {
		float step = 1.0f / 64.0f;
		for (int x = 0; x < 64; x++) {
			for (int y = 0; y < 64; y++) {
				points[x][y].x = (20.0f * (x * step) - 10.0f);
				points[x][y].y = perlin->getValue(x, y) * 0.25f - 9.0f;
				points[x][y].z = (7.0f * (y * step) - 4.5f);
			}
		}
	}

	void GDrawRoom(GTex *g);
};

#endif // _G_ROOM_