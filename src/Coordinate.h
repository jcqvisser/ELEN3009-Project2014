/*
 * Coordinate.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef COORDINATE_H_
#define COORDINATE_H_

#include <cmath>
#include <iostream>
/*! \def PI
 *  This defines the value of pi as a float, to be used in calculating angles.
 */

/*! \def INF
 * This value defines a very large number - approximately infinity to the program.
 */

/*! \def NOTHING
 * This value approximates zero
 */
#define PI 3.1415926536
#define INF 200000
#define NOTHING 0.001

class Collision_Exception{};

/*! \class Coordinate
 *  \brief The Coordinate class is used to define a point with an x value and a y value and perform operations on the coordinate.
 *
 * The class has overloaded operator functions for performing mathematical operations and comparisons on coordinates.
 * A coordinate can be defined by a magnitude and angle as well as an x value and y value.
 */
class Coordinate
{
public:
	~Coordinate(){};
	/*!
	 *  default constructor
	 */
	Coordinate();
	/*! \brief Coordinate has floats for x and y coordinates
	 * 	\param newX gives x coordinate
	 * 	\param newY gives y coordinate
	 */
	Coordinate(float newX, float newY);

	/*! Coordinate takes in a constant coordinate position by reference.
	 *
	 */
	Coordinate(const Coordinate& pos);

	/*! \brief angle gives the angle in degrees
	 *
	 * \return Angle is a float value.
	 */
	float angle() const;
	/*! \brief magnitude returns the distance of the coordinate from the origin
	 *
	 */
	float magnitude() const;
	/*! \brief magSquared returns the squared distance from the origin
	 *
	 */
	float magSquared() const;

	/*! 
	 *	\return Returns the x value of the Coordinate object.
	 */
	float x() const;

	/*!
	*	\return Returns the y value of the Coordinate object.
	*/
	float y() const;

	/*! \brief Prints the x and y values to the consile
	void print() const;	//!< Print the coordinate values to the console

	/*! \brief operator+ for addition of coordinates
	 * \param coord is an x,y coordinate
	 * \return returns sum of two coordinates
	 */
	Coordinate operator+(const Coordinate& coord) const;

	/*!  \brief operator- for coordinate subtraction
	 * 	\return returns difference of two coordinates
	 */
	Coordinate operator-(const Coordinate& coord) const;

	/*!  operator* for coordinate dot product
	 *   \return returns dot product
	 */
	float operator*(const Coordinate& coord) const; //dot product

	/*! \brief Adds the x and y components of the rhs Coordinate to the lhs coordinate.
	*/
	void operator+=(const Coordinate& coord);

	/*! \brief Subtracts the x and y components of the rhs Coordinate to the lhs coordinate.
	*/
	void operator-=(const Coordinate& coord);

	/*! \brief Evaluate the equality of two Coordinate objects.
	*
	*	The value of the x and y components from the LHS and RHS coordinates are compared.
	]*	\return Returns true if the _x and _y members of the LHS and RHS Coordinates have the same value.
	*/
	bool operator==(const Coordinate& coord) const;

	/*! \brief Determines whether the LHS Coordinate object has a larger magnitude than the RHS Coordinate object.
	*
	*	Makes use of the magSquared() function to evaluate the ralative magnitudes of the Coordinate objects being compared.
	*
	*	\return Returns true if the square of the magnitude of the LHS Coordinate object is larger than that of the RHS Coordinate object.
	*/ 
	bool operator>(const Coordinate& coord) const;
	
	/*! \brief Determines whether the LHS Coordinate object has a smaller magnitude than the RHS Coordinate object.
	*
	*	Makes use of the magSquared() function to evaluate the ralative magnitudes of the Coordinate objects being compared.
	*
	*	\return Returns true if the square of the magnitude of the LHS Coordinate object is smaller than that of the RHS Coordinate object.
	*/ 
	bool operator<(const Coordinate& coord) const;

	/*! \brief Multiplies the magnitude of the LHS by a factor supplied in the RHS float value.
	*	\param rhs A floating point value by which to multiply the magnitude of the coordinate.
	*	
	*	The _x and _y members of the Coordinate object are both multiplied by rhs
	*
	*	\return Returns a Coordinate with a magnitude rhs times larger than the original coordinate.
	*/
	Coordinate operator*(const float& rhs) const;

	/*! \brief Divides the magnitude of the LHS by a factor supplied in the RHS float value.
	*	\param rhs A floating point value by which to divide the magnitude of the coordinate.
	*	
	*	The _x and _y members of the Coordinate object are both divided by rhs
	*
	*	\return Returns a Coordinate with a magnitude rhs times smaller than the original coordinate.
	*/
	Coordinate operator/(const float& rhs) const;

	/*! \brief determines whether the magnitude of a Coordinate object is larger than a supplied floating point number.
	*	\param rhs A floating point number to compare to the magnitude of the Coordinate object.
	*
	*	The magnitude of the Coordinate object is obtained by making use of the function magnitude(), this is compared with rhs.
	*
	*	\return True if the magnitude of the Coordinate is larger than rhs. False else.
	*/
	bool operator>(const float& rhs) const;

	/*! \brief determines whether the magnitude of a Coordinate object is smaller than a supplied floating point number.
	*	\param rhs A floating point number to compare to the magnitude of the Coordinate object.
	*
	*	The magnitude of the Coordinate object is obtained by making use of the function magnitude(), this is compared with rhs.
	*
	*	\return True if the magnitude of the Coordinate is smaller than rhs. False else.
	*/
	bool operator<(const float& rhs) const;

	/*! \brief determines whether the magnitude of a Coordinate object is the same as a supplied floating point number.
	*	\param rhs A floating point number to compare to the magnitude of the Coordinate object.
	*
	*	The magnitude of the Coordinate object is obtained by making use of the function magnitude(), this is compared with rhs.
	*
	*	\return True if the magnitude of the Coordinate equal to rhs. False else.
	*/
	bool operator==(const float& rhs) const;

	/*! \brief Rotates the object around a point in 2D space
	*	\param angle A floating point value representing the angle, in radians, the coordinate is rotated by.
	*	\param center A Coordinate object that represents the origin around which the calling Coordinate is rotated.
	*
	*	The Coordinate is moved so that is is seen as relative to center. It is then rotated about the origin, and the initial movement operation is undone.
	*	This makes use of the rotate(const float angle) function.
	*/
	void rotate(const float angle, const Coordinate& center);

	/*! \brief Rotates the calling Coordinate object around the origin.
	*	\param angle A floating point value representing the angle, in radians, the coordinate is rotated by.
	*
	*	\A rotation matrix is constructed, using angle as Theta. The calling coordinate is then multiplied by this matrix.
	*/
	void rotate(const float angle);

	float _x; //< The x value of a Coordinate object.
	float _y; //< The y value of a Coordinate object.

	/*! \brief Setter for _x
	*	\param x This value is assigned to _x of the Coordinate object.
	*/
	void setX(float x);
	
	/*! \brief Setter for _y
	*	\param y This value is assigned to _y of the Coordinate object.
	*/
	void setY(float y);
};

#endif /* COORDINATE_H_ */
