/*
 * Tank.cpp
 *
 */

#include "Tank.h"

Tank::Tank() :
	GameObject(TANKMASS)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0.0001}};
	shared_ptr<Coordinate> c1{new Coordinate{50.0001,0}};
	shared_ptr<Coordinate> c2{new Coordinate{25.00006,50.0001}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	//tweak these values
	addTriangle(t0);
	setDragCoeff(1);
	_enginePowerFwd = 200;
	_enginePowerRev = -5;
	_turningPower = 0.05;
}

Tank::~Tank() {
	// TODO Auto-generated destructor stub
}

void Tank::driveForward()
{
	applyForceLinear(_forward * _enginePowerFwd);
}

void Tank::driveReverse()
{
	applyForceLinear(_forward * _enginePowerRev);
}

void Tank::turnRight()
{
	applyForceAngular(-_turningPower);
}

void Tank::turnLeft()
{
	applyForceAngular(_turningPower);
}

void Tank::react(const Coordinate& rhs)
{
	applyImpulseLinear(rhs);
}

