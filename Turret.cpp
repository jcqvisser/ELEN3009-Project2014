///*
// * Turret.cpp
// *
// *  Created on: 30 Sep 2014
// *      Author: Jacques
// */
//
//#include "Turret.h"
//
//
//Turret::Turret(const vector<shared_ptr<Tank>>& tanks) :
//	GameObject(1),
//	_tanks(tanks)
//{ }
//
//Turret::~Turret() {
//	// TODO Auto-generated destructor stub
//}
//
//shared_ptr<Tank> Turret::closestTank()
//{
//	shared_ptr<Tank> closest;
//	float distSquaredClosest =_range *90;;
//	for (auto tank : _tanks)
//	{
//		float distSquared = (tank->getCenter() - getCenter()).magSquared();
//		if (distSquared < distSquaredClosest )
//			closest = tank;
//	}
//	return closest;
//}
//
//bool Turret::aim()
//{
//	shared_ptr<Tank> closest = closestTank();
//	float tankAngle = (closest->getCenter() - getCenter()).angle();
//	float turretAngle = _forward.angle();
//	float dAngle = tankAngle - turretAngle;
//	float dist = (closest->getCenter() - getCenter()).magnitude();
//
//	if (tankAngle > turretAngle)
//		applyForceAngular(_turningPower);
//	else
//		applyForceAngular(-_turningPower);
//
//
//
//	if (abs(dAngle) < _accuracy && dist < _range)
//		return true;
//	else
//		return false;
//}
//
//void Turret::fireRocket()
//{
//	float time = clock();
//	time = time/CLOCKS_PER_SEC;
//	if (time >= _lastRocketFireTime + _rocketFirePeriod)
//	{
//		_lastRocketFireTime = time;
//	}
//	else
//	{
//		throw Rocket_Fire_Frequency_too_High{};
//	}
//}
