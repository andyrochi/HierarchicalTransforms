#pragma once
#include "Utils.h"

class Robot {
public:
	Robot()
		: leftShoulderAngle(0), leftShoulderOpenAngle(0), leftShoulderTwistAngle(0), leftElbowAngle(0)
		, rightShoulderAngle(0), rightShoulderOpenAngle(0), rightShoulderTwistAngle(0), rightElbowAngle(0)
		, leftThighAngle(0), leftCalfAngle(0)
		, rightThighAngle(0), rightCalfAngle(0), rightStateForward(true) {}

	void incShoulderAngle(int side = LEFT, int deg = 5);
	void decShoulderAngle(int side = LEFT, int deg = 5);
	
	void incShoulderOpenAngle(int side = LEFT, int deg = 5);
	void decShoulderOpenAngle(int side = LEFT, int deg = 5);

	void incShoulderTwistAngle(int side = LEFT, int deg = 5);
	void decShoulderTwistAngle(int side = LEFT, int deg = 5);

	void incElbowAngle(int side = LEFT, int deg = 5);
	void decElbowAngle(int side = LEFT, int deg = 5);

	void incThighAngle(int side = LEFT, int deg = 5);
	void decThighAngle(int side = LEFT, int deg = 5);

	void incCalfAngle(int side = LEFT, int deg = 5);
	void decCalfAngle(int side = LEFT, int deg = 5);
	void drawRobot();

	void setRunPosture();
	void setRunStep();
	void setRunStatus(bool running);

private:

	void drawLeftArm(GLfloat centerDist = 1.0);
	void drawRightArm(GLfloat centerDist = 1.0);
	void drawTorso();
	void drawLeftLeg();
	void drawRightLeg();
	void drawHead();

	int leftShoulderAngle, leftShoulderOpenAngle, leftShoulderTwistAngle, leftElbowAngle;
	int rightShoulderAngle, rightShoulderOpenAngle, rightShoulderTwistAngle, rightElbowAngle;

	int leftThighAngle, leftCalfAngle,
		rightThighAngle, rightCalfAngle;

	bool rightStateForward;
	bool running;

};