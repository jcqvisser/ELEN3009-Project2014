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
	try
	{
		findCollisionEdge();
	}
	catch(No_Collision&)
	{
		throw No_Collision{};
	}

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
	catch (No_Line_Intersects&)
	{
		throw No_Collision{};
	}
}
void Collision::findApproachVelocity()
{
	_approachVelocity = _collider->getVelocity() - _collidee->getVelocity();
	if (_approachVelocity < NOTHING)
		throw object_Rotated_Into_Collision{};
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

	normal.rotate(PI);

	Coordinate ColliderImpulse = normal*(momentum*_collidee->getMass()/totalMass)*1;
	Coordinate CollideeImpulse = normal*(-momentum*_collider->getMass()/totalMass)*1;

	_collidee->react(CollideeImpulse);
	_collider->react(ColliderImpulse);
}

void Collision::printCollisionEdge() const
{
	_collisionEdge.print();
}
