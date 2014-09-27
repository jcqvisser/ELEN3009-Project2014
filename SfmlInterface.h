/*
 * SfmlInterface.h
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#ifndef SFMLINTERFACE_H_
#define SFMLINTERFACE_H_
#include "SGSTank.h"
#include "SGSRocket.h"
#include "SGSCrate.h"
#include "SGSImmovableCrate.h"
#include "GameLogic.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class SfmlInterface {
public:
	SfmlInterface();
	virtual ~SfmlInterface();
private:
	vector<shared_ptr<SfmlGameSprite>> _gameSprites;
	GameLogic _gameLogic{};
};

#endif /* SFMLINTERFACE_H_ */
