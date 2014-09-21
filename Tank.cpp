/*
 * Tank.cpp
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#include "Tank.h"

Tank::Tank() :
	GameObject(TANKMASS)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,0}};
	shared_ptr<Coordinate> c1{new Coordinate{0,50}};
	shared_ptr<Coordinate> c2{new Coordinate{25,25}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	//tweak these values
	addTriangle(t0);
	unglue();
	setDragCoeffLinear(0.5);
	setDragCoeffAngular(0.5);
	_enginePowerFwd = 10;
	_enginePowerRev = 5;
	_turningPower = 2;
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

