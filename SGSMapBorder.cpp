/*
 * SGSMapBorder.cpp
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */

#include "SGSMapBorder.h"

SGSMapBorder::SGSMapBorder(const float hres)
{
	_object = shared_ptr<MapBorder>{new MapBorder{Coordinate{0,0}, Coordinate{hres,10}}};
	_texture.setSmooth(true);
	_texture.loadFromFile("border.png", sf::IntRect(0, 0, hres,10));
	setTexture(_texture);
	setOrigin(0,0);
}

SGSMapBorder::~SGSMapBorder()
{
	// TODO Auto-generated destructor stud
}

void SGSMapBorder::Update()
{
	Coordinate center = _object->getCenter();
	setOrigin(center.x(), center.y());
	setPosition(center.x(), center.y());
	setRotation(_object->getRotation()*180/PI+90);
}

void SGSMapBorder::changePosition(float x, float y)
{
	Coordinate newPos{x,y};
	_object->setPosition(newPos);
	setPosition(x,y);
}

void SGSMapBorder::addRotation(const float angle)
{
	_object->rotate(angle);
	Update();
}

