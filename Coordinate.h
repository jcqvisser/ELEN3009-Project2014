/*
 * Coordinate.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <cmath>
#define PI 3.1415926536
#define INF 2000

class Coordinate
{
public:
	~Coordinate(){};
	Coordinate();
	Coordinate(float newX, float newY);
	Coordinate(const Coordinate& pos);

	float angle() const;
	float magnitude() const;
	float magSquared() const;
	float x() const;
	float y() const;

	Coordinate operator+(const Coordinate& coord) const;
	Coordinate operator-(const Coordinate& coord) const;
	float operator*(const Coordinate& coord) const; //dot product
	void operator+=(const Coordinate& coord);
	void operator-=(const Coordinate& coord);
	bool operator==(const Coordinate& coord) const;
	bool operator>(const Coordinate& coord) const;
	bool operator<(const Coordinate& coord) const;

	Coordinate operator*(const float& rhs) const;
	Coordinate operator/(const float& rhs) const;
	bool operator>(const float& rhs) const;
	bool operator<(const float& rhs) const;
	bool operator==(const float& rhs) const;

	void rotate(const float angle, const Coordinate& center);
private:
	float _x;
	float _y;
	void setX(float x);
	void setY(float y);
};

#endif /* COORDINATE_H_ */
