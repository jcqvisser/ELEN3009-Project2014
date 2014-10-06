#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_
#include "Collision.h"

/*!
*	\brief Handles Collisions between objects.
*
*	Creates, resolves and erases collisions between a set of GameObjects.
*/
class CollisionManager {
public:
	CollisionManager(){}; /**< Default Constructor*/
	virtual ~CollisionManager(); /**< Standard Virtual Destructor*/

	/*!
	*	/brief Sets the vector of shared pointers to GameObjects to be iterated through to find collisions.
	*/
	void setGameObjecs(const vector<shared_ptr<GameObject>>& gameObjects);

	/*!
	*	\Brief Finds collsions between listed GameObjects
	*
	*	Enumerates all the non-ordered combinations of two GameObjects from _gameObjects and tests whether they collide by attempting to create a Collision object using the two objects and catching any exceptions thrown when these two GameObject objects do not collide.
	*/
	void findCollisions();

	/*!
	*	/brief Resolves all listed Collision objects.
	*/
	void ResolveCollisions(const float stepTime);

	int numCollisions(); /**< Returns the number of collisions */

	void purgeCollisions(); /**< Removes all Collision objects- must be done when they are all resolved. */

	void purgeObjects(); /**< Removes all GameObjects*/

private:
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<Collision> _collisions;
};

#endif /* COLLISIONMANAGER_H_ */
