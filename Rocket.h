/*
 * Rocket.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef ROCKET_H_
#define ROCKET_H_
#include "CollisionManager.h"
#define ROCKETMASS 0.1
class Rocket : public GameObject
{
public:
	Rocket();
	virtual ~Rocket();

private:
	virtual void clearForce();
	float _rocketPower;
};

#endif /* ROCKET_H_ */
