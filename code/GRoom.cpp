#include "GRoom.h"

void GRoom::GDrawRoom(GTex *g) {
	GLfloat roomLength = 18.0f, l = roomLength / 2;
	GLfloat roomWidth = 18.0f, w = roomWidth / 2;
	GLfloat roomHeight = 6.0f, flooring = -2.0f, ceiling = 4.0f;

	glTranslatef(0.0f, flooring, 0.0f);
	glBindTexture(GL_TEXTURE_2D, g->getTexture(8));
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-w, 0.0f, -l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-w, 0.0f, l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(w, 0.0f, l);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(w, 0.0f, -l);
	glEnd();
	glTranslatef(0.0f, -flooring, 0.0f);

	glTranslatef(0.0f, ceiling, 0.0f);
	glBindTexture(GL_TEXTURE_2D, g->getTexture(9));
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-w, 0.0f, -l);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(w, 0.0f, -l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(w, 0.0f, l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-w, 0.0f, l);
	glEnd();
	glTranslatef(0.0f, -ceiling, 0.0f);

	glBindTexture(GL_TEXTURE_2D, g->getTexture(7));
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	GDrawWall();
	glEnd();

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	GDrawWall();
	glEnd();

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	GDrawWall();
	glEnd();

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	GDrawWall();
	glEnd();

	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
}

void GRoom::GDrawWall() {
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	float float_x, float_y, float_xb, float_yb;
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 64; y++) {
			float_x = float(x) / 64.0f;				// 生成X浮点值
			float_y = float(y) / 64.0f;				// 生成Y浮点值
			float_xb = float(x + 1) / 64.0f;		// X浮点值+0.0227f
			float_yb = float(y + 1) / 64.0f;		// Y浮点值+0.0227f

			glTexCoord2f(float_x, float_y);			// 第一个纹理坐标 (左下角)
			glVertex3f(points[x][y].x, points[x][y].y, points[x][y].z);
			glTexCoord2f(float_x, float_yb);		// 第二个纹理坐标 (左上角)
			glVertex3f(points[x][y + 1].x, points[x][y + 1].y, points[x][y + 1].z);
			glTexCoord2f(float_xb, float_yb);		// 第三个纹理坐标 (右上角)
			glVertex3f(points[x + 1][y + 1].x, points[x + 1][y + 1].y, points[x + 1][y + 1].z);
			glTexCoord2f(float_xb, float_y);		// 第四个纹理坐标 (右下角)
			glVertex3f(points[x + 1][y].x, points[x + 1][y].y, points[x + 1][y].z);
		}
	}
	glEnd();
}

/*void GRoom::perlin(){
	GLfloat step = 1.0f / 64.0f;
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 64; y++) {
			points[x][y].x = (20.0f * (x * step) - 10.0f);
			points[x][y].y = generatePerlin(x * step, y * step) * 0.2f - 9.0f;
			points[x][y].z = (7.0f * (y * step) - 4.5f);
		}
	}
}

GLfloat GRoom::generatePerlin(GLfloat x, GLfloat y) {
	GLfloat ret = 0.0f;
	GLfloat persist = 0.5f;
	int iterTime = 5;

	for (int i = 0; i < iterTime; i++) {
		GLfloat freq = pow(2.0, i);
		GLfloat amplitude = pow(persist, i);
		ret += generateInterpolateNoise(x * freq, y * freq) * amplitude;
	}
	return ret;
}

GLfloat GRoom::generateInterpolateNoise(GLfloat x, GLfloat y) {
	int xint = x * 512.0f;
	int yint = y * 512.0f;

	float v1 = smoothing(xint, yint);
	float v2 = smoothing(xint + 1, yint);
	float v3 = smoothing(xint, yint + 1);
	float v4 = smoothing(xint + 1, yint + 1);

	float i1 = interpolate(v1, v2, x);
	float i2 = interpolate(v3, v4, x);

	return interpolate(i1, i2, y);
}

GLfloat GRoom::smoothing(GLfloat x, GLfloat y) {
	GLfloat corners = (noise(x - 1, y - 1) + noise(x - 1, y + 1) + noise(x + 1, y - 1) + noise(x + 1, y + 1)) / 16;
	GLfloat sides = (noise(x - 1, y) + noise(x, y - 1) + noise(x + 1, y) + noise(x, y + 1)) / 8;
	GLfloat center = noise(x, y) / 4;
	return corners + sides + center;
}

GLfloat GRoom::interpolate(GLfloat a, GLfloat b, GLfloat x) {
	GLfloat ft = x * PI;
	GLfloat f = (1 - cos(ft)) * 0.5f;
	return a * (1 - f) + b * f;
}

GLfloat GRoom::noise(int x, int y) {
	int n;
	n = x + y * 17;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}*/