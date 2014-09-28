/*
 * SGSRocket.cpp
 *
 */

#include "SGSRocket.h"

SGSRocket::SGSRocket()
{
	_texture.setSmooth(true);
	_texture.loadFromFile("rocket.png", sf::IntRect(0,0, 10,34));
	setOrigin(5,17);
	setTexture(_texture,true);
}

SGSRocket::~SGSRocket() {
	// TODO Auto-generated destructor stub
}

void SGSRocket::Update()
{
	Coordinate center = _object->getCenter();

	setPosition(center.x(), center.y());
	setRotation(_object->getRotation()*180/PI+90);
}

void SGSRocket::changePosition(float x, float y)
{
	Coordinate newPos{x,y};
	_object->setPosition(newPos);
	setPosition(x,y);
}

void SGSRocket::animate(const float time)
{
	_object->propel();
	_object->animate(time);
}

void SGSRocket::setDirection(float angle)
{
	_object->setDirection(angle);
	Update();
}
