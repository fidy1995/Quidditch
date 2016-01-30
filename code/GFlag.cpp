#include "GFlag.h"

void GFlag::GDrawFlag(GTex *g) {
	TVector pos = f->getPosition();
	GLfloat poleRadius = 0.02f;
	GLfloat poleLength = 2.5f;

	// 旗杆
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, g->getTexture(6));
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_SMOOTH);
	gluQuadricTexture(quadric, TRUE);
	gluCylinder(quadric, 2 * poleRadius, poleRadius, poleLength, 25, 25);
	delete quadric;

	// 旗杆顶部的球体
	glTranslatef(0.0f, 0.0f, poleLength);
	glBindTexture(GL_TEXTURE_2D, g->getTexture(0));
	quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_SMOOTH);
	gluQuadricTexture(quadric, TRUE);
	gluSphere(quadric, 2 * poleRadius, 25, 25);
	delete quadric;
	glTranslatef(0.0f, 0.0f, -poleLength);

	float float_x, float_y, float_xb, float_yb;

	glBindTexture(GL_TEXTURE_2D, g->getTexture(5));
	glTranslatef(0, -points[0][0].y, 0);				// 把旗帜固定在旗杆上
	glBegin(GL_QUADS);								// 四边形绘制开始
	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int x = 0; x < 44; x++) {
		for (int y = 0; y < 44; y++) {
			float_x = float(x) / 44.0f;				// 生成X浮点值
			float_y = float(y) / 44.0f;				// 生成Y浮点值
			float_xb = float(x + 1) / 44.0f;		// X浮点值+0.0227f
			float_yb = float(y + 1) / 44.0f;		// Y浮点值+0.0227f

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
	glEnd();										// 四边形绘制结束

	glBegin(GL_QUADS);								// 四边形绘制开始
	glNormal3f(0.0f, 0.0f, -1.0f);
	for (int x = 0; x < 44; x++) {
		for (int y = 0; y < 44; y++) {
			float_x = float(x) / 44.0f;				// 生成X浮点值
			float_y = float(y) / 44.0f;				// 生成Y浮点值
			float_xb = float(x + 1) / 44.0f;		// X浮点值+0.0227f
			float_yb = float(y + 1) / 44.0f;		// Y浮点值+0.0227f

			glTexCoord2f(float_x, float_y);			// 第一个纹理坐标 (左下角)
			glVertex3f(points[x][y].x, points[x][y].y, points[x][y].z);
			glTexCoord2f(float_xb, float_y);		// 第四个纹理坐标 (右下角)
			glVertex3f(points[x + 1][y].x, points[x + 1][y].y, points[x + 1][y].z);
			glTexCoord2f(float_xb, float_yb);		// 第三个纹理坐标 (右上角)
			glVertex3f(points[x + 1][y + 1].x, points[x + 1][y + 1].y, points[x + 1][y + 1].z);
			glTexCoord2f(float_x, float_yb);		// 第二个纹理坐标 (左上角)
			glVertex3f(points[x][y + 1].x, points[x][y + 1].y, points[x][y + 1].z);
		}
	}
	glEnd();										// 四边形绘制结束

	if (frameCount == 5) {							// 用来降低波浪速度(每隔2帧一次)
		for (int y = 0; y < 45; y++) {				// 沿Y平面循环
			hold = points[0][y].y;					// 存储当前左侧波浪值
			for (int x = 0; x < 44; x++) {			// 沿X平面循环
				// 当前波浪值等于其右侧的波浪值
				points[x][y].y = points[x + 1][y].y;
			}
			points[44][y].y = hold;				// 刚才的值成为最左侧的波浪值
		}
		frameCount = 0;								// 计数器清零
	}
	frameCount++;									// 计数器加一
	
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-pos.x, -pos.y, -pos.z);
}