/*
 * Crate.h
 *
 *  Created on: 23 Sep 2014
 *      Author: Jacques
 */

#ifndef CRATE_H_
#define CRATE_H_
#include "CollisionManager.h"
#define CRATEMASS 10

class Crate : public GameObject
{
public:
	Crate();
	virtual ~Crate();
	virtual void react(const Coordinate&);
};

#endif /* CRATE_H_ */
