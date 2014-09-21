/*
 * Collision.h
 *
 *  Created on: 19 Sep 2014
 *      Author: Jacques
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include "GameObject.h"

class No_Collision{};
class Neither_of_these_are_moving_WTF{};

class Collision {
public:
	Collision(){};
	Collision(const Collision& col);
	Collision(
			const shared_ptr<GameObject>& obj1,
			const shared_ptr<GameObject>& obj2);
	virtual ~Collision();
	void printCollisionEdge() const;
	void resolve();

	shared_ptr<GameObject> _collider;
	shared_ptr<GameObject> _collidee;

	Coordinate _approachVelocity{};
	Line _collisionEdge;

private:
	void findCollisionEdge();
	void findCollision(
			shared_ptr<GameObject> obj1,
			shared_ptr<GameObject> obj2);
	void findApproachVelocity();

};

#endif /* COLLISION_H_ */