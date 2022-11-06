#include "Robot.h"

void Robot::incShoulderAngle(int side , int deg ) {
	if (side == LEFT) {
		leftShoulderAngle += deg;
		if (leftShoulderAngle >= 90) leftShoulderAngle = 90;
	}
	else {
		rightShoulderAngle += deg;
		if (rightShoulderAngle >= 90) rightShoulderAngle = 90;
	}
}

void Robot::decShoulderAngle(int side , int deg ) {
	if (side == LEFT) {
		leftShoulderAngle -= deg;
		if (leftShoulderAngle <= -90) leftShoulderAngle = -90;
	}
	else {
		rightShoulderAngle -= deg;
		if (rightShoulderAngle <= -90) rightShoulderAngle = -90;
	}
}

void Robot::incShoulderOpenAngle(int side , int deg ) {
	if (side == LEFT) {
		leftShoulderOpenAngle += deg;
		if (leftShoulderOpenAngle >= 90) leftShoulderOpenAngle = 90;
	}
	else {
		rightShoulderOpenAngle += deg;
		if (rightShoulderOpenAngle >= 90) rightShoulderOpenAngle = 90;
	}
}

void Robot::decShoulderOpenAngle(int side , int deg ) {
	if (side == LEFT) {
		leftShoulderOpenAngle -= deg;
		if (leftShoulderOpenAngle <= -90) leftShoulderOpenAngle = -90;
	}
	else {
		rightShoulderOpenAngle -= deg;
		if (rightShoulderOpenAngle <= -90) rightShoulderOpenAngle = -90;
	}
}

void Robot::incShoulderTwistAngle(int side , int deg ) {
	if (side == LEFT) {
		leftShoulderTwistAngle += deg;
		if (leftShoulderTwistAngle >= 90) leftShoulderTwistAngle = 90;
	}
	else {
		rightShoulderTwistAngle += deg;
		if (rightShoulderTwistAngle >= 90) rightShoulderTwistAngle = 90;
	}
}
void Robot::decShoulderTwistAngle(int side , int deg ) {
	if (side == LEFT) {
		leftShoulderTwistAngle -= deg;
		if (leftShoulderTwistAngle <= 0) leftShoulderTwistAngle = 0;
	}
	else {
		rightShoulderTwistAngle -= deg;
		if (rightShoulderTwistAngle <= 0) rightShoulderTwistAngle = 0;
	}
}

void Robot::incElbowAngle(int side , int deg ) {
	if (side == LEFT) {
		leftElbowAngle += deg;
		if (leftElbowAngle >= 90) leftElbowAngle = 90;
	}
	else {
		rightElbowAngle += deg;
		if (rightElbowAngle >= 90) rightElbowAngle = 90;
	}
}

void Robot::decElbowAngle(int side , int deg ) {
	if (side == LEFT) {
		leftElbowAngle -= deg;
		if (leftElbowAngle <= 0) leftElbowAngle = 0;
	}
	else {
		rightElbowAngle -= deg;
		if (rightElbowAngle <= 0) rightElbowAngle = 0;
	}
}

void Robot::incThighAngle(int side , int deg ) {
	if (side == LEFT) {
		leftThighAngle += deg;
		if (leftThighAngle >= 90) leftThighAngle = 90;
	}
	else {
		rightThighAngle += deg;
		if (rightThighAngle >= 90) rightThighAngle = 90;
	}
}

void Robot::decThighAngle(int side , int deg ) {
	if (side == LEFT) {
		leftThighAngle -= deg;
		if (leftThighAngle <= -90) leftThighAngle = -90;
	}
	else {
		rightThighAngle -= deg;
		if (rightThighAngle <= -90) rightThighAngle = -90;
	}
}

void Robot::incCalfAngle(int side , int deg ) {
	if (side == LEFT) {
		leftCalfAngle += deg;
		if (leftCalfAngle >= 0) leftCalfAngle = 0;
	}
	else {
		rightCalfAngle += deg;
		if (rightCalfAngle >= 0) rightCalfAngle = 0;
	}
}

void Robot::decCalfAngle(int side , int deg ) {
	if (side == LEFT) {
		leftCalfAngle -= deg;
		if (leftCalfAngle <= -90) leftCalfAngle = -90;
	}
	else {
		rightCalfAngle -= deg;
		if (rightCalfAngle <= -90) rightCalfAngle = -90;
	}
}


void Robot::drawLeftArm(GLfloat centerDist) {
	glPushMatrix();

	glColor3fv(paleSilver);
	// Draw the upper arm, rotated shoulder degrees about the y-axis.  Note that
	// the thing about glutWireBox is that normally its origin is in the middle
	// of the box, but we want the "origin" of our box to be at the left end of
	// the box, so it needs to first be shifted 1 unit in the -z direction, then
	// rotated.
	glTranslatef(0.0, 0.0, -centerDist); // shift entire arm in -z direction
	glRotatef((GLfloat)leftShoulderOpenAngle, 1.0, 0.0, 0.0); // open arm w.r.t. x-axis
	glRotatef((GLfloat)leftShoulderAngle, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)leftShoulderTwistAngle, 0.0, 0.0, 1.0); // twist arm
	glTranslatef(0.0, 0.0, -1.0); // shift towards -z direction

	//wireBox(1.0, 0.4, 2.0);
	wireBox(1.2, 0.7, 2.2);

	// Now we are ready to draw the lower arm.  Since the lower arm is attached
	// to the upper arm we put the code here so that all rotations we do are
	// relative to the rotation that we already made above to orient the upper
	// arm.  So, we want to rotate elbow degrees about the y-axis.  But, like
	// before, the anchor point for the rotation is at the end of the box, so
	// we translate <0,0,-1> before rotating.  But after rotating we have to
	// position the lower arm at the end of the upper arm, so we have to
	// translate it <0,0,-1> again.
	glColor3fv(floralWhite);
	glTranslatef(0.0, 0.0, -1.0);
	glRotatef((GLfloat)-leftElbowAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, -1.0); // displace
	wireBox(0.6, 0.4, 2.0);

	glPopMatrix();
}

void Robot::drawRightArm(GLfloat centerDist) {
	glPushMatrix();

	glColor3fv(paleSilver);

	// Draw the upper arm, rotated shoulder degrees about the y-axis.  Note that
	// the thing about glutWireBox is that normally its origin is in the middle
	// of the box, but we want the "origin" of our box to be at the right end of
	// the box, so it needs to first be shifted 1 unit in the z direction, then
	// rotated.
	glTranslatef(0.0, 0.0, centerDist); // shift entire arm in z direction
	glRotatef((GLfloat)-rightShoulderOpenAngle, 1.0, 0.0, 0.0);
	glRotatef((GLfloat)-rightShoulderAngle, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)rightShoulderTwistAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, 0.0, 1.0);

	//wireBox(1.0, 0.4, 2.0);
	wireBox(1.2, 0.7, 2.2);

	// Now we are ready to draw the lower arm.  Since the lower arm is attached
	// to the upper arm we put the code here so that all rotations we do are
	// relative to the rotation that we already made above to orient the upper
	// arm.  So, we want to rotate elbow degrees about the y-axis.  But, like
	// before, the anchor point for the rotation is at the end of the box, so
	// we translate <0,0,1> before rotating.  But after rotating we have to
	// position the lower arm at the end of the upper arm, so we have to
	// translate it <0,0,1> again.
	glColor3fv(floralWhite);
	glTranslatef(0.0, 0.0, 1.0);
	glRotatef((GLfloat)rightElbowAngle, 0.0, 1.0, 0.0);
	glTranslatef(0.0, 0.0, 1.0);
	wireBox(0.6, 0.4, 2.0);

	glPopMatrix();
}

void Robot::drawTorso() {
	glPushMatrix();
	glColor3fv(blackOlive);
	glTranslatef(0.0, -2.0, 0);
	wireBox(1.0, 4., 3.0);
	glPopMatrix();
}

void Robot::drawLeftLeg() {
	glPushMatrix();

	glColor3fv(eerieBlack);

	glTranslatef(0.0, -4.0, -0.75); // shift entire arm in -z direction
	glRotatef((GLfloat)leftThighAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);

	wireBox(1.0, 2.0, 1.0);

	glColor3fv(floralWhite);
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)leftCalfAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.0, 0.5);

	glPopMatrix();
}

void Robot::drawRightLeg() {
	glPushMatrix();

	glColor3fv(eerieBlack);

	glTranslatef(0.0, -4.0, 0.75); // shift entire arm in -z direction
	glRotatef((GLfloat)rightThighAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);

	wireBox(1.0, 2.0, 1.0);

	glColor3fv(floralWhite);
	glTranslatef(0.0, -1.0, 0.0);
	glRotatef((GLfloat)rightCalfAngle, 0.0, 0.0, 1.0);
	glTranslatef(0.0, -1.0, 0.0);
	wireBox(0.5, 2.0, 0.5);

	glPopMatrix();
}

void Robot::drawHead() {
	glPushMatrix();

	glColor3f(1.0, 1.0, 1.0);

	glTranslatef(0.0, 0.6, 0); // shift head to correct position
	wireBox(1.0, 1.2, 1.0);

	glPopMatrix();
}

void Robot::drawRobot() {
	drawTorso();
	drawLeftArm(1.5 + 0.1);
	drawRightArm(1.5 + 0.1);
	drawLeftLeg();
	drawRightLeg();
	drawHead();

	if (!running) {
		printf("===\n");
		printf("leftShoulderAngle: %d, leftShoulderOpenAngle: %d, leftShoulderTwistAngle: %d, leftElbowAngle: %d\n", leftShoulderAngle, leftShoulderOpenAngle, leftShoulderTwistAngle, leftElbowAngle);
		printf("leftThighAngle: %d, leftCalfAngle: %d\n", leftThighAngle, leftCalfAngle);
		printf("rightShoulderAngle: %d, rightShoulderOpenAngle: %d, rightShoulderTwistAngle: %d, rightElbowAngle: %d\n", rightShoulderAngle, rightShoulderOpenAngle, rightShoulderTwistAngle, rightElbowAngle);
		printf("rightThighAngle: %d, rightCalfAngle: %d\n", rightThighAngle, rightCalfAngle);
	}
}

void Robot::setRunPosture() {
	leftShoulderAngle = -30;
	leftShoulderOpenAngle = -80;
	leftShoulderTwistAngle = 0;
	leftElbowAngle = 50;
	rightShoulderAngle = 30;
	rightShoulderOpenAngle = -80;
	rightShoulderTwistAngle = 5;
	rightElbowAngle = 50;

	leftThighAngle = -30;
	leftCalfAngle = -40;
	rightThighAngle = 30;
	rightCalfAngle = -40;
}

void Robot::setRunStep() {
	if (rightStateForward) {
		leftShoulderAngle += 5;
		leftThighAngle = leftShoulderAngle;
		rightShoulderAngle -= 5;
		rightThighAngle = rightShoulderAngle;
		if (leftShoulderAngle >= 45) {
			rightStateForward = !rightStateForward;
		}
	}
	else {
		leftShoulderAngle -= 5;
		leftThighAngle = leftShoulderAngle;
		rightShoulderAngle += 5;
		rightThighAngle = rightShoulderAngle;
		if (rightShoulderAngle >= 45) rightStateForward = !rightStateForward;
	}
}

void Robot::setRunStatus(bool running) {
	this->running = running;
	if (running) {
		printf("Robot is now RUNNING!\nFeel free to rotate its limbs\n");
	}
	else {
		printf("Stop running.\n");
	}
}