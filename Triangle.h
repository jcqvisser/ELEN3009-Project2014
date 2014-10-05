/*
 * Triangle.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "Line.h"
#include <vector>

using namespace std;
//Exception Classes
class argument_exceeds_number_of_coordinates{};
class provide_positive_argument{};

/*! \class Triangle
*	\brief The triangle class represents a triangle in two-dimensional space. It is defined by a vector of three coordinates.
*	
*	The class is mainly used to determine whether a coordinate is within the defined triangular area.
*/
class Triangle {
public:
/*! Constructor
*	\param coord0, coord1 and coord2 define the three corners of the triangle.
*
*/
	Triangle(const shared_ptr<Coordinate>& coord0,
			 const shared_ptr<Coordinate>& coord1,
			 const shared_ptr<Coordinate>& coord2);
/*!
*	Default Virtual Destructor
*/
	virtual ~Triangle();
	bool hasInside(const shared_ptr<Coordinate>& coord) const;
	bool hasInside(const vector<shared_ptr<Coordinate>>& coords) const;
	bool hasInside(const vector<Triangle> triangles) const;
	vector<shared_ptr<Coordinate>> coordsInside(const vector<shared_ptr<Coordinate>>& coords) const;
	vector<shared_ptr<Coordinate>> coordsInside(const vector<Triangle> triangles) const;
	shared_ptr<Coordinate> getCoordinate(const int coord) const;
	void rotate(const float angle, const Coordinate& center);
	void move(const Coordinate change);
	Line getLine(const int LineNo);
//protected:
	vector<shared_ptr<Coordinate>> _coordinates;
};

#endif /* TRIANGLE_H_ */
