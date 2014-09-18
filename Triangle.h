/*
 * Triangle.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Coordinate.h"
#include "Line.h"
#include <vector>

using namespace std;
//Exception Classes
class argument_exceeds_number_of_coordinates{};
class provide_positive_argument{};

class Triangle {
public:
	Triangle(const shared_ptr<Coordinate>& coord0,
			 const shared_ptr<Coordinate>& coord1,
			 const shared_ptr<Coordinate>& coord2);
	virtual ~Triangle();
	bool isInside(const shared_ptr<Coordinate>& coord) const;
	int coordsInside(const vector<shared_ptr<Coordinate>>& coords) const;
	int coordsInside(const vector<shared_ptr<Triangle>> triangles) const; //TODO
	shared_ptr<Coordinate> getCoordinate(const int coord) const;
	void rotate(const float angle, const Coordinate& center);
	void move(const Coordinate change);
protected:
	vector<shared_ptr<Coordinate>> _coordinates;
};

#endif /* TRIANGLE_H_ */
