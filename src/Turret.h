#ifndef TURRET_H_
#define TURRET_H_
#include "CollisionManager.h"
using namespace std;

class Turret : public GameObject {
public:
	Turret();
	virtual ~Turret();

	/*!
	*	\brief An overwritten version of GameObject's react function.
	*
	*	This function is empty and thus prevents the Turret object from reacting in a spatial way to any collisions.
	*/
	virtual void react(const Coordinate& thing){};

	/*!
	*	\brief Aims the turret at the closest target.
	*	\return Returns true if the turret is within some range of aiming at one of it's targets.
	*
	*	Initally the closest Target is determined using the Turret::closesTarget() function. The turret turns towards it's target and this function returns true if the target is within it's sights.
	*/
	bool aim();

	/*!
	*	\brief Does not actually create a rocket object.
	*	\throws Rocket_Fire_Frequency_too_High When this function is called too often.
	*
	*	This function does not fire a rocket, it simply dictates the frequency at chich rockets may be fired by throwing an exception if rockets are fired with too high a frequency.
	*/
	void fireRocket();

	/*!
	*	\brief Assigns a vector of Coordinates to the _targets vector.
	*/
	void setTargets(const vector<Coordinate>& targets);
private:

	/*!
	*	\brief Computes the target closes to the Turret.
	*	\return Returns a Coordinate representing the closest target.
	*
	*	This function loops through a vector of coordinates and determines which of them is closes to the center of mass of the Turret.
	*/
	Coordinate closestTarget();

	vector<Coordinate> _targets{};

	float _turningPower = 5;
	float _lastRocketFireTime = 0;
	float _rocketFirePeriod = 0.5;

	float _range = 500;
	float _accuracy = PI/5;

};

#endif /* TURRET_H_ */
