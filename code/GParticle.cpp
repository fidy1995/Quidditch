#include "GParticle.h"

void GParticle::drawParticles(GTex *t, TVector cp) {
	glTranslatef(cp.x, cp.y, cp.z);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	for (int loop = 0; loop < MAX_PARTICLES; loop++) {
		if (p[loop].active) {
			float x = p[loop].pos.x;
			float y = p[loop].pos.y;
			float z = p[loop].pos.z;
			glColor4f(p[loop].color.x, 
				p[loop].color.y, 
				p[loop].color.z, 
				p[loop].life);

			glTranslatef(x, y, z);
			GLUquadricObj *quadric = gluNewQuadric();
			/*gluQuadricNormals(quadric, GL_SMOOTH);
			gluQuadricTexture(quadric, TRUE);*/
			gluSphere(quadric, 0.015f, 3, 3);
			delete quadric;
			glTranslatef(-x, -y, -z);

			p[loop].pos.x += p[loop].velo.x / 1000;		// 更新X坐标的位置
			p[loop].pos.y += p[loop].velo.y / 1000;		// 更新Y坐标的位置
			p[loop].pos.z += p[loop].velo.z / 1000;		// 更新Z坐标的位置

			p[loop].life -= p[loop].fade;				// 减少粒子的生命值
			if (p[loop].life < 0.0f) {					// 如果粒子生命值小于0
				p[loop].life = 1.0f;					// 产生一个新的粒子
				p[loop].fade = float(rand() % 100) / 1000.0f + 0.005f;		// 随机生成衰减速率
				p[loop].pos.x = 0.0f;		// 重置X坐标的位置
				p[loop].pos.y = 0.0f;		// 重置Y坐标的位置
				p[loop].pos.z = 0.0f;		// 重置Z坐标的位置
				p[loop].velo.x = float((rand() % 45) - 22.0f) / 9.0f;		// 随机生成X轴方向速度
				p[loop].velo.y = float((rand() % 45) - 22.0f) / 9.0f;		// 随机生成Y轴方向速度
				p[loop].velo.z = float((rand() % 45) - 22.0f) / 9.0f;		// 随机生成Z轴方向速度
			}
		}
	}
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glTranslatef(-cp.x, -cp.y, -cp.z);
}