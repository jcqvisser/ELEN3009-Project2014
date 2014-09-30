/*
 * Tank.h
 *
 */

#ifndef TANK_H_
#define TANK_H_
#include <time.h>
#include "CollisionManager.h"
#define TANKMASS 300

class Rocket_Fire_Frequency_too_High{};

class Tank : public GameObject
{
public:
	Tank();
	virtual ~Tank();

	void driveForward();
	void driveReverse();
	void turnRight();
	void turnLeft();
	void fireRocket();

	virtual void react(const Coordinate&);
private:
	float _enginePowerFwd;
	float _enginePowerRev;
	float _turningPower;

	float _lastRocketFireTime = 0;
	float _rocketFirePeriod = 1.5;
};

#endif /* TANK_H_ */
