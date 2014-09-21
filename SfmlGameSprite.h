/*
 * SfmlGameSprite.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef SFMLGAMESPRITE_H_
#define SFMLGAMESPRITE_H_
#include <SFML/Graphics.hpp>
#include "Tank.h"

class SfmlGameSprite : public sf::Sprite
{
public:
	SfmlGameSprite();
	virtual ~SfmlGameSprite();
	shared_ptr<GameObject> _object;
	void Update();
};

#endif /* SFMLGAMESPRITE_H_ */
