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

Collision::~Collision() {}

Collision::Collision(
		const shared_ptr<GameObject>& obj1,
		const shared_ptr<GameObject>& obj2,
		const float& stepTime)
{
	_stepTime = stepTime;
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
	{
		_approachVelocity = _collidee->getCenter() - _collider->getCenter();
		_approachVelocity = _approachVelocity/_approachVelocity.magnitude()*NOTHING;
	}
}

void Collision::resolve()
{

	//get normal and check that it points out of the object
	Coordinate normal = _collisionEdge.getNormal();
	if (_collisionEdge.isBelow(make_shared<Coordinate>(_collidee->getCenter())))
	{
		if (normal.y() < 0)
		{
			normal = normal*(-1);
		}
	} else
	{
		if (normal.y() > 0)
		{
			normal = normal*(-1);
		}
	}



	Coordinate colliderVel = _collider->getVelocity();
	Coordinate collideeVel = _collidee->getVelocity();
	float colliderMass = _collider->getMass();
	float collideeMass = _collidee->getMass();
	float totalMass = collideeMass + colliderMass;

	//Solve Clipping
	if (colliderVel > 0)
	{

		//Solve clipping for Rotation
		_collider->move(normal*_stepTime);

//		cout <<"Normal:" << normal.x() << " " << normal.y() << endl;
//		cout <<"ColPnt:" << _collisionPt.x() << " " << _collisionPt.y() << endl;
//		cout <<"N+Clpt:" << normal.x() + _collisionPt.x() << " " << normal.y() + _collisionPt.y() << endl;
//		cout <<"Center:" << _collidee->getCenter().x() << " " << _collidee->getCenter().y() << endl;
//		cout <<"ColLn1:" << _collisionEdge._coordinate1->x() << " " << _collisionEdge._coordinate1->y() << endl;
//		cout <<"ColLn2:" << _collisionEdge._coordinate2->x() << " " << _collisionEdge._coordinate2->y() << endl <<endl;

		//Newton's First Law (effectively)
		auto f = _collider->getForceLinear();
		_collider->clearForce();


	}
	else if (collideeVel > 0)
	{

		//Solve clipping for Rotation
		_collidee->move(normal*_stepTime);

		//Newton's First Law (effectively)
		auto f = _collidee->getForceLinear();
		_collidee->clearForce();

	}

	float momentum =
			collideeMass*(collideeVel*normal) +
			colliderMass*(colliderVel*normal);

	Coordinate ColliderImpulse = normal*(collideeMass/totalMass)*-momentum*0.01;
	Coordinate CollideeImpulse = normal*(colliderMass/totalMass)*momentum*0.01;

	_collidee->react(CollideeImpulse);
	_collider->react(ColliderImpulse);
}

void Collision::printCollisionEdge() const
{
	_collisionEdge.print();
}
