///*
// * Turret.h
// *
// *  Created on: 30 Sep 2014
// *      Author: Jacques
// */
//
//#ifndef TURRET_H_
//#define TURRET_H_
//#include "CollisionManager.h"
//#include "Tank.h"
//
//class Turret : public GameObject {
//public:
//	Turret(const vector<shared_ptr<Tank>>& tanks);
//	virtual ~Turret();
//
//	virtual void react(const Coordinate&);
//	bool aim();
//	void fireRocket();
//private:
//	shared_ptr<Tank> closestTank();
//
//	vector<shared_ptr<Tank>> _tanks;
//
//	float _turningPower = 3;
//	float _lastRocketFireTime = 0;
//	float _rocketFirePeriod = 1.5;
//
//	float _range = 300;
//	float _accuracy = PI/10;
//
//};
//
//#endif /* TURRET_H_ */
