/*
 * Boundary.cpp
 *
 *  Created on: 28 Sep 2014
 *      Author: Jacques
 */

#include "Boundary.h"

Boundary::Boundary(const int hres, const int vres) :
	GameObject(10)
{
	//top
	shared_ptr<Coordinate> c0{new Coordinate{0.01, 0.01}};
	shared_ptr<Coordinate> c1{new Coordinate{hres,0}};
	shared_ptr<Coordinate> c2{new Coordinate{hres/2,-100}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	//bottom
	shared_ptr<Coordinate> c3{new Coordinate{0.01, hres-400}};
	shared_ptr<Coordinate> c4{new Coordinate{vres,hres+0.01-400}};
	shared_ptr<Coordinate> c5{new Coordinate{vres,hres+10-400}};
	shared_ptr<Triangle> t1{new Triangle{c3,c4,c5}};

	addTriangle(t0);
	addTriangle(t1);
}

Boundary::~Boundary() {
	// TODO Auto-generated destructor stub
}

