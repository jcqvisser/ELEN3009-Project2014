/*
 * CollisionManager.h
 *
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include "Collision.h"

class CollisionManager {
public:
	CollisionManager(){};
	CollisionManager(const float& stepTime);
	virtual ~CollisionManager();
	void setGameObjecs(const vector<shared_ptr<GameObject>>& gameObjects);
	void findCollisions();
	void ResolveCollisions();
	int numCollisions();
	void purgeCollisions();
	void purgeObjects();

private:
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<Collision> _collisions;
	float _stepTime = 0.1;
};

#endif /* COLLISIONMANAGER_H_ */
