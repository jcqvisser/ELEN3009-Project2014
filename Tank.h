/*
 * Tank.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef TANK_H_
#define TANK_H_
#include "CollisionManager.h"
#define TANKMASS 10

class Tank : public GameObject
{
public:
	Tank();
	virtual ~Tank();

	void driveForward();
	void driveReverse();
	void turnRight();
	void turnLeft();
private:
	float _enginePowerFwd;
	float _enginePowerRev;
	float _turningPower;
};

#endif /* TANK_H_ */
