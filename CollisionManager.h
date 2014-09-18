/*
 * CollisionManager.h
 *
 *  Created on: 18 Sep 2014
 *      Author: Jacques
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include "GameObject.h"

class CollisionManager {
public:
	CollisionManager();
	virtual ~CollisionManager();

	bool hasCollided(
			const shared_ptr<GameObject>& obj1,
			const shared_ptr<GameObject>& obj2);
	void resolveCollision(
			shared_ptr<GameObject>& obj1,
			shared_ptr<GameObject>& obj2);
};

#endif /* COLLISIONMANAGER_H_ */
