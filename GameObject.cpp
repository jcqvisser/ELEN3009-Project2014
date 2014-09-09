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
		_frictionLinear = vert->getMass()*_frictionCoeff;
		//TODO: angular
	}
	else
	{
		_centerOfMass += *vert;
		_center += Vertex{(Coordinate) *vert, 0}; //Workaround to make mass = 0
		if (_centerOfMass.dist(*vert) > _maxDistFromCoM)
			_maxDistFromCoM = _centerOfMass.dist(*vert);
		_frictionLinear = _frictionLinear/_vertices.size()*(_vertices.size()-1);
		_frictionLinear += (vert->getMass())/_vertices.size();
		//TODO: angular
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
}

