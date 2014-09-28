/*
 * Boundary.h
 *
 *  Created on: 28 Sep 2014
 *      Author: Jacques
 */

#ifndef BOUNDARY_H_
#define BOUNDARY_H_
#include "CollisionManager.h"

class Boundary : public GameObject
{
public:
	Boundary(const int hres, const int vres);
	virtual ~Boundary();

	virtual void react(const Coordinate&) {};
};

#endif /* BOUNDARY_H_ */
