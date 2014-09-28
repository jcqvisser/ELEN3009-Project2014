/*
 * Tank.h
 *
 */

#ifndef TANK_H_
#define TANK_H_
#include "CollisionManager.h"
#define TANKMASS 300

class Tank : public GameObject
{
public:
	Tank();
	virtual ~Tank();

	void driveForward();
	void driveReverse();
	void turnRight();
	void turnLeft();

	virtual void react(const Coordinate&);
private:
	float _enginePowerFwd;
	float _enginePowerRev;
	float _turningPower;
};

#endif /* TANK_H_ */
