#ifndef ROCKET_H_
#define ROCKET_H_
#include "CollisionManager.h"
#define ROCKETMASS 2

class Rocket : public GameObject
{
public:
	/*!
	*	Sets the collision triangle, rocket power, lifetime, health and drag coefficient.
	*/
	Rocket();
	virtual ~Rocket();

	/*!
	*	\brief Propels the rocket forward.
	*
	*	Applies _rocketPower times the orientation vector to the rocket as a force.
	*/
	void propel();

	/*!
	*	\brief Changes the direction the rocket travels in.
	*	\param norm Expected to be some value times the unit normal of the surface the rocket has collided with.
	*
	*	adds twice the unit normal dotted with the rocket's orientation vector times it's orientation vector to the rocket's orientation vector. This makes the rocket appear to bounce off of surfaces.
	*/
	virtual void react(const Coordinate& norm);

	/*!
	*	\brief Sets the direction of the orientation vector.
	*/
	void setDirection(const float angle);

	/*!
	*	\brief Clears the linear and Angular force on the rocket.
	*/
	virtual void clearForce();

	float _rocketPower;	/**< a floating point number representing the magnitue of the force with which the rocket propels itself.
};

#endif /* ROCKET_H_ */
