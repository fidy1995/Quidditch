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

			p[loop].pos.x += p[loop].velo.x / 1000;		// ����X�����λ��
			p[loop].pos.y += p[loop].velo.y / 1000;		// ����Y�����λ��
			p[loop].pos.z += p[loop].velo.z / 1000;		// ����Z�����λ��

			p[loop].life -= p[loop].fade;				// �������ӵ�����ֵ
			if (p[loop].life < 0.0f) {					// �����������ֵС��0
				p[loop].life = 1.0f;					// ����һ���µ�����
				p[loop].fade = float(rand() % 100) / 1000.0f + 0.005f;		// �������˥������
				p[loop].pos.x = 0.0f;		// ����X�����λ��
				p[loop].pos.y = 0.0f;		// ����Y�����λ��
				p[loop].pos.z = 0.0f;		// ����Z�����λ��
				p[loop].velo.x = float((rand() % 45) - 22.0f) / 9.0f;		// �������X�᷽���ٶ�
				p[loop].velo.y = float((rand() % 45) - 22.0f) / 9.0f;		// �������Y�᷽���ٶ�
				p[loop].velo.z = float((rand() % 45) - 22.0f) / 9.0f;		// �������Z�᷽���ٶ�
			}
		}
	}
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	
	glTranslatef(-cp.x, -cp.y, -cp.z);
}