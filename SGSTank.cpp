/*
 * SGSTank.cpp
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#include "SGSTank.h"

SGSTank::SGSTank()
{
	texture.setSmooth(true);
	texture.loadFromFile("tank.png", sf::IntRect(0, 0, 50, 50));
	setTexture(texture);
}

SGSTank::~SGSTank() {
	// TODO Auto-generated destructor stub
}

