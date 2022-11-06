// This program is from the OpenGL Programming Guide.  It shows a robot arm
// that you can rotate by pressing the arrow keys.
#include <GL/freeglut.h>
#include <cstdio>
#include "Camera.h"

// The robot arm is specified by (1) the angle that the upper arm makes
// relative to the x-axis, called shoulderAngle, and (2) the angle that the
// lower arm makes relative to the upper arm, called elbowAngle.  These angles
// are adjusted in 5 degree increments by a keyboard callback.
static int shoulderAngle = 0, elbowAngle = 0;

static int shoulderOpenAngle = 0, shoulderTwistAngle = 0;

static int leftThighAngle = 0, leftCalfAngle = 0,
			rightThighAngle = 0, rightCalfAngle = 0;

// Initialize camera
Camera camera;

// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: camera.moveLeft(); break;
	case GLUT_KEY_RIGHT: camera.moveRight(); break;
	case GLUT_KEY_UP: camera.moveUp(); break;
	case GLUT_KEY_DOWN: camera.moveDown(); break;
	}
	glutPostRedisplay();
}

// Handles the keyboard event: 
void key(unsigned char key, int, int) {
	switch (key) {
	case 'W':
	case 'w':
		(shoulderOpenAngle += 5) %= 360; break;
	case 'S':
	case 's':
		(shoulderOpenAngle -= 5) %= 360; break;
	case 'A':
	case 'a':
		(shoulderTwistAngle += 5) %= 360; break;
	case 'D':
	case 'd':
		(shoulderTwistAngle -= 5) %= 360; break;
	case 'J':
	case 'j':
		(elbowAngle += 5) %= 360; break;
	case 'L':
	case 'l':
		(elbowAngle -= 5) %= 360; break;
	case 'I':
	case 'i':
		(shoulderAngle += 5) %= 360; break;
	case 'K':
	case 'k':
		(shoulderAngle -= 5) %= 360; break;

	case '1':
		(leftThighAngle -= 5) %= 360; break;
	case '2':
		(leftThighAngle += 5) %= 360; break;
	case '3':
		(leftCalfAngle -= 5) %= 360; break;
	case '4':
		(leftCalfAngle += 5) %= 360; break;

	case '5':
		(rightThighAngle -= 5) %= 360; break;
	case '6':
		(rightThighAngle += 5) %= 360; break;
	case '7':
		(rightCalfAngle -= 5) %= 360; break;
	case '8':
		(rightCalfAngle += 5) %= 360; break;
	default: return;
	}
	glutPostRedisplay();
}

// wireBox(w, h, d) makes a wireframe box with width w, height h and
// depth d centered at the origin.  It uses the GLUT wire cube function.
// The calls to glPushMatrix and glPopMatrix are essential here; they enable
// this function to be called from just about anywhere and guarantee that
// the glScalef call does not pollute code that follows a call to myWireBox.
void wireBox(GLdouble width, GLdouble height, GLdouble depth) {
	glPushMatrix();
	glScalef(width, height, depth);
	glutWireCube(1.0);
	glPopMatrix();
}

void drawLeftArm(GLfloat centerDist=1.0) {
	glPushMatrix();

	glColor3f(1.0, 0.0, 0.0);
	// Draw the upper arm, rotated shoulder degrees about the y-axis.  Note that
	// the thing about glutWireBox is that normally its origin is in the middle
	// of the box, but we want the "origin" of our box to be at the left end of
	// the box, so it needs to first be shifted 1 unit in the -z direction, then
	// rotated.
	glTranslatef(0.0, 0.0, -centerDist); // shift entire arm in -z direction
	glRotatef((GLfloat)shoulderOpenAngle, 1.0, 0.0, 0.0); // open arm w.r.t. x-axis
	glRotatef((GLfloat)shoulderAngle, 0.0, 1.0, 0.0); 
	glRotatef((GLfloat)shoulderTwistAngle, 0.0, 0.0, 1.0); // twist arm
	glTranslatef(0.0, 0.0, -1.0); // shift towards -z direction

	wireBox(1.0, 0.4, 2.0);

	// Now we are ready to draw the lower arm.  Since the lower arm is attached
	// to the upper arm we put the code here so that all rotations we do are
	// relative to the rotation that we already made above to orient the upper
	// arm.  So, we want to rotate elbow degrees about the y-axis.  But, like
	// before, the anchor point for the rotation is at the end of the box, so
	// we translate <0,0,-1> before rotating.  But after rotating we have to
	// position the lower arm at the end of the upper arm, so we have to
	// translate it <0,0,-1> again.
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef((GLfloat)elbowAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -1.0); // displace
	wireBox(1.0, 0.4, 2.0);

	glPopMatrix();
}

void drawRightArm(GLfloat centerDist=1.0) {
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);

	// Draw the upper arm, rotated shoulder degrees about the y-axis.  Note that
	// the thing about glutWireBox is that normally its origin is in the middle
	// of the box, but we want the "origin" of our box to be at the right end of
	// the box, so it needs to first be shifted 1 unit in the z direction, then
	// rotated.
	glTranslatef(0.0, 0.0, centerDist); // shift entire arm in z direction
	glRotatef((GLfloat)-shoulderOpenAngle, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)-shoulderAngle, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)shoulderTwistAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 1.0);

	wireBox(1.0, 0.4, 2.0);

	// Now we are ready to draw the lower arm.  Since the lower arm is attached
	// to the upper arm we put the code here so that all rotations we do are
	// relative to the rotation that we already made above to orient the upper
	// arm.  So, we want to rotate elbow degrees about the y-axis.  But, like
	// before, the anchor point for the rotation is at the end of the box, so
	// we translate <0,0,1> before rotating.  But after rotating we have to
	// position the lower arm at the end of the upper arm, so we have to
	// translate it <0,0,1> again.
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef((GLfloat)-elbowAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 1.0);
	wireBox(1.0, 0.4, 2.0);

	glPopMatrix();
}

void drawTorso() {
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.0, -2.0, 0);
	glRotatef(90.0, 0, 1, 0);
	wireBox(3.0, 4., 1.0);
	glPopMatrix();
}

void drawLeftLeg() {
	glPushMatrix();

	glColor3f(1.0, 0.0, 0.0);
	
	glTranslatef(0.0, -4.0, -0.75); // shift entire arm in -z direction
	glRotatef((GLfloat)leftThighAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);

	wireBox(1.0, 2.0, 1.0);

	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)leftCalfAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.0, 0.5);

	glPopMatrix();
}

void drawRightLeg() {
	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);

	glTranslatef(0.0, -4.0, 0.75); // shift entire arm in -z direction
	glRotatef((GLfloat)rightThighAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);

	wireBox(1.0, 2.0, 1.0);

	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)rightCalfAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.0, 0.5);

	glPopMatrix();
}

void drawHead() {
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glTranslatef(0.0, 0.6, 0); // shift entire arm in -z direction
	wireBox(1.0, 1.2, 1.0);

	glPopMatrix();
}

// Displays the arm in its current position and orientation.  The whole
// function is bracketed by glPushMatrix and glPopMatrix calls because every
// time we call it we are in an "environment" in which a gluLookAt is in
// effect.  (Note that in particular, replacing glPushMatrix with
// glLoadIdentity makes you lose the camera setting from gluLookAt).
void display() {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);


	drawLeftArm(1.5);
	drawRightArm(1.5);
	drawTorso();

	drawLeftLeg();
	drawRightLeg();

	drawHead();

	printf("shoulderAngle: %d, shoulderOpenAngle: %d, shoulderTwistAngle: %d\n", shoulderAngle, shoulderOpenAngle, shoulderTwistAngle);
	printf("elbowAngle: %d\n", elbowAngle);
	printf("leftThighAngle: %d, rightThighAngle: %d\n", leftThighAngle, rightThighAngle);
	glFlush();
}

// Handles the reshape event by setting the viewport so that it takes up the
// whole visible region, then sets the projection matrix to something reason-
// able that maintains proper aspect ratio.
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, GLfloat(w) / GLfloat(h), 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

// Perfroms application specific initialization: turn off smooth shading,
// sets the viewing transformation once and for all.  In this application we
// won't be moving the camera at all, so it makes sense to do this.
void init() {
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1, 2, 8
	//	, 0, 0, 0
	//	, 0, 1, 0);
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Robot Arm");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	init();
	glutMainLoop();
}