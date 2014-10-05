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
/*! 
*	\param coord0 shared pointer to a coordinate representing the first corner of the triangle.
*	\param coord1 shared pointer to a coordinate representing the second corner of the triangle.
*	\param coord2 shared pointer to a coordinate representing the third corner of the triangle.
*/
	Triangle(const shared_ptr<Coordinate>& coord0,
			 const shared_ptr<Coordinate>& coord1,
			 const shared_ptr<Coordinate>& coord2);

/*!
*	Default Virtual Destructor
*/
	virtual ~Triangle();

/*! 
*	\param coord A shared pointer to a coordinate either inside or outside of the triangle.
*	\return Either true or false, depending on whether the coordinate passed to the function is inside or outside the triangle.
*/
	bool hasInside(const shared_ptr<Coordinate>& coord) const;


/*! 
*	\param coords A vector of shared pointers to coordinates, either inside or outside of the triangle.
*	\return returns true if at least one of the coordinates from coords are inside the triangle.
*	
*	Makes use of bool Triangle::hasInside(const shared_ptr< Coordinate > &coord) const
*/
	bool hasInside(const vector<shared_ptr<Coordinate>>& coords) const;

/*! 
*	\param triangles A vector of Triangles.
*	\return returns true if at least one of the coordinates from one of the vector of triangles are inside the triangle.
*	
*	Makes use of bool hasInside(const vector<shared_ptr<Coordinate>>& coords) const
*/
	bool hasInside(const vector<Triangle> triangles) const;

/*! 
*	\param coords A vector of shared pointers to coordinates, either inside or outside of the triangle.
*	\return returns a vector of pointers to all the coordinates from coords that are inside the triangle.
*	
*	Makes use of bool hasInside(const shared_ptr<Coordinate>& coord) const
*/
	vector<shared_ptr<Coordinate>> coordsInside(const vector<shared_ptr<Coordinate>>& coords) const;

/*! 
*	\param triangles A vector of Triangles.
*	\return returns a vector of shared pointers to coordinates that make up triangles that are inside the triangle.
*	
*	Makes use of vector<shared_ptr<Coordinate>> coordsInside(const vector<shared_ptr<Coordinate>>& coords) const
*/
	vector<shared_ptr<Coordinate>> coordsInside(const vector<Triangle> triangles) const;
	shared_ptr<Coordinate> getCoordinate(const int coord) const;
	void rotate(const float angle, const Coordinate& center);
	void move(const Coordinate change);
	Line getLine(const int LineNo);
//protected:
	vector<shared_ptr<Coordinate>> _coordinates;
};

#endif /* TRIANGLE_H_ */
