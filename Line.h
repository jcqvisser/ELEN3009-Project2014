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
	float lengthSquared() const;
	float length() const;
	bool isBelow(const std::shared_ptr<Coordinate>& coord) const;
protected:
	float getYVal(float xVal) const;
	float getSlope() const;
	float getYIntercept() const;
private:
	std::shared_ptr<Coordinate> _coordinate1;
	std::shared_ptr<Coordinate> _coordinate2;
};

#endif /* LINE_H_ */
