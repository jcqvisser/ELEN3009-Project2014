/*
 * Concrete.cpp
 *
 *  Created on: 04 Oct 2014
 *      Author: Jacques
 */

#include "Concrete.h"

Concrete::Concrete() :
	GameObject(10)
{
	shared_ptr<Coordinate> c0{new Coordinate{0,1}};
	shared_ptr<Coordinate> c1{new Coordinate{100,0}};
	shared_ptr<Coordinate> c2{new Coordinate{101,50}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	shared_ptr<Coordinate> c3{new Coordinate{0,1}};
	shared_ptr<Coordinate> c4{new Coordinate{100,0}};
	shared_ptr<Coordinate> c5{new Coordinate{101,50}};
	shared_ptr<Triangle> t1{new Triangle{c3,c4,c5}};

	addTriangle(t0);
	addTriangle(t1);

	setDragCoeff(10);

	_health = 300;

	glue();

}

Concrete::~Concrete() {
	// TODO Auto-generated destructor stub
}

