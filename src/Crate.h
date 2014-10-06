#ifndef CRATE_H_
#define CRATE_H_
#include "CollisionManager.h"
#define CRATEMASS 5

/*!
*	\brief Represents a movable crate object.
*/
class Crate : public GameObject
{
public:
	/*!
	*	Creates Triangles that make up the collision-box, sets the drag coefficient and the mass.
	*/
	Crate();
	virtual ~Crate(); /**< Standard Virtual Destructor */

	/*!
	*	\brief Determines how a crate reacts to a collision.
	*
	* Overwrites react from GameObject
	*/
	virtual void react(const Coordinate&);
private:

};

#endif /* TANK_H_ */
