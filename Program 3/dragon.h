// Jasenko.Cordalija, CS342, Program 3
// Dragon Class

#ifndef DRAGON_H
#define DRAGON_H

#include "Turtle.h"
#include <iostream>
#include <math.h>
using namespace std;

//from turtle
class Dragon : public Turtle {

public:
// coordinates for dragon, x y and angle
	Dragon(float initX = 0.0, float initY = 0.0, float initAngle = 0.0);
	void leftCurve(int l, float d); // leftCurve and below is the rightCurve that will be used
	void rightCurve(int l, float d);

};
#endif
