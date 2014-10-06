#include "ImmovableCrate.h"

ImmovableCrate::ImmovableCrate() :
	Crate()
{
	_glued = true;
}

ImmovableCrate::~ImmovableCrate() {}

void ImmovableCrate::react(const Coordinate& rhs, const Coordinate& normal)
{
	clearForce();
}
