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

static GLfloat colors[12][3] =				// �ʺ���ɫ
{
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};

class GParticle {
	Particle p[MAX_PARTICLES];
public:
	GParticle() {
		for (int loop = 0; loop < MAX_PARTICLES; loop++) {						//��ʼ�����е�����
			p[loop].active = true;										// ʹ���е�����Ϊ����״̬
			p[loop].life = 1.0f;										// ���е���������ֵΪ���
			p[loop].fade = float(rand() % 100) / 1000.0f + 0.005f;		// �������˥������
			p[loop].color.x = colors[loop * 12 / MAX_PARTICLES][0];		// ���ӵĺ�ɫ��ɫ
			p[loop].color.y = colors[loop * 12 / MAX_PARTICLES][1];		// ���ӵ���ɫ��ɫ
			p[loop].color.z = colors[loop * 12 / MAX_PARTICLES][2];		// ���ӵ���ɫ��ɫ		
			p[loop].velo.x = float((rand() % 45) - 22.0f) / 9.0f;		// �������X�᷽���ٶ�
			p[loop].velo.y = float((rand() % 45) - 22.0f) / 9.0f;		// �������Y�᷽���ٶ�
			p[loop].velo.z = float((rand() % 45) - 22.0f) / 9.0f;		// �������Z�᷽���ٶ�
			p[loop].acle.x = 0.0f;						// ����X�᷽����ٶ�Ϊ0
			p[loop].acle.y = 0.0f;						// ����Y�᷽����ٶ�Ϊ0
			p[loop].acle.z = 0.0f;						// ����Z�᷽����ٶ�Ϊ0
		}
	}

	void drawParticles(GTex *t, TVector cp);
};

#endif // _G_PARTICLE_