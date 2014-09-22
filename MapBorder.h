/*
 * MapBorder.h
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */

#ifndef MAPBORDER_H_
#define MAPBORDER_H_
#include "CollisionManager.h"

class MapBorder : public GameObject
{
public:
	MapBorder(const Coordinate&, const Coordinate&);
	virtual ~MapBorder();
};

#endif /* MAPBORDER_H_ */
