#include "GTable.h"
#include <gl/glew.h>

void GTable::GDrawTable(GTex *g) {
	GLfloat width = table->getWidth();
	GLfloat w = width / 2;
	GLfloat length = table->getLength();
	GLfloat l = length / 2;
	GLfloat y = -0.25f;
	GLfloat lowRadius = 0.075f;
	GLfloat highRadius = 0.1f;
	GLfloat poleLength = 2.0f;

	glBindTexture(GL_TEXTURE_2D, g->getTexture(4));

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-w, 0.0f, l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-w, y, l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(w, y, l);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(w, 0.0f, l);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-w, 0.0f, -l);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(w, 0.0f, -l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(w, y, -l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-w, y, -l);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-w, 0.0f, l);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-w, 0.0f, -l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-w, y, -l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-w, y, l);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(w, 0.0f, l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(w, y, l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(w, y, -l);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(w, 0.0f, -l);
	glEnd();

	GLfloat fx, fy, fxb, fyb;
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int x = 0; x < 64; x++) {
		for (int y = 0; y < 64; y++) {
			fx = float(x) / 64.0f * width;				// ����X����ֵ
			fy = float(y) / 64.0f * length;				// ����Y����ֵ
			fxb = float(x + 1) / 64.0f * width;			// X����ֵ+0.0227f
			fyb = float(y + 1) / 64.0f * length;		// Y����ֵ+0.0227f

			glColor3f(0.0f, color[x][y], 0.0f);			// ��һ���������� (���½�)
			glVertex3f(-w + fx, 0.0f, -l + fy);
			glColor3f(0.0f, color[x][y + 1], 0.0f);		// �ڶ����������� (���Ͻ�)
			glVertex3f(-w + fx, 0.0f, -l + fyb);
			glColor3f(0.0f, color[x + 1][y + 1], 0.0f);		// �������������� (���Ͻ�)
			glVertex3f(-w + fxb, 0.0f, -l + fyb);
			glColor3f(0.0f, color[x + 1][y], 0.0f);		// ���ĸ��������� (���½�)
			glVertex3f(-w + fxb, 0.0f, -l + fy);
		}
	}
	/*glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-w, 0.0f, -l);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(w, 0.0f, -l);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(w, 0.0f, l);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-w, 0.0f, l);*/
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, g->getTexture(6));
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_SMOOTH);
	gluQuadricTexture(quadric, TRUE);

	glTranslatef(w - 0.25f, -0.1f, l - 0.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadric, highRadius, lowRadius, poleLength, 25, 25);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glTranslatef(-w + 0.25f, 0.1f, -l + 0.5f);

	glTranslatef(-w + 0.25f, -0.1f, -l + 0.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadric, highRadius, lowRadius, poleLength, 25, 25);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glTranslatef(w - 0.25f, 0.1f, l - 0.5f);

	glTranslatef(-w + 0.25f, -0.1f, l - 0.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadric, highRadius, lowRadius, poleLength, 25, 25);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glTranslatef(w - 0.25f, 0.1f, -l + 0.5f);

	glTranslatef(w - 0.25f, -0.1f, -l + 0.5f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(quadric, highRadius, lowRadius, poleLength, 25, 25);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glTranslatef(-w + 0.25f, 0.1f, l - 0.5f);

	delete quadric;
}