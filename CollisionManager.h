/*
 * CollisionManager.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include "Collision.h"

class CollisionManager {
public:
	CollisionManager(){};
	CollisionManager(vector<shared_ptr<GameObject>> gameObjects);
	virtual ~CollisionManager();
	void setGameObjecs(const vector<shared_ptr<GameObject>>& gameObjects);
	void findCollisions();
	void ResolveCollisions();
	int numCollisions();

private:
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<Collision> _collisions;
};

#endif /* COLLISIONMANAGER_H_ */
