/*
 * MapBorder.cpp
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */

#include "MapBorder.h"

MapBorder::MapBorder(const Coordinate& leftBottom, const Coordinate& rightTop) :
	GameObject(1)
{
	float xlb = leftBottom.x();
	float ylb = leftBottom.y();
	float xrt = rightTop.x();
	float yrt = rightTop.x();

	shared_ptr<Coordinate> c0{new Coordinate{xlb, ylb}};
	shared_ptr<Coordinate> c1{new Coordinate{xlb, yrt}};
	shared_ptr<Coordinate> c2{new Coordinate{xrt, yrt}};
	shared_ptr<Triangle> t0{new Triangle{c0,c1,c2}};

	shared_ptr<Coordinate> c3{new Coordinate{xlb, ylb}};
	shared_ptr<Coordinate> c4{new Coordinate{xrt, ylb}};
	shared_ptr<Coordinate> c5{new Coordinate{xrt, yrt}};
	shared_ptr<Triangle> t1{new Triangle{c3,c4,c5}};

	addTriangle(t0);
	addTriangle(t1);
}

MapBorder::~MapBorder() {
	// TODO Auto-generated destructor stub
}

