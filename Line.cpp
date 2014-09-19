/*
 * Line.cpp
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#include "Line.h"

Line::~Line() {
	// TODO Auto-generated destructor stub
}

Line::Line(const std::shared_ptr<Coordinate>& coord1, const std::shared_ptr<Coordinate>& coord2) :
	_coordinate1(coord1),
	_coordinate2(coord2)
{ }

Line::Line(const Line& lin) : //Note this is iportant for th report, copy constr copies pointers to coords, resulting in less data moving around.
	_coordinate1(lin._coordinate1),
	_coordinate2(lin._coordinate2)
{ }


float Line::lengthSquared() const
{
	Coordinate tempCoord = (*_coordinate1) - (*_coordinate2);
	float len = tempCoord.magSquared();
	return len;
}

float Line::length() const
{
	return sqrt(lengthSquared());
}

float Line::getSlope() const
{
	float x1 = _coordinate1->x();
	float y1 = _coordinate1->y();
	float x2 = _coordinate2->x();
	float y2 = _coordinate2->y();

	return ((y1-y2)/(x1-x2));
}

float Line::getYIntercept() const
{
	float x1 = _coordinate1->x();
	float y1 = _coordinate1->y();

	float m = getSlope();
	float c = y1 - (m*x1);

	return c;
}

float Line::getYVal(float xVal) const
{
	float m = getSlope();
	float c = getYIntercept();

	float y1 = m*xVal + c;

	return y1;
}

bool Line::isBelow(const std::shared_ptr<Coordinate>& coord) const
{
	float y0 = coord->y();
	float x0 = coord->x();
	float y1 = getYVal(x0);

	if (y0 < y1)
		return true;
	else
		return false;
}

float Line::isBetween(const float& pt0, const float& bound1, const float& bound2) const
{
	if (pt0 <= bound2 && pt0 >= bound1)
		return true;
	else if ((pt0 >= bound2 && pt0 <= bound1))
		return true;
	return false;
}

bool Line::intersects(const Line& line)
{
	float m0 = getSlope();
	float c0 = getYIntercept();

	float m1 = line.getSlope();
	float c1 = line.getYIntercept();

	float x2 = (c0-c1)/(m1-m0);

	if (  isBetween(x2, _coordinate1->x(), _coordinate2->x()) &&
		 isBetween(x2, line._coordinate1->x(), line._coordinate2->x()) )
		return true;

	return false;
}

Coordinate Line::getNormal()
{
	//rotate by pi/2
	//subtr endpoints
	//divide my mag
	Coordinate normal{};
	_coordinate2->rotate(PI/2, *(_coordinate1));
	if (_coordinate1->magSquared() > _coordinate2->magSquared())
		normal = *_coordinate1 - *_coordinate2;
	else if (_coordinate1->magSquared() < _coordinate2->magSquared())
		normal = *_coordinate2 - *_coordinate1;

	normal = normal/normal.magnitude();
	return normal;
}
