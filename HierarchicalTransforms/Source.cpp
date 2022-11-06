// This program is from the OpenGL Programming Guide.  It shows a robot arm
// that you can rotate by pressing the arrow keys.
#include "Camera.h"
#include "Robot.h"

const bool showAxis = false;

// Initialize camera
Camera camera;

// Initialize robot
Robot robot;

bool run = false;
int refreshMillis = 50;
float delta = 0.0;
bool showGround = true;

void drawGround() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = -10; i < 11; i++) {
		glVertex3f(-10.0, -8.0, (GLfloat)i);
		glVertex3f(10.0, -8.0, (GLfloat)i);
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	for (int i = -10; i < 11; i++) {
		if (i - delta >= -10) {
			glVertex3f((GLfloat)i - delta, -8.0, -10.0);
			glVertex3f((GLfloat)i - delta, -8.0, 10.0);
		}
	}
	glEnd();
	glPopMatrix();
	delta += 0.1;
	if (delta > 1) delta = 0;
}

void refreshDisplayRun(int value) {
	robot.setRunStep();
	glutPostRedisplay();    // Post a paint request to activate display()
	if (run)
		glutTimerFunc(refreshMillis, refreshDisplayRun, 0); // subsequent timer call at milliseconds
}

// Handles the keyboard event: the left and right arrows bend the elbow, the
// up and down keys bend the shoulder.
void special(int key, int, int) {
	switch (key) {
	case GLUT_KEY_LEFT: camera.moveLeft(); break;
	case GLUT_KEY_RIGHT: camera.moveRight(); break;
	case GLUT_KEY_UP: camera.moveUp(); break;
	case GLUT_KEY_DOWN: camera.moveDown(); break;
	case GLUT_KEY_F5: robot.setRunPosture(); break;
	case GLUT_KEY_F6:
		if (!run) {
			run = true;
			robot.setRunStatus(run);
			robot.setRunPosture();
			refreshDisplayRun(0);
		}
		else {
			run = false;
			robot.setRunStatus(run);
		}
		break;
	case GLUT_KEY_F7:
		showGround = !showGround;
		break;
	}
	glutPostRedisplay();
}

// Handles the keyboard event: 
void key(unsigned char key, int, int) {
	switch (key) {
	case 'W':
	case 'w':
		robot.incShoulderOpenAngle(LEFT);
		break;
	case 'S':
	case 's':
		robot.decShoulderOpenAngle(LEFT);
		break;
	case 'A':
	case 'a':
		robot.incShoulderTwistAngle(LEFT);
		break;
	case 'D':
	case 'd':
		robot.decShoulderTwistAngle(LEFT);
		break;
	case 'E':
	case 'e':
		robot.incElbowAngle(LEFT);
		break;
	case 'C':
	case 'c':
		robot.decElbowAngle(LEFT);
		break;
	case 'Q':
	case 'q':
		if(!run)
			robot.incShoulderAngle(LEFT);
		break;
	case 'Z':
	case 'z':
		if(!run)
			robot.decShoulderAngle(LEFT);
		break;

	case 'I':
	case 'i':
		robot.incShoulderOpenAngle(RIGHT);
		break;
	case 'K':
	case 'k':
		robot.decShoulderOpenAngle(RIGHT);
		break;
	case 'J':
	case 'j':
		robot.decShoulderTwistAngle(RIGHT);
		break;
	case 'L':
	case 'l':
		robot.incShoulderTwistAngle(RIGHT);
		break;
	case 'U':
	case 'u':
		robot.incElbowAngle(RIGHT);
		break;
	case 'M':
	case 'm':
		robot.decElbowAngle(RIGHT);
		break;
	case 'O':
	case 'o':
		if (!run)
			robot.incShoulderAngle(RIGHT);
		break;
	case '>':
	case '.':
		if (!run)
			robot.decShoulderAngle(RIGHT);
		break;

	case '1':
		robot.decThighAngle(LEFT);
		break;
	case '2':
		robot.incThighAngle(LEFT);
		break;
	case '3':
		robot.decCalfAngle(LEFT);
		break;
	case '4':
		robot.incCalfAngle(LEFT);
		break;

	case '5':
		robot.decThighAngle(RIGHT);
		break;
	case '6':
		robot.incThighAngle(RIGHT);
		break;
	case '7':
		robot.decCalfAngle(RIGHT);
		break;
	case '8':
		robot.incCalfAngle(RIGHT);
		break;
	default: return;
	}
	glutPostRedisplay();
}

// Displays the robot in its current position and orientation.  The whole
// function is bracketed by glPushMatrix and glPopMatrix calls because every
// time we call it we are in an "environment" in which a gluLookAt is in
// effect.  (Note that in particular, replacing glPushMatrix with
// glLoadIdentity makes you lose the camera setting from gluLookAt).
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
		centerX, centerY, centerZ,
		0.0, 1.0, 0.0);

	robot.drawRobot();
	if (run && showGround) drawGround();
	
	if(showAxis) drawAxis();
	glutSwapBuffers();
}

// Handles the reshape event by setting the viewport so that it takes up the
// whole visible region, then sets the projection matrix to something reason-
// able that maintains proper aspect ratio.
void reshape(GLint w, GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, GLfloat(w) / GLfloat(h), 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Initializes GLUT, the display mode, and main window; registers callbacks;
// does application initialization; enters the main event loop.
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hierarchical Transforms: Running Robot");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(special);
	init();
	glutMainLoop();
}