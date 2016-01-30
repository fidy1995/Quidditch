#include "GBat.h"
#include <gl/glew.h>
#include <gl/GLUT.H>

void GBat::GDrawBat(Sphere s, double force, double angle, GTex *g) {
	GLfloat batLength = 4.5f;
	GLfloat batRadius = 0.02f;

	GLfloat xrot = -10.0f;
	GLfloat cosx = cos(-xrot * PI / 180);
	GLfloat sinx = sin(-xrot * PI / 180);
	GLfloat cosa = cos(angle * PI / 180);
	GLfloat sina = sin(angle * PI / 180);
	TVector t = s.getPosition();

	GLfloat f = force / 20 + 0.2f;
	//TVector tv = TVector(f, angle * PI / 180, xrot * PI / 180, 0);
	TVector tv = TVector(f * cosx * sina, f * sinx, f * cosx * cosa);

	glTranslatef(t.x, t.y, t.z);
	glTranslatef(tv.x, tv.y, tv.z);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);

	glBindTexture(GL_TEXTURE_2D, g->getTexture(10));
	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_SMOOTH);
	gluQuadricTexture(quadric, TRUE);
	gluCylinder(quadric, batRadius, 2 * batRadius, batLength, 25, 25);
	delete quadric;


	glRotatef(xrot, -1.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, -1.0f, 0.0f);

	glTranslatef(-tv.x, -tv.y, -tv.z);
	glTranslatef(-t.x, -t.y, -t.z);
}