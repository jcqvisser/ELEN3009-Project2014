/*
 * CollisionManager.h
 *
 *  Created on: 18 Sep 2014
 *      Author: Jacques
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include "Collision.h"
#include <iterator>

class Objects_did_not_collide{};

class CollisionManager {
public:
	CollisionManager();
	virtual ~CollisionManager();


	Collision hasCollided(
			const shared_ptr<GameObject>& collider,
			const shared_ptr<GameObject>& collidee) const;
	void resolveCollision(Collision& col); // TODO
	void findCollisions(
			const vector<shared_ptr<GameObject>>& objects);
	void resolveAllCollisions();

	vector<shared_ptr<Collision>> _collisions;
};

#endif /* COLLISIONMANAGER_H_ */
