#ifndef MINE_H_
#define MINE_H_
#include "CollisionManager.h"

/*!
*	\brief Represents an immovable mine object
*
*	Mine inherits from GameObject, it serves as an easy way of declaring the collision triangle for a GameObject so that it represents a mine.
*/
class Mine : public GameObject
{
public:
	/*!
	*	Creates the Collision triangle of the mine and sets it's mass.
	*/
	Mine();
	virtual ~Mine();

	/*!
	*	An overwritten react function that kills the mine as a reaction to a collision.
	*/
	virtual void react(const Coordinate&);
};

#endif /* MINE_H_ */
