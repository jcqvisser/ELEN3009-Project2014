/*
 * CollisionManager.cpp
 *
 *  Created on: 18 Sep 2014
 *      Author: Jacques
 */

#include "CollisionManager.h"

CollisionManager::CollisionManager() {
	// TODO Auto-generated constructor stud
}

CollisionManager::~CollisionManager() {
	// TODO Auto-generated destructor stud
}


Collision CollisionManager::hasCollided(
		const shared_ptr<GameObject>& collider,
		const shared_ptr<GameObject>& collidee) const
{
	if (collidee->hasInside(collider))
		return Collision{collider, collidee};

	throw Objects_did_not_collide{};
}

void CollisionManager::resolveCollision(Collision& col)
{
// TODO apply appropriate impulses to objects
}

void CollisionManager::findCollisions(
		const vector<shared_ptr<GameObject>>& objects)
{
	_collisions.clear();

	for (auto obj0 = objects.begin(); obj0 != objects.end(); ++obj0)
	{
		for (auto obj1 = obj0 + 1; obj1 != objects.end(); ++obj1)
		{
			try
			{
				_collisions.push_back(shared_ptr<Collision>{new Collision{*obj0, *obj1}});
			}
			catch(Objects_did_not_collide&)
			{
				//do nothing
			}
		}
	}

	if (_collisions.size() == 0)
		throw Objects_did_not_collide{};
}

void CollisionManager::resolveAllCollisions()
{
	for (auto collision : _collisions)
	{
		resolveCollision(*collision);
	}
	_collisions.clear();
}
