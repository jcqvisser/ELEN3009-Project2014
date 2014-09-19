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

Coordinate GameObject::getVelocity() const
{
	return _velocityLinear;
}

float GameObject::getMass() const
{
	return _mass;
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

void GameObject::applyImpulseLinear(const Coordinate& impulse)
{
	_velocityLinear += impulse;
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

Coordinate GameObject::avgCoordInside(const GameObject& gO)
{
	float xn=0;
	float yn=0;
	int count = 0;

	auto tris = gO._triangles;

	vector<shared_ptr<Coordinate>> temp;
	for (auto tri : _triangles)
	{
		temp = tri->coordsInside(tris);
		for (auto coord : temp)
		{
			xn += coord->x();
			yn += coord->y();
			count++;
		}
	}

	xn /= count;
	yn /= count;
	return Coordinate{xn, yn};
}

Line GameObject::intersectingLine(const Line& penetratingLine)
{
	for (auto tri : _triangles)
	{
		for (int n = 0; n < 3; n++)
		{
			if (tri->getLine(n).intersects(penetratingLine))
			{
				return Line{tri->getLine(n)};
			}
		}
	}
	throw No_Line_Intersects{};
}

bool GameObject::hasInside(const shared_ptr<GameObject>& gO)
{
	for (auto tri1 : _triangles)
		if (tri1->hasInside(gO->_triangles))
			return true;
	return false;
}
