/*
 * GameFundamentals.h
 *
 *  Created on: 07 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMEFUNDAMENTALS_H_
#define GAMEFUNDAMENTALS_H_


#include <cmath>
#include <vector>
#include <exception>
#include <memory>
#include <iostream>

#define PI 3.14159265


//Exception Classes
class impulse_cannot_have_zero_time{};
class polygon_cannot_contain_more_coordinates{};
class Index_exceeds_max_coordinates{};
class Index_exceeds_Polygon_coordinates{};
class Triangle_only_has_3_lines_0_to_2{};

enum Property
{
	X,
	Y,
	ANGLE,
	MAGNITUDE
};

class Coordinate
{
public:
	Coordinate(const float& x, const float& y) : _x(x), _y(y) {};
	Coordinate() : _x(0), _y(0) {};
	Coordinate(const Coordinate& pos) : _x(pos._x), _y(pos._y) {};
	virtual ~Coordinate() {};
	virtual bool doCompare(const Coordinate& rhs) const;
	bool operator==(const Coordinate& rhs) const;
	bool operator!=(const Coordinate& rhs) const;
	Coordinate operator-(const Coordinate& rhs) const;
	float dist(const Coordinate& rhs) const;
	float getX() const;
	float getY() const;
protected:
	void setX(const float& x);
	void setY(const float& y);
	void setMass(const float& m);
private:
	float _x;
	float _y;
};

class Vertex: public Coordinate
{
public:
	Vertex(const Coordinate& coord, float mass) : Coordinate(coord), _mass(mass) {};
	Vertex(const Coordinate& coord) : Coordinate(coord), _mass(0){};
	Vertex(const Vertex& vert) : Coordinate(vert), _mass(vert.getMass()) {};
	Vertex(const float& x, const float& y, const float& mass) : Coordinate(x,y), _mass(mass) {};
	Vertex(const float& x, const float& y) : Coordinate(x,y) {}; // sets mass to 0
	Vertex() : Coordinate(), _mass(0.0f) {};
	virtual ~Vertex() {};
	virtual bool doCompare(const Vertex& rhs) const;
	bool operator==(const Vertex& rhs) const;
	bool operator!=(const Vertex& rhs) const;
	void operator+=(const Vertex& rhs);
	float getMass() const;
protected:
	void setMass(const float& m);
private:
	float _mass = 0.0f;
};

class VectorQuantity
{
public:
	VectorQuantity();
	VectorQuantity(const Coordinate& pos);
	VectorQuantity(const VectorQuantity& vec);
	VectorQuantity(const float& angle, const float& magnitude);

	float getMagnitude()const; // TODO
	float getAngle() const; // TODO

	bool doCompare(const VectorQuantity& rhs) const;
	bool operator==(const VectorQuantity& rhs) const;
	bool operator!=(const VectorQuantity& rhs) const;
	VectorQuantity operator-(const VectorQuantity& rhs) const;
	VectorQuantity operator+(const VectorQuantity& rhs) const;
	float operator*(const VectorQuantity& rhs) const; //dot product, cross product is meaningless in 2D
	float getX() const;
	float getY() const;
protected:
	Coordinate _coordinate;
};


class VectorImpulse : public VectorQuantity
{
public:
	VectorImpulse();
	VectorImpulse(const float& time);
	VectorImpulse(const Coordinate& pos, const float& time);
	VectorImpulse(const VectorQuantity& vec, const float& time);
	VectorImpulse(const float& angle, const float& magnitude, const float& time);
	float getTime() const; // TODO
protected:
	float _time; //time over which the force is applied.
};


class Polygon
{
public:
	Polygon();
	virtual ~Polygon();
	void addCoordinate(std::shared_ptr<Coordinate> coordinate);
	std::shared_ptr<Coordinate> getCoordinateAt(const unsigned int coordPos) const;
	void sortCoordinates(const Property sortPriority); // TODO sorts coordinate ptrs in vector according to a property.
	float distanceBetween(unsigned int c1, unsigned int c2); // returns distance between coordinates at given positions.
	virtual bool doCompare(const Polygon& rhs) const;
	bool operator==(const Polygon& rhs) const;
	bool operator!=(const Polygon& rhs) const;
	unsigned int countCoordinates() const;
protected:
	void setMaxCoordinates(const unsigned int& max); // 0 means no limit
	unsigned int getMaxCoordinates();
	std::vector<std::shared_ptr<Coordinate>> _coordinates; // TODO Should this be a deque? or a list of some sort rather? look this up!
private:
	unsigned int _maxCoordinates = 0; //0 means no limit
};

class Line : public Polygon
{
public:
	Line();
	Line(const std::shared_ptr<Coordinate> c1, const std::shared_ptr<Coordinate> c2);
	bool operator==(const Line& rhs) const;
	bool operator!=(const Line& rhs) const;
	float length();
	float getSlope();
	float getYIntercept();
	float getYval(float xVal);
	bool isOnLine(const std::shared_ptr<Coordinate>& c1, const float& error);
	bool isBelowLine(const std::shared_ptr<Coordinate>& c1);
};

class Triangle : public Polygon
{
public:
	Triangle(	const std::shared_ptr<Coordinate> c0,
				const std::shared_ptr<Coordinate> c1,
				const std::shared_ptr<Coordinate> c2);
	bool operator==(const Triangle& rhs) const;
	bool operator!=(const Triangle& rhs) const;
	std::shared_ptr<Line> getLine(unsigned int);
	std::shared_ptr<Coordinate> getOpposingCoord(unsigned int);
	bool isInside(const std::shared_ptr<Coordinate>& c1); //returns true if coord is inside triangle, use isbelowline after making temp line object
	unsigned int numberInside(std::vector<std::shared_ptr<Coordinate>> coords); // TODO returns how many of coords in vector is inside the triangle
	bool isOnEdge(const std::shared_ptr<Coordinate>& c1, const float& error); // uses isOnLine() after making a temporary line object
};


#endif /* GAMEFUNDAMENTALS_H_ */
