#ifndef _G_FLAG_
#define _G_FLAG_

#include <math.h>

#include "flag.h"

#include "GTex.h"

#include <gl/glew.h>
#include <gl/GLUT.H>

class GFlag {
	Flag *f;

	TVector points[45][45];
	int frameCount;
	GLfloat hold;

public:
	GFlag() : f(NULL) {}
	GFlag(Flag fl){
		TVector pos = fl.getPosition();
		f = new Flag(pos);

		for (int x = 0; x < 45; x++) {
			// 沿Y平面循环
			for (int y = 0; y < 45; y++) {
				// 向表面添加波浪效果
				points[x][y].x = float((x / 30.0f));
				points[x][y].y = float(sin((((x / 5.0f) * 40.0f) / 360.0f) * PI * 2.0f) * 0.25);
				points[x][y].z = float((y / 45.0f) + 1.5f);
			}
		}
	}

	void GDrawFlag(GTex *g);
};

#endif // _G_FLAG_