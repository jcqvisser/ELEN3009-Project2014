#ifndef IMMOVABLECRATE_H_
#define IMMOVABLECRATE_H_
#include "Crate.h"

/*!
*	\brief A crate object that cannot move.
*
*	Inherits from Crate, which, in turn inherits from GameObject.
*/
class ImmovableCrate : public Crate
{
public:
	ImmovableCrate();
	virtual ~ImmovableCrate();

	/*!
	*	\brief Overwritten react function that prevents the Crate from moving when it reacts to a collision.
	*/
	virtual void react(const Coordinate&, const Coordinate& normal);
};

#endif /* IMMOVABLECRATE_H_ */
