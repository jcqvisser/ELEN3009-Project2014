/*
 * Game.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef GAME_H_
#define GAME_H_
#include "GameLogic.h"

class Game {
public:
	Game();
	virtual ~Game();

	int hres = 1300;
	int vres = 700;

	void run();

private:
	sf::RenderWindow window{sf::VideoMode(hres,vres), "TANKS!"};

	shared_ptr<SGSTank> _player1;
	shared_ptr<SGSTank> _player2;

	vector<shared_ptr<SfmlGameSprite>> _gameObjects;

	GameLogic _logic;

	float _stepTime = 0.1;

	void draw();
};

#endif /* GAME_H_ */
