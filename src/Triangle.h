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
*	Makes use of  hasInside(const shared_ptr< Coordinate > &coord) const
*/
	bool hasInside(const vector<shared_ptr<Coordinate>>& coords) const;

/*! 
*	\param triangles A vector of Triangles.
*	\return returns true if at least one of the coordinates from one of the vector of triangles are inside the triangle.
*	
*	Makes use of  hasInside(const vector<shared_ptr<Coordinate>>& coords) const
*/
	bool hasInside(const vector<Triangle> triangles) const;

/*! 
*	\param coords A vector of shared pointers to coordinates, either inside or outside of the triangle.
*	\return returns a vector of pointers to all the coordinates from coords that are inside the triangle.
*	
*	Makes use of  hasInside(const shared_ptr<Coordinate>& coord) const
*/
	vector<shared_ptr<Coordinate>> coordsInside(const vector<shared_ptr<Coordinate>>& coords) const;

/*! 
*	\param triangles A vector of Triangles.
*	\return returns a vector of shared pointers to coordinates that make up triangles that are inside the triangle.
*	
*	Makes use of coordsInside(const vector<shared_ptr<Coordinate>>& coords) const
*/
	vector<shared_ptr<Coordinate>> coordsInside(const vector<Triangle> triangles) const;

/*!
*	\param coord an integer representing one of the three coordinates of the triangle.
*	\return returns a shared pointer to the selected coordinate.
*   \throws argument_exceeds_number_of_coordinates when coord is higher than 2.
*	\throws provide_positive_argument when coord is smaller than 0.
*/
	shared_ptr<Coordinate> getCoordinate(const int coord) const;

/*!
*	\param angle The angle by which to rotate the triangle.
*	\param center The origin around which to rotate the triangle.
*
*	rotate makes use of Coordinate::rotate(const float angle, const Coordinate& center) function to rotate each corner of the triangle.
*/
	void rotate(const float angle, const Coordinate& center);

/*!
*	\param change a Coordinate by which the Triangle is to be moved by.
*/
	void move(const Coordinate change);


/*!
*	\param LineNo An integer representing one of the three lines that make up the triangle, may take values 0,1 and 2.
*	\return returns a Line object corresponding to the side of the triangle specified in LineNo
*/
	Line getLine(const int LineNo);

/*1
*	A vector containing three Coordinate objects that represent the corners of the Triangle.
*/
	vector<shared_ptr<Coordinate>> _coordinates;
};

#endif /* TRIANGLE_H_ */
