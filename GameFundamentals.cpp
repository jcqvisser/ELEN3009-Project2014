/*
 * GameFundamentals.cpp
 *
 *  Created on: 07 Sep 2014
 *      Author: Jacques
 */

#include "GameFundamentals.h"



//------------------------------------------------------------------------------
//				Coordinate
//------------------------------------------------------------------------------
bool Coordinate::doCompare(const Coordinate& rhs) const
{
	if (_x == rhs._x && _y == rhs._y)
		return true;
	else
		return false;
}

bool Coordinate::operator==(const Coordinate& rhs) const
{	return doCompare(rhs);}

bool Coordinate::operator!=(const Coordinate& rhs) const
{	return !doCompare(rhs);}

Coordinate Coordinate::operator-(const Coordinate& rhs) const
{
	float x = getX() - rhs.getX();
	float y = getY() - rhs.getY();

	return Coordinate{x,y};
}

Coordinate Coordinate::operator+(const Coordinate& rhs) const
{
	float x = getX() - rhs.getX();
	float y = getY() - rhs.getY();

	return Coordinate{x,y};
}

float Coordinate::dist(const Coordinate& rhs) const
{
	float x1 = getX();
	float x2 = rhs.getX();
	float y1 = getY();
	float y2 = rhs.getY();

	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

float Coordinate::getX() const
{ 	return _x; }

float Coordinate::getY() const
{ 	return _y; }

void Coordinate::setX(const float& x)
{	_x = x;}

void Coordinate::setY(const float& y)
{	_y = y;}



//------------------------------------------------------------------------------
//				Vertex
//------------------------------------------------------------------------------
float Vertex::getMass() const { return _mass; }

bool Vertex::doCompare(const Vertex& rhs) const
{
	if (	Coordinate::doCompare(rhs) &&
			getMass() == rhs.getMass())
		return true;
	else
		return false;
}

void Vertex::setMass(const float& m)
{	_mass = m;}

bool Vertex::operator==(const Vertex& rhs) const
{ 	return doCompare(rhs);}

bool Vertex::operator!=(const Vertex& rhs) const
{	return !doCompare(rhs);}

void Vertex::operator+=(const Vertex& rhs)
{
	float totalMass = getMass() + rhs.getMass();
	float rhsMass = rhs.getMass();
	float lhsMass = getMass();

	if (rhsMass == 0.0f && lhsMass == 0.0f) // Prevent division by 0.
	{
		rhsMass = 1;
		lhsMass = 1;
	}
	if (totalMass == 0.0f)
		totalMass = 1;

	setX((getX()*lhsMass + rhs.getX()*rhsMass)/totalMass);
	setY((getY()*lhsMass + rhs.getY()*rhsMass)/totalMass);
	setMass(lhsMass + rhsMass);
}

//------------------------------------------------------------------------------
//				VectorQuantity
//------------------------------------------------------------------------------

VectorQuantity::VectorQuantity() :
	_coordinate(0.0, 0.0) {};
VectorQuantity::VectorQuantity(const Coordinate& pos) :
	_coordinate(pos) {};
VectorQuantity::VectorQuantity(const VectorQuantity& vec) :
	_coordinate(vec._coordinate) {};
VectorQuantity::VectorQuantity(const float& angle, const float& magnitude) :
	_coordinate((magnitude * cos(angle)), (magnitude * sin(angle))) {};


bool VectorQuantity::doCompare(const VectorQuantity& rhs) const
{	return _coordinate == rhs._coordinate;}

bool VectorQuantity::operator ==(const VectorQuantity& rhs) const
{	return doCompare(rhs);}

bool VectorQuantity::operator !=(const VectorQuantity& rhs) const
{	return !doCompare(rhs);}

VectorQuantity VectorQuantity::operator-(const VectorQuantity& rhs) const
{	return VectorQuantity{_coordinate - rhs._coordinate};}

VectorQuantity VectorQuantity::operator+(const VectorQuantity& rhs) const
{
	float x = _coordinate.getX() + rhs._coordinate.getX();
	float y = _coordinate.getY() + rhs._coordinate.getY();

	return VectorQuantity{Coordinate{x,y}};
}

float VectorQuantity::operator*(const VectorQuantity& rhs) const
{
	float x = _coordinate.getX() * rhs._coordinate.getX();
	float y = _coordinate.getY() * rhs._coordinate.getY();

	return x + y;
}

float VectorQuantity::getX() const
{	return _coordinate.getX();}

float VectorQuantity::getY() const
{	return _coordinate.getY();}

float VectorQuantity::getMagnitude() const
{
	return sqrt(pow(_coordinate.getX(),2) + pow(_coordinate.getY(),2));
}

float VectorQuantity::getAngle() const
{
	return atan2(_coordinate.getY(), _coordinate.getX()) + 2*PI;
}

Coordinate VectorQuantity::getCoordinate() const
{
	return _coordinate;
}




//------------------------------------------------------------------------------
//				VectorImpulse
//------------------------------------------------------------------------------
VectorImpulse::VectorImpulse() :
	_time(0.0)
{throw impulse_cannot_have_zero_time{};};

VectorImpulse::VectorImpulse(const float& time) :
	_time(time) {};

VectorImpulse::VectorImpulse(	const Coordinate& pos,
								const float& time) :
	VectorQuantity(pos), _time(time) {};

VectorImpulse::VectorImpulse(	const VectorQuantity& vec, const float& time) :
	VectorQuantity(vec), _time(time) {};

VectorImpulse::VectorImpulse(	const float& angle,
								const float& magnitude,
								const float& time) :
	VectorQuantity(angle, magnitude), _time(time) {};

//------------------------------------------------------------------------------
//				Polygon
//------------------------------------------------------------------------------
Polygon::Polygon() {};
Polygon::~Polygon() {};
void Polygon::addCoordinate(std::shared_ptr<Coordinate> coordinate)
{
	if (_maxCoordinates == 0 || _coordinates.size() < _maxCoordinates)
	{
		_coordinates.push_back(coordinate);
	}
	else
	{
		throw polygon_cannot_contain_more_coordinates{};
	}
}

void Polygon::setMaxCoordinates(const unsigned int& max)
{ _maxCoordinates = max; };

std::shared_ptr<Coordinate> Polygon::getCoordinateAt(const unsigned int coordPos) const
{
	if (_maxCoordinates != 0 && coordPos >= _maxCoordinates)
		throw Index_exceeds_max_coordinates{};
	if (coordPos >= _coordinates.size())
		throw Index_exceeds_Polygon_coordinates{};
	return _coordinates[coordPos];
}

unsigned int Polygon::getMaxCoordinates() { return _maxCoordinates; }

float Polygon::distanceBetween(unsigned int c1, unsigned int c2)
{	return _coordinates[c1]->dist(*_coordinates[c2]);}

unsigned int Polygon::countCoordinates() const
{
	return _coordinates.size();
}

bool Polygon::doCompare(const Polygon& rhs) const
{
	if (rhs.countCoordinates() != countCoordinates())
		return false;

	for(unsigned int n = 0; n != countCoordinates(); n++)
	{
		if (*getCoordinateAt(n) != *rhs.getCoordinateAt(n))
			return false;
	}
	return true;
}

bool Polygon::operator==(const Polygon& rhs) const
{	return doCompare(rhs);}

bool Polygon::operator!=(const Polygon& rhs) const
{	return !doCompare(rhs);}

//------------------------------------------------------------------------------
//				Line
//------------------------------------------------------------------------------
Line::Line(const std::shared_ptr<Coordinate> c1, const std::shared_ptr<Coordinate> c2)
{
	setMaxCoordinates(2);
	addCoordinate(c1);
	addCoordinate(c2);
}

bool Line::operator==(const Line& rhs) const
{	return Polygon::doCompare(rhs);}

bool Line::operator!=(const Line& rhs) const
{	return !Polygon::doCompare(rhs);}


float Line::length()
{
	return distanceBetween(0,1);
}

float Line::getSlope()
{
	float x1 = _coordinates[0]->getX();
	float x2 = _coordinates[1]->getX();
	float y1 = _coordinates[0]->getY();
	float y2 = _coordinates[1]->getY();

	float m = (y1 - y2)/(x1 - x2);

	return m;
}

float Line::getYIntercept()
{
	float x1 = _coordinates[0]->getX();
	float y1 = _coordinates[0]->getY();

	float m = getSlope();
	float c = y1 - (m*x1);

	return c;
}

bool Line::isOnLine(const std::shared_ptr<Coordinate>& c1, const float& error)
{
	float y0 = c1->getY();
	float x0 = c1->getX();


	float x3 = _coordinates[0]->getX();
	float x4 = _coordinates[1]->getX();

	float largestX = std::max(x3, x4);
	float smallestX = std::min(x3, x4);

	if ( (x3 < smallestX - error) || (x3 > largestX + error) )
		return false;

	float y1 = getYval(x0);
	if (std::abs(y1 - y0) > error)
		return false;

	return true;
}

float Line::getYval(float xVal)
{
	float m = getSlope();
	float c = getYIntercept();

	float y1 = m*xVal + c;

	return y1;
}

bool Line::isBelowLine(const std::shared_ptr<Coordinate>& c1)
{
	float y0 = c1->getY();
	float y1 = getYval(c1->getX());

	if (y0 < y1)
		return true;
	else
		return false;
}

//------------------------------------------------------------------------------
//				Triangle
//------------------------------------------------------------------------------
Triangle::Triangle(const std::shared_ptr<Coordinate> c0, const std::shared_ptr<Coordinate> c1, const std::shared_ptr<Coordinate> c2)
{
	setMaxCoordinates(3);
	addCoordinate(c0);
	addCoordinate(c1);
	addCoordinate(c2);
}

bool Triangle::operator==(const Triangle& rhs) const
{	return Polygon::doCompare(rhs);}

bool Triangle::operator!=(const Triangle& rhs) const
{	return !Polygon::doCompare(rhs);}

std::shared_ptr<Line> Triangle::getLine(unsigned int ln)
{
	unsigned int c0 = 0;
	unsigned int c1 = 0;

	switch (ln) {
	case 0 :
		c0 = 0;
		c1 = 1;
		break;
	case 1 :
		c0 = 0;
		c1 = 2;
		break;
	case 2 :
		c0 = 1;
		c1 = 2;
		break;
	default :
		throw Triangle_only_has_3_lines_0_to_2{};
	}

	std::shared_ptr<Line> theLine{new Line{_coordinates[c0], _coordinates[c1]}};
	return theLine;

}

std::shared_ptr<Coordinate> Triangle::getOpposingCoord(unsigned int ln)
{ 	return _coordinates[2-ln];}

bool Triangle::isOnEdge(const std::shared_ptr<Coordinate>& c1, const float& error)
{
	for (unsigned int n = 0; n < 3; n++)
	{
		auto theLine = getLine(n);
		if (theLine->isOnLine(c1, error))
			return true;
	}
	return false;
}

bool Triangle::isInside(const std::shared_ptr<Coordinate>& c1)
{
	//if the coordinate is on the same side of the line as the coordinate in the
	//triangle opposing the line, for all three lines, then it is inside the triangle.
	int k = 0;

	for(unsigned int n = 0; n < 3; n++)
	{
		auto theLine = getLine(n);
		if (theLine->isBelowLine(c1) == theLine->isBelowLine(getOpposingCoord(n)))
			k++;
	}

	if (k == 3)
		return true;

	return false;
}
