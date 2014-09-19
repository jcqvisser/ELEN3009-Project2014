/*
 * Collision.h
 *
 *  Created on: 19 Sep 2014
 *      Author: Jacques
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include "GameObject.h"

class Collision {
public:
	Collision(
			shared_ptr<GameObject> collider,
			shared_ptr<GameObject> collidee);
	virtual ~Collision();
	void findCollisionEdge();

	//ASSUMPTION: each coord will only cross one edge
	shared_ptr<GameObject> _collider;
	shared_ptr<GameObject> _collidee;

	Coordinate _approach{};
	shared_ptr<Line> _collisionEdge;



};

#endif /* COLLISION_H_ */
