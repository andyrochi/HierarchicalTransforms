#include "Utils.h"

// wireBox(w, h, d) makes a wireframe box with width w, height h and
// depth d centered at the origin.  It uses the GLUT wire cube function.
// The calls to glPushMatrix and glPopMatrix are essential here; they enable
// this function to be called from just about anywhere and guarantee that
// the glScalef call does not pollute code that follows a call to myWireBox.
void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
	glScalef(width, height, depth);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawAxis() {
	glPushMatrix();
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();

	glColor3f(0, 1.0, 0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);
	glEnd();

	glColor3f(0.0, 0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();
	glPopMatrix();
}