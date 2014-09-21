/*
 * SfmlGameSprite.cpp
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#include "SfmlGameSprite.h"

SfmlGameSprite::SfmlGameSprite()
{ }

SfmlGameSprite::~SfmlGameSprite() {
	// TODO Auto-generated destructor stub
}

void SfmlGameSprite::Update()
{
	setPosition(_object->getCenter().x(), _object->getCenter().y());
	setRotation(_object->getRotation());
}


