#ifndef _G_PARTICLE_
#define _G_PARTICLE_

#include "tvector.h"
#include "GTex.h"

const int MAX_PARTICLES = 300;

struct Particle {
	bool active;
	float life;
	float fade;

	TVector color;
	TVector pos;
	TVector velo;
	TVector acle;

	Particle() : pos(TVector()), velo(TVector()), life(1.0f) {};
	Particle(TVector p) : pos(p) {
		life = 1.0f;
		velo = TVector();
	}
};

static GLfloat colors[12][3] =				// 彩虹颜色
{
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};

class GParticle {
	Particle p[MAX_PARTICLES];
public:
	GParticle() {
		for (int loop = 0; loop < MAX_PARTICLES; loop++) {						//初始化所有的粒子
			p[loop].active = true;										// 使所有的粒子为激活状态
			p[loop].life = 1.0f;										// 所有的粒子生命值为最大
			p[loop].fade = float(rand() % 100) / 1000.0f + 0.005f;		// 随机生成衰减速率
			p[loop].color.x = colors[loop * 12 / MAX_PARTICLES][0];		// 粒子的红色颜色
			p[loop].color.y = colors[loop * 12 / MAX_PARTICLES][1];		// 粒子的绿色颜色
			p[loop].color.z = colors[loop * 12 / MAX_PARTICLES][2];		// 粒子的蓝色颜色		
			p[loop].velo.x = float((rand() % 45) - 22.0f) / 9.0f;		// 随机生成X轴方向速度
			p[loop].velo.y = float((rand() % 45) - 22.0f) / 9.0f;		// 随机生成Y轴方向速度
			p[loop].velo.z = float((rand() % 45) - 22.0f) / 9.0f;		// 随机生成Z轴方向速度
			p[loop].acle.x = 0.0f;						// 设置X轴方向加速度为0
			p[loop].acle.y = 0.0f;						// 设置Y轴方向加速度为0
			p[loop].acle.z = 0.0f;						// 设置Z轴方向加速度为0
		}
	}

	void drawParticles(GTex *t, TVector cp);
};

#endif // _G_PARTICLE_