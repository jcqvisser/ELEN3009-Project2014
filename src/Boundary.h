/*
 * Boundary.h
 *
 *  Created on: 28 Sep 2014
 *      Author: Jacques
 */

#ifndef BOUNDARY_H_
#define BOUNDARY_H_
#include "CollisionManager.h"

/** Direction Enumeration. Each value represents a side of the window.*/
enum direction{
	NORTH, /**<Represents the top side*/
	SOUTH, /**<Represents the bottom side*/
	EAST, /**<Represents the right side*/
	WEST /**<Represents the left side*/
};

/*!
*	\brief Represents a boundary to the window.
*
*	GameObjects are able to move off the window, unless their path is blocked by some other GameObject.
*	Boundary objects fulfill this purpose. They are created using the window dimentions and an enum value, thus the four boundaries can be created easily. Furthermore, they are immovable, so once the four Boundary objects are created all the GameObjects created in the window are constrained to the window, assuming working collision management.
*/
class Boundary : public GameObject
{
public:
	/*!
	*	\brief Creates on of the four screen boundaries.
	*	\param hres Horisontal window resolution
	*	\param vres Vertical window resolution
	*	\param direction An enum indicating which of the four borders to create.
	*/
	Boundary(const int hres, const int vres, const direction);

	/*
	*	\brief Standard virtual destructor.
	*/
	virtual ~Boundary();
};

#endif /* BOUNDARY_H_ */
