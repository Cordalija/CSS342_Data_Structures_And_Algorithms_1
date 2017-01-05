//Jasenko.Cordalija, CS342, Program3

#include "dragon.h"

Dragon::Dragon(float initX, float initY, float initAngle)
	: Turtle(initX, initY, initAngle) {
}

//-------------Right Curve--------------------
// draws level - 1 Right Curve with distance d

void Dragon::rightCurve(int level, float d) {

	if (level > 0) {	// if level is bigger than 0

		turn(-90);
		leftCurve(level - 1, d); //leftCurve after turn
		turn(-90);
		rightCurve(level - 1, d); //rightCurve after turn

	}
	else
		draw(d); // else if level is 0 just draw
}

//------------Left Curve-----------------------
// draws level - 1 Left Curve with distance d

void Dragon::leftCurve(int level, float d) {

	if (level > 0) { // if level is bigger than 0

		leftCurve(level - 1, d); // start with leftCurve then turn
		turn(90);
		rightCurve(level - 1, d); // rightCurve after turn then another turn
		turn(90);
	}
	else
		draw(d); // else if level is 0 just draw
}
