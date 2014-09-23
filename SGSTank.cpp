/*
 * SGSTank.cpp
 *
 */

#include "SGSTank.h"

SGSTank::SGSTank()
{
	_texture.setSmooth(true);
	_texture.loadFromFile("Tank.png", sf::IntRect(0, 0, 50, 50));
	setOrigin(25,25);
	setTexture(_texture);
}

SGSTank::~SGSTank() {
	// TODO Auto-generated destructor stub
}

void SGSTank::Update()
{
	Coordinate center = _object->getCenter();
	setPosition(center.x(), center.y());
	setRotation(_object->getRotation()*180/PI+90);
}

void SGSTank::changePosition(float x, float y)
{
	Coordinate newPos{x,y};
	_object->setPosition(newPos);
	setPosition(x,y);
}

void SGSTank::animate(const float time)
{
	_object->animate(time);
}
