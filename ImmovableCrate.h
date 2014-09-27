/*
 * ImmovableCrate.h
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#ifndef IMMOVABLECRATE_H_
#define IMMOVABLECRATE_H_
#include "Crate.h"

class ImmovableCrate : public Crate
{
public:
	ImmovableCrate();
	virtual ~ImmovableCrate();
	virtual void react(const Coordinate&);
};

#endif /* IMMOVABLECRATE_H_ */
