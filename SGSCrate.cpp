/*
 * SGSCrate.cpp
 *
 */

#include "SGSCrate.h"

SGSCrate::SGSCrate()
{
	_texture.setSmooth(true);
	_texture.loadFromFile("Crate.png", sf::IntRect(0, 0, 60, 60));
	setOrigin(30,30);
	setTexture(_texture);
}

SGSCrate::~SGSCrate() {
	// TODO Auto-generated destructor stub
}

void SGSCrate::Update()
{
	Coordinate center = _object->getCenter();
	setPosition(center.x(), center.y());
	setRotation(_object->getRotation()*180/PI+90);
}

void SGSCrate::changePosition(float x, float y)
{
	Coordinate newPos{x,y};
	_object->setPosition(newPos);
	setPosition(x,y);
}

void SGSCrate::animate(const float time)
{
	_object->animate(time);
}
