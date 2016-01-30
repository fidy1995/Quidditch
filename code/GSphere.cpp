#include "GSphere.h"
#include <gl/glew.h>
#include <gl/GLUT.H>

void GSphere::GDrawSphere(GTex *g) {
	double r = sphere->getRange();
	TVector pos = sphere->getPosition();
	TVector originPos = sphere->getOriginalPosition();
	Type t = sphere->getType();

	switch (t) {
	case CUE:
		glBindTexture(GL_TEXTURE_2D, g->getTexture(0)); 
		break;
	case QUIET:
		glBindTexture(GL_TEXTURE_2D, g->getTexture(1));
		break;
	case NOISE:
		glBindTexture(GL_TEXTURE_2D, g->getTexture(2));
		break;
	case GOLD:
		glBindTexture(GL_TEXTURE_2D, g->getTexture(3));
		break;
	default:
		break;
	}
	glTranslatef(pos.x, pos.y, pos.z);
	
	/*double deltaX = double(pos.x - originPos.x) * RATIO / (PI * 2 * r);
	double deltaZ = double(pos.z - originPos.z) * RATIO / (PI * 2 * r);

	glRotatef(deltaX, 0.0f, 0.0f, -1.0f);
	glRotatef(deltaZ, 1.0f, 0.0f, 0.0f);*/

	// a not well-optimized sphere drawing with polar
	/*for (GLfloat i = 0.0f; i < PI; i += 0.1f) {
		double ci = cos(i), si = sin(i);
		double cii = cos(i + 0.1f), sii = sin(i + 0.1f);
		for (GLfloat j = 0.0f; j < PI * 2; j += 0.1f) {
			double cj = cos(j), sj = sin(j);
			double cji = cos(j + 0.1f), sji = (j + 0.1f);
			glBegin(GL_QUADS);
			glNormal3f(r * cj * si, r * sj * si, r * ci);
			glVertex3f(r * cj * si, r * sj * si, r * ci);
			glVertex3f(r * cji * si, r * sji * si, r * ci);
			glVertex3f(r * cji * sii, r * sji * sii, r * cii);
			glVertex3f(r * cj * sii, r * si * sii, r * cii);
			glEnd();
		}
	}*/

	GLUquadricObj *quadric = gluNewQuadric();
	gluQuadricNormals(quadric, GL_SMOOTH);
	gluQuadricTexture(quadric, TRUE);
	gluSphere(quadric, r, 25, 25);
	delete quadric;
	if (t == CUE) {
		GLfloat spotPos[] = { 0.0f, 10.0f, 0.0f, 1.0f };
		GLfloat direction[] = { 0.0f, -1.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT1, GL_POSITION, spotPos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);
	}
	glTranslatef(-pos.x, -pos.y, -pos.z);
}