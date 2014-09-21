/*
 * Collision.cpp
 *
 *  Created on: 19 Sep 2014
 *      Author: Jacques
 */

#include "Collision.h"



Collision::Collision(const Collision& col) :
	_collider(col._collider),
	_collidee(col._collidee),
	_approachVelocity(col._approachVelocity),
	_collisionEdge(col._collisionEdge)
{ }

Collision::~Collision() {
	// TODO Auto-generated destructor stud
}

Collision::Collision(
		const shared_ptr<GameObject>& obj1,
		const shared_ptr<GameObject>& obj2)
{
	findCollision(obj1, obj2);
	findApproachVelocity();
	findCollisionEdge();
}

void Collision::findCollision(
		shared_ptr<GameObject> obj1,
		shared_ptr<GameObject> obj2)
{
	if (obj1->hasInside(obj2))
	{
		_collider = obj2;
		_collidee = obj1;
	}
	else if (obj2->hasInside(obj1))
	{
		_collider = obj1;
		_collidee = obj2;
	}
	else
		throw No_Collision{};

}
void Collision::findCollisionEdge()
{
	try
	{
		shared_ptr<Coordinate> penetrator0{
			new Coordinate{_collidee->avgCoordInside(*_collider)}};
		shared_ptr<Coordinate> penetrator1{
			new Coordinate{*penetrator0 - _approachVelocity*INF}};

		Line penetratingLine{ penetrator0, penetrator1};
		_collisionEdge = _collidee->intersectingLine(penetratingLine);
	}
	catch (No_Coordinates_Inside&)
	{
		throw No_Collision{};
	}
}
void Collision::findApproachVelocity()
{
	_approachVelocity = _collider->getVelocity() - _collidee->getVelocity();
	if (_approachVelocity < NOTHING)
		throw Neither_of_these_are_moving_WTF{}; //this should never happen
}

void Collision::resolve()
{
	Coordinate normal = _collisionEdge.getNormal();
	float momentum =
			_collidee->getMass()*
				(_collidee->getVelocity()*normal) +
			_collider->getMass()*
				(_collider->getVelocity()*normal);
	momentum = momentum*0.5;

	float totalMass = _collider->getMass() + _collidee->getMass();

	//direction is stated in direction that collider is traveling
	float normAngle = normal.angle();
	float colliderAngle = _collider->getVelocity().angle();
	if (abs(normAngle - colliderAngle) > PI/2)
		normal.rotate(PI);

	Coordinate ColliderImpulse = normal*(momentum*_collidee->getMass()/totalMass);
	Coordinate CollideeImpulse = normal*(momentum*_collider->getMass()/totalMass);

	_collidee->applyImpulseLinear(CollideeImpulse);
	_collider->applyImpulseLinear(ColliderImpulse);
}

void Collision::printCollisionEdge() const
{
	_collisionEdge.print();
}
