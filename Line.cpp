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
