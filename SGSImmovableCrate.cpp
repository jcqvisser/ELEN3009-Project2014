/*
 * SGSImmovableCrate.cpp
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#include "SGSImmovableCrate.h"

SGSImmovableCrate::SGSImmovableCrate()
{
	_texture.setSmooth(true);
	_texture.loadFromFile("Crate.png", sf::IntRect(0, 0, 60, 60));
	setOrigin(20,40);
	setTexture(_texture);
}

SGSImmovableCrate::~SGSImmovableCrate() {}

void SGSImmovableCrate::Update()
{
	Coordinate center = _object->getCenter();
	setPosition(center.x(), center.y());
	setRotation(_object->getRotation()*180/PI+90);
}

void SGSImmovableCrate::changePosition(float x, float y)
{
	Coordinate newPos{x,y};
	_object->setPosition(newPos);
	setPosition(x,y);
}

void SGSImmovableCrate::animate(const float time)
{
	//_object->animate(time);
}
