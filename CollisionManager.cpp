/*
 * CollisionManager.cpp
 *
 */

#include "CollisionManager.h"

CollisionManager::CollisionManager(const float& stepTime) :
		_stepTime(stepTime)
{}

CollisionManager::~CollisionManager() { }

void CollisionManager::setGameObjecs(const vector<shared_ptr<GameObject>>& gameObjects)
{
	_gameObjects = gameObjects;
}

void CollisionManager::findCollisions()
{
	for (unsigned go1 = 0; go1 < _gameObjects.size()-1; go1++)
	{
		for (unsigned go2 = go1+1; go2 < _gameObjects.size(); go2++)
		{
			if ( _gameObjects[go1]->hasInside(_gameObjects[go2]) ||
				(_gameObjects[go2]->hasInside(_gameObjects[go1])))
			{
				try
				{
					Collision col{_gameObjects[go1], _gameObjects[go2], _stepTime};
					_collisions.push_back(col);
				}
				catch(No_Collision&)
				{
					cout << "issue01_01 something" << endl;
				}
				catch(object_Rotated_Into_Collision&)
				{
					//Do Nothing
					cout << "issue01_02 : obj rotate into collision" << endl;
				}
			}
		}
	}
}

void CollisionManager::ResolveCollisions()
{
	for (auto col : _collisions)
	{
		col.resolve();
	}
}

int CollisionManager::numCollisions()
{
	return _collisions.size();
}

void CollisionManager::purgeCollisions()
{
	_collisions.clear();
}

void CollisionManager::purgeObjects()
{
	_gameObjects.clear();
}

