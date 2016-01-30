#include "GFlag.h"

void GFlag::GDrawFlag(GTex *g) {
	TVector pos = f->getPosition();
	GLfloat poleRadius = 0.02f;
	GLfloat poleLength = 2.5f;

	// ���
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, g->getTexture(6));
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_SMOOTH);
	gluQuadricTexture(quadric, TRUE);
	gluCylinder(quadric, 2 * poleRadius, poleRadius, poleLength, 25, 25);
	delete quadric;

	// ��˶���������
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
	glTranslatef(0, -points[0][0].y, 0);				// �����Ĺ̶��������
	glBegin(GL_QUADS);								// �ı��λ��ƿ�ʼ
	glNormal3f(0.0f, 0.0f, 1.0f);
	for (int x = 0; x < 44; x++) {
		for (int y = 0; y < 44; y++) {
			float_x = float(x) / 44.0f;				// ����X����ֵ
			float_y = float(y) / 44.0f;				// ����Y����ֵ
			float_xb = float(x + 1) / 44.0f;		// X����ֵ+0.0227f
			float_yb = float(y + 1) / 44.0f;		// Y����ֵ+0.0227f

			glTexCoord2f(float_x, float_y);			// ��һ���������� (���½�)
			glVertex3f(points[x][y].x, points[x][y].y, points[x][y].z);
			glTexCoord2f(float_x, float_yb);		// �ڶ����������� (���Ͻ�)
			glVertex3f(points[x][y + 1].x, points[x][y + 1].y, points[x][y + 1].z);
			glTexCoord2f(float_xb, float_yb);		// �������������� (���Ͻ�)
			glVertex3f(points[x + 1][y + 1].x, points[x + 1][y + 1].y, points[x + 1][y + 1].z);
			glTexCoord2f(float_xb, float_y);		// ���ĸ��������� (���½�)
			glVertex3f(points[x + 1][y].x, points[x + 1][y].y, points[x + 1][y].z);
		}
	}
	glEnd();										// �ı��λ��ƽ���

	glBegin(GL_QUADS);								// �ı��λ��ƿ�ʼ
	glNormal3f(0.0f, 0.0f, -1.0f);
	for (int x = 0; x < 44; x++) {
		for (int y = 0; y < 44; y++) {
			float_x = float(x) / 44.0f;				// ����X����ֵ
			float_y = float(y) / 44.0f;				// ����Y����ֵ
			float_xb = float(x + 1) / 44.0f;		// X����ֵ+0.0227f
			float_yb = float(y + 1) / 44.0f;		// Y����ֵ+0.0227f

			glTexCoord2f(float_x, float_y);			// ��һ���������� (���½�)
			glVertex3f(points[x][y].x, points[x][y].y, points[x][y].z);
			glTexCoord2f(float_xb, float_y);		// ���ĸ��������� (���½�)
			glVertex3f(points[x + 1][y].x, points[x + 1][y].y, points[x + 1][y].z);
			glTexCoord2f(float_xb, float_yb);		// �������������� (���Ͻ�)
			glVertex3f(points[x + 1][y + 1].x, points[x + 1][y + 1].y, points[x + 1][y + 1].z);
			glTexCoord2f(float_x, float_yb);		// �ڶ����������� (���Ͻ�)
			glVertex3f(points[x][y + 1].x, points[x][y + 1].y, points[x][y + 1].z);
		}
	}
	glEnd();										// �ı��λ��ƽ���

	if (frameCount == 5) {							// �������Ͳ����ٶ�(ÿ��2֡һ��)
		for (int y = 0; y < 45; y++) {				// ��Yƽ��ѭ��
			hold = points[0][y].y;					// �洢��ǰ��ನ��ֵ
			for (int x = 0; x < 44; x++) {			// ��Xƽ��ѭ��
				// ��ǰ����ֵ�������Ҳ�Ĳ���ֵ
				points[x][y].y = points[x + 1][y].y;
			}
			points[44][y].y = hold;				// �ղŵ�ֵ��Ϊ�����Ĳ���ֵ
		}
		frameCount = 0;								// ����������
	}
	frameCount++;									// ��������һ
	
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(-pos.x, -pos.y, -pos.z);
}