/*
 * GameObject.cpp
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#include "GameObject.h"

GameObject::GameObject(float mass) :
	_mass(mass)
{}

Coordinate GameObject::getCenter() const
{
	return _centerOfMass;
}

void GameObject::addTriangle(const shared_ptr<Triangle>& tri)
{
	_triangles.push_back(tri);
	for (int i = 0; i < 3; i++)
	{
		_centerOfMass += *(tri->getCoordinate(i));
	}
}

void GameObject::glue()
{	_glued = true;}

void GameObject::unglue()
{	_glued = false;}

void GameObject::applyForceLinear(const Coordinate& force)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};
	_forceLinear += force;

}

void GameObject::applyForceAngular(const float& force)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};
	_forceAngular += force;
}

void GameObject::rotate(const float& angle)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};
	for (auto triangle : _triangles)
		triangle->rotate(angle, _centerOfMass);
	_forward.rotate(angle, _centerOfMass);
}

void GameObject::move(const Coordinate& change)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};
	for (auto triangle : _triangles)
		triangle->move(change);
}

bool GameObject::animateLinear(const float& time)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};
	bool moved = false;

	if (_forceLinear > _forceLinearThreshold)
	{
		Coordinate a = _forceLinear/_dragCoeffLinear;
		float e2 = exp(-_dragCoeffLinear/_mass*time);
		float e1 = 1-e2;
		_velocityLinear = a*e1 + _velocityLinear*time*e2;

		Coordinate dPos = _velocityLinear*time;
		move(dPos);
		moved = true;
		_forceLinear = Coordinate{};
	}
	else if (_velocityLinear > _vThresholdLinear)
	{
		float e2 = exp(-_dragCoeffLinear/_mass*time);
		_velocityLinear = _velocityLinear*time*e2;

		Coordinate dPos = _velocityLinear*time;
		move(dPos);
		moved = true;
		_forceLinear = Coordinate{};
	}
	else
	{
		_velocityLinear = Coordinate{0,0};
	}

	return moved;
}

bool GameObject::animateAngular(const float& time)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};

	bool rotated = false;

	if (_forceAngular > _forceAngularThreshold)
	{
		float a = _forceAngular/_dragCoeffAngular;
		float e2 = exp(-_dragCoeffAngular/_mass*time);
		float e1 = 1-e2;
		_velocityAngular = a*e1 + _velocityAngular*time*e2;

		float dPos = _velocityAngular*time;
		rotate(dPos);

		rotated = true;
		_forceAngular = 0;
	}
	else if (_velocityAngular > _vThresholdAngular)
	{
		float e2 = exp(-_dragCoeffAngular/_mass*time);
		_velocityAngular = _velocityAngular*time*e2;

		float dPos = _velocityAngular*time;
		rotate(dPos);

		rotated = true;
		_forceAngular = 0;
	}
	else
	{
		_velocityAngular = 0;
	}

	return rotated;
}

bool GameObject::animate(const float& time)
{
	if (_glued == true)
		throw object_is_glued_and_cannot_move{};
	bool move = animateLinear(time);
	bool rotate = animateAngular(time);

	if (move || rotate)
		return true;

	return false;
}
