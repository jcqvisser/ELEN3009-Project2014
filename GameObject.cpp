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

Coordinate GameObject::getCenter()
{
	return _centerOfMass;
}

Coordinate GameObject::getVelocity() const
{
	return _velocityLinear;
}

Coordinate GameObject::getForward() const
{
	return _forward;
}

float GameObject::getMass() const
{
	return _mass;
}

void GameObject::addTriangle(shared_ptr<Triangle>& tri)
{
	_triangles.push_back(*tri);

	_centerOfMass = Coordinate{0,0};

	for (auto tri : _triangles)
		for (auto coord : tri._coordinates)
		{
			_centerOfMass += *coord;
		}
	_centerOfMass = _centerOfMass/(_triangles.size()*3);
}



void GameObject::applyForceLinear(const Coordinate& force)
{

	_forceLinear += force;

}

void GameObject::applyImpulseLinear(const Coordinate& impulse)
{
	_velocityLinear += impulse;
}

void GameObject::rotate(const float& angle)
{
	for (auto triangle : _triangles)
		triangle.rotate(angle, _centerOfMass);
	_forward.rotate(angle);
}

void GameObject::move(const Coordinate& change)
{
	for (auto triangle : _triangles)
		triangle.move(change);
	_centerOfMass += change;
}

bool GameObject::animateLinear(const float& time)
{
	bool moved = false;

	if (_forceLinear.magSquared() > 0)
	{
		Coordinate a = _forceLinear/_dragCoeff;
		float e2 = exp(-_dragCoeff/_mass*time);
		float e1 = 1-e2;
		_velocityLinear = a*e1 + _velocityLinear*time*e2;

		Coordinate dPos = _velocityLinear*time;
		move(dPos);
		moved = true;
	}
	else if (_velocityLinear.magSquared() > 0)
	{
		float e2 = exp(-_dragCoeff/_mass*time);
		_velocityLinear = _velocityLinear*e2;

		Coordinate dPos = _velocityLinear*time;
		move(dPos);
		moved = true;
	}
	else
	{
		_velocityLinear = Coordinate{0,0};
	}

	return moved;
}

bool GameObject::animate(const float& time)
{
	animateLinear(time);
	rotate(_forceAngular*time);
	clearForce();
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
		temp = tri.coordsInside(tris);
		for (auto coord : temp)
		{
			xn += coord->x();
			yn += coord->y();
			count++;
		}
	}

	if (count == 0)
		throw No_Coordinates_Inside{};
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
			if (tri.getLine(n).intersects(penetratingLine))
			{
				return Line{tri.getLine(n)};
			}
		}
	}
	cout << endl <<  "No Line Intersects" << endl;
	throw No_Line_Intersects{};
}

bool GameObject::hasInside(const shared_ptr<GameObject>& gO)
{
	for (auto tri1 : _triangles)
		if (tri1.hasInside(gO->_triangles))
			return true;
	return false;
}

bool GameObject::hasInside(const Coordinate& coord) const
{
	auto coordPtr = make_shared<Coordinate>(coord);
	for (auto tri : _triangles)
	{
		if (tri.hasInside(coordPtr))
			return true;
	}
	return false;
}

void GameObject::setDragCoeff(const float& dC)
{
	_dragCoeff = dC;
}

void GameObject::clearForce()
{
	_forceLinear = Coordinate{0,0};
	_forceAngular = 0;
}

float GameObject::getRotation() const
{
	return _forward.angle();
}

void GameObject::setPosition(const Coordinate& pos)
{
	auto dPos = pos -getCenter();
	move(dPos);
}

vector<Triangle> GameObject::getTriangles() const
{
	return _triangles;
}

void GameObject::applyForceAngular(const float& force)
{
	_forceAngular += force;
}
