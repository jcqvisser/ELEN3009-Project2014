/*
 * Rocket.cpp
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#include "Rocket.h"

Rocket::Rocket() :
	GameObject(ROCKETMASS)
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
	_rocketPower = 20;

}

Rocket::~Rocket() {
	// TODO Auto-generated destructor stub
}

void Rocket::clearForce()
{
	_forceLinear = Coordinate{0,0};
	_forceAngular = 0;
	_forceLinear += _forward * _rocketPower;
}
