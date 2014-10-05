/*
 * Concrete.h
 *
 *  Created on: 04 Oct 2014
 *      Author: Jacques
 */

#ifndef CONCRETE_H_
#define CONCRETE_H_
#include "CollisionManager.h"

class Concrete : public GameObject
{
public:
	Concrete();
	virtual ~Concrete();
	virtual void react(const Coordinate&){};
};

#endif /* CONCRETE_H_ */
