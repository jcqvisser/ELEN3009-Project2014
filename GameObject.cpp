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
		_center = Vertex{(Coordinate) *vert, 0}; //Workaround to make mass = 0
		_frictionForceMagnitude = vert->getMass()*_frictionCoeff*G;
	}
	else
	{
		_centerOfMass += *vert;
		_center += Vertex{(Coordinate) *vert, 0}; //Workaround to make mass = 0
		_frictionForceMagnitude = _frictionForceMagnitude/_vertices.size()*(_vertices.size()-1);
		_frictionForceMagnitude += (vert->getMass())/_vertices.size()*_frictionCoeff*G;
	}
	setPosition(_center.getX(), _center.getY()); //TODO should this be here?
}

void GameObject::printVertices()
{
	for (auto vert : _vertices)
	{
	 std::cout << vert->getX()  << " " << vert->getY() << " " << vert->getMass() << std::endl;
	}
}


void GameObject::applyForce(const VectorQuantity& force, const Coordinate& pos)
{
	if (pos == _centerOfMass)
	{
		_summedForce = force + _summedForce; // TODO incr by
	}
}

void GameObject::animate(float time)
{
	if (_summedForce.getMagnitude() > _frictionForceMagnitude)
	{
		VectorQuantity resultantForce{_summedForce.getAngle(), (_summedForce.getMagnitude() - _frictionForceMagnitude)}; // TODO scalar sub

	}

}

void GameObject::move(const Coordinate& pos)
{
	if (pos != _center)
	{
		float dx = pos.getX() - _center.getX();
		float dy = pos.getY() - _center.getY();

		for (auto coord : _vertices)
		{
			coord->setX(coord->getX() + dx);
			coord->setY(coord->getY() + dy);
		}

		_centerOfMass.setX(_centerOfMass.getX() + dx);
		_centerOfMass.setY(_centerOfMass.getY() + dy);

		_center.setX(_center.getX() + dx);
		_center.setY(_center.getY() + dy);
	}
}

