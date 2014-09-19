/*
 * Line.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef LINE_H_
#define LINE_H_
#include "Coordinate.h"
#include <iostream>
#include <memory>

class Line {
public:
	virtual ~Line();
	Line(const std::shared_ptr<Coordinate>& coord1, const std::shared_ptr<Coordinate>& coord2);
	Line(const Line& lin);
	float lengthSquared() const;
	float length() const;
	bool isBelow(const std::shared_ptr<Coordinate>& coord) const;
	bool intersects(const Line& line);
	Coordinate getNormal();
protected:
	float getYVal(float xVal) const;
	float getSlope() const;
	float getYIntercept() const;
	float isBetween(const float& pt0, const float& bound1, const float& bound2) const;
private:
	std::shared_ptr<Coordinate> _coordinate1;
	std::shared_ptr<Coordinate> _coordinate2;
};

#endif /* LINE_H_ */
