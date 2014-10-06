#ifndef LINE_H_
#define LINE_H_
#include "Coordinate.h"
#include <iostream>
#include <memory>

class Lines_Do_Not_Intersect{};
class Infinite_Slope{};

/*! \class Line
*	\brief 
class Line {
public:
	/*! \brief Standard virtual destructor
	*/
	virtual ~Line();

	/*! \brief Default constructor
	*/
	Line(){};

	/*! \brief Constructs a Line object representing a line between two coordinates
	*	\param coord1 Point in 2D space where the line starts.
	*	\param coord2 Point in 2D space where the line ends.
	*/
	Line(const std::shared_ptr<Coordinate>& coord1,
		 const std::shared_ptr<Coordinate>& coord2);

	/*! \brief Copy Constructor
	*
	*	Creates a line which is a copy of another line. This new line has it's own begin and end ponts.
	*/
	Line(const Line& lin);
	
	/*! \brief Operator that evaluates the equality of two lines.
	*
	*	Determines whether the begin and end points of the one line matches that of the other.
	*/
	bool operator==(const Line& rhs) const;
	
	/*! \brief Determines the square of the length of the line, ie. the squared distance between the begin and end points.
	*
	*	The suared length of a line is found by subtracting the end Coordinate from the begin Coordinate, and finding the squared magnitude of the result.
	*	lengthSquared() takes a shorter time to compute than length()
	*/
	float lengthSquared() const;

	/*! \brief Determines the length of the line, ie. the distance between the begin and end points.
	*
	*	The length of a line is found by subtracting the end Coordinate from the begin Coordinate, and finding the magnitude of the result.
	*	lenght() takes longer than lengthSquared() due to it having to do one more operation: a square root.
	*/
	float length() const;

	/*! \brief Determines whether a Coordinate appears below the Line.
	*	\param coord A shared pointer to a Coordinate, the position, relative to the line, is to be evaluated.
	*
	*	The horisontal component of coord is passed to getYVal(float xVal) in irder to obtain its corresponding vertical component on the line, this is then compared to the vertical component of coord.
	*	
	*	\return Returns true if coord is below the line in a 2D plane. Returns false otherwise.
	*/
	bool isBelow(const std::shared_ptr<Coordinate>& coord) const;

	/*! \brief determines whether two lines intersect.
	*	\param line A line used to check for intersection.
	*
	*	Makes use of intersectionPt(const Line& ln). The exception Lines_Do_Not_Intersect{} is caught and false is returned. If it not caught true is returned.
	*/
	bool intersects(const Line& line) const ;

	/*! \brief Finds the intersection point between two lines as a Coordinate.
	*	\param ln A Line object to check for intersection
	*	\throws Lines_Do_Not_Intersect Thrown when the lines under scrutiny do not intersect.
	*
	*/
	Coordinate intersectionPt(const Line& ln) const;

	/*!
	*	\brief Returns true when the coordinate is on the line.
	*/
	bool isOnLine(const Coordinate& coord) const;

	/*!
	*	\brief Finds the normal to the line as a unit vector.
	*	\return Returns a Coordinate representing a unit vector normal to the line.
	*/
	Coordinate getNormal();

	std::shared_ptr<Coordinate> _coordinate1; /**< The starting point of the line */
	std::shared_ptr<Coordinate> _coordinate2; /**< The end-point of the line*/

	void print() const; /**< Prints the stert and end point to the console. */

	/*!	\brief Finds the y value on the line corresponding to a supplied x value
	*	\param xVal A floating point number representing the x-value of which to find the y-value
	*	\return a floating point number, the Y value corresponding to the supplied x value.
	*	\throws 
	*/
	float getYVal(float xVal) const; 

	/*!
	*	\brief Finds the slope of the line.
	*	\return Returns a floating point number representing the slope of the line.
	*/
	float getSlope() const;
	
	/*!
	*	\brief finds the Y-intercept of the line.
	*	\return Returns a floating point number representing the Y-intercept of the line.
	*/
	float getYIntercept() const;

	/*!
	*	\brief Determines whether a floating bpoint number is between two other floating point numbers.
	*/
	float isBetween(const float& pt0, const float& bound1, const float& bound2) const;
private:

};

#endif /* LINE_H_ */
