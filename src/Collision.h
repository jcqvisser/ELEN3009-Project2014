/*
 * Collision.h
 *
 */

#ifndef COLLISION_H_
#define COLLISION_H_
#include "GameObject.h"

class No_Collision : public Collision_Exception {};
class object_Rotated_Into_Collision : public Collision_Exception {};

class Collision {
public:
	/*!
	*	\brief Default Constructor
	*/
	Collision(){};

	/*!
	*	\brief Copy Constructor
	*/
	Collision(const Collision& col);

	/*!
	*	\brief Constructor taking shared pointers to two GameObjects
	*	\param obj1 A shared pointer to a GameObject that is expected to have collided with obj2
	*	\param obj2 A shared pointer to a GameObject that is expected to hace collided with obj1
	*	\throws No_Collision This is thrown when two GameObjects that are not involved in a collision is passed to the constructor.
	*	
	*/
	Collision(
			const shared_ptr<GameObject>& obj1,
			const shared_ptr<GameObject>& obj2);

	/*!
	*	\brief Standard virtual destructor.
	*/
	virtual ~Collision();

	/*!
	*	\brief Prints the x and y values of the Coordinates making up the collision edge line.
	*/
	void printCollisionEdge() const;

	/*!
	*	\brief Resolves the collision.
	*	\param stepTime The time to reverse the simulation by in order to undo the collision.
	*
	*	Firstly the normal of the collision edge is computed, it is checked that it is pointing out of the GameObject which incorporates the collision edge. This is done by comparing the position of the GameObject's center of mass and the normal relative to the collision edge, and inverting the normal if appropriate.
	*
	*Next the total momentum involved in the collision is computed and redistributed in a manner so that the more massive object is affected less by the collision. This redistribution is applied using the GameObject::react(const Coordinate& rhs) function. before applying the GameObject::animate(const float& time) 

	Furthermore, clipping between game objects is checked and solved by moving them apart, accoring to the normal until they do not overlap.                
	*/
	void resolve(const float stepTime);

	shared_ptr<GameObject> _collider; /**< a shared pointer to a GameObject which has coordinates inside the _collidee GameObject*/
	shared_ptr<GameObject> _collidee; /**< a shared pointer to a GameObject whose coordinates are inside _collider*/

	Line _collisionEdge; /**< The line on which the collision takes place.*/

	/*!
	*	\brief Finds the edge on which the collision took place.
	*/
	void findCollisionEdge();

	/*!
	*	\brief Arranges the GameObjects into _collider and _collidee
	*/
	void findCollision(
			shared_ptr<GameObject> obj1,
			shared_ptr<GameObject> obj2);
};

#endif /* COLLISION_H_ */
