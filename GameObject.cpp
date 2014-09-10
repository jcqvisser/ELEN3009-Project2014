/*
 * GameObject.cpp
 *
 *  Created on: 07 Sep 2014
 *      Author: Jacques
 */

#include "GameObject.h"

void GameObject::addVertex(const std::shared_ptr<Vertex>& vert)
{
	_vertices.push_back(vert);

	//recompute the center of mass
	if (_vertices.size() == 0)
	{
		_centerOfMass = *vert;
		_frictionForceMagnitude = vert->getMass()*_frictionCoeff*GACC;
	}
	else
	{
		_centerOfMass += *vert;
		_frictionForceMagnitude = _frictionForceMagnitude/_vertices.size()*(_vertices.size()-1);
		_frictionForceMagnitude += (vert->getMass())/_vertices.size()*_frictionCoeff*GACC;
	}
	setPosition(_centerOfMass.getX(), _centerOfMass.getY()); //TODO should this be here?
}

void GameObject::printVertices()
{
	for (auto vert : _vertices)
	{
	 std::cout << vert->getX()  << " " << vert->getY() << " " << vert->getMass() << std::endl;
	}
}


void GameObject::applyForce(const VectorQuantity& force)
{

	_summedForce = force + _summedForce; // TODO incr by

}

void GameObject::animate(float time)
{
	if (_summedForce.getMagnitude() > _frictionForceMagnitude)
	{
		//See Notes\ForceApplication.pdf
		VectorQuantity resultantForce{_summedForce.getAngle(), (_summedForce.getMagnitude() - _frictionForceMagnitude)}; // TODO scalar sub
		auto a = resultantForce/_dragCoeff;
		float e2 = exp(-_dragCoeff/_centerOfMass.getMass()*time);
		float e1 = 1-e2;
		_velocity = a*e1 + _velocity*e2;

		VectorQuantity dPos = _velocity * time;
		moveBy(dPos);
		clearForce();
	}
	else if (_velocity.getMagnitude() != 0)
	{
		float e2 = exp(-_dragCoeff/_centerOfMass.getMass()*time);
		_velocity = _velocity*e2;

		VectorQuantity dPos = _velocity * time;
		moveBy(dPos);
		clearForce();
	}

}

void GameObject::move(const Coordinate& pos)
{
	if (pos != _centerOfMass)
	{
		float dx = pos.getX() - _centerOfMass.getX();
		float dy = pos.getY() - _centerOfMass.getY();

		for (auto coord : _vertices)
		{
			coord->setX(coord->getX() + dx);
			coord->setY(coord->getY() + dy);
		}

		_centerOfMass.setX(_centerOfMass.getX() + dx);
		_centerOfMass.setY(_centerOfMass.getY() + dy);
		setPosition(_centerOfMass.getX() + dx, _centerOfMass.getY() + dy);
	}
}

void GameObject::moveBy(const VectorQuantity& d)
{
	float dx = d._coordinate.getX();
	float dy = d._coordinate.getY();

	float x = _centerOfMass.getX() + dx;
	float y = _centerOfMass.getY() + dy;

	move(Coordinate{x,y});
}

void GameObject::clearForce()
{
	_summedForce._coordinate.setX(0);
	_summedForce._coordinate.setY(0);
}

