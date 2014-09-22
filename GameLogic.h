/*
 * GameLogic.h
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "SGSTank.h"
#include "SGSMapBorder.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameLogic {
public:
	GameLogic(const shared_ptr<SGSTank>& player1, const shared_ptr<SGSTank>& player2);
	virtual ~GameLogic();
	void setBorders(const vector<shared_ptr<SGSMapBorder>> mb);

	void step();
	void controllerInput();

	shared_ptr<SGSTank> _player1;
	shared_ptr<SGSTank> _player2;

	CollisionManager _collMan;
};

#endif /* GAMELOGIC_H_ */
