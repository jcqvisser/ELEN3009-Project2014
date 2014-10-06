#ifndef TANK_H_
#define TANK_H_
#include "CollisionManager.h"
#define TANKMASS 20
/*! \class Tank
*	\brief The Tank class represents a tank in game. It inherits from GameObject.
*	
*	The Tank class is a specialised form of GameObject. It has
functions allowing it to drive and an implementation of the virtual react function
which is called by a Collision object when the Tank object interacts iwht other objects
*/
class Tank : public GameObject
{
public:
/*!
*	The constructor creates triangles that act as the body of the tank when detecting collisions.
It also specifies the forces by which it drives and turns, it's mass, and it's drag coefficient.	
*/
	Tank();

/*!
*	Standard virtual destructor.
*/
	virtual ~Tank();

/*!
*	Applies a linear force on the tank in the direction it is facing.
*/
	void driveForward();
	
/*!
*	Applies a linear force on the tank in the opposite direction from where it is facing.
*/	
	void driveReverse();

/*!
*	Applies an angular force on the tank, causing it to rotate clockwise. The force is negative. (Right hand rule)
*/
	void turnRight();

/*!
*	Applies an angular force on the tank, causing it to rotate counter-clockwise. The force is positive. (Right hand rule)
*/
	void turnLeft();

/*!
*	Checks whether a rocket may be fired. If not, an exception is thrown. If one may be fired; the time is recorded.
*	\throws Rocket_Fire_Frequency_too_High when too little time has passed between consecutive calls of this function.
*/
	void fireRocket();

/*!
*	Checks whether a mine may be planted. If not, an exception is thrown. If one may be planted; the time is recorded.
*	\throws Mine_Plant_frequency_too_High when too little time has passed between consecutive calls of this function.
	\throws Out_of_Mines when too many mines have been planted.
*/
	void plantMine();

/*!
*	\param impulse A vector proportional to the mass and velocity of two objects colliding.
*
*	react is called by a Collision object during collision resolution.
*/
	virtual void react(const Coordinate& impulse);
private:
	float _enginePowerFwd;
	float _enginePowerRev;
	float _turningPower;

	float _lastRocketFireTime = 0;
	float _rocketFirePeriod = 0.5;

	float _lastMinePlantTime = 0;
	float _minePlantPeriod = 0.5;
	int _minesRemaining = 10;
};

#endif /* TANK_H_ */
