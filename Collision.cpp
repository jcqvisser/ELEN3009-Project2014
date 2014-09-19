/*
 * Collision.cpp
 *
 *  Created on: 19 Sep 2014
 *      Author: Jacques
 */

#include "Collision.h"

Collision::Collision(
		shared_ptr<GameObject> collider,
		shared_ptr<GameObject> collidee) :
			_collider(collider),
			_collidee(collidee)
{
	_approach = (collider->getVelocity() - collidee->getVelocity());
	findCollisionEdge();
}

Collision::~Collision() {
	// TODO Auto-generated destructor stud
}

void Collision::findCollisionEdge()
{
	shared_ptr<Coordinate> penetrator0{
		new Coordinate{_collidee->avgCoordInside(*_collider)}};
	shared_ptr<Coordinate> penetrator1{
		new Coordinate{*penetrator0 - _approach}};

	Line penetratingLine{ penetrator0, penetrator1};

	*_collisionEdge = _collidee->intersectingLine(penetratingLine);
}
