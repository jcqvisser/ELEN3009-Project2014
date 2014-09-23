/*
 * GameLogic.h
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "SGSTank.h"
#include "SGSRocket.h"
#include "SGSCrate.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#define MAXROCKETS 50

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();
	void coreLoop();
	void updateCollisionManager();

	void step();
	void controllerInput();

	void checkPlayerDeath();
	void loadLevelLayout(const int level);

	shared_ptr<SGSTank> _player1{new SGSTank{}};
	shared_ptr<SGSTank> _player2{new SGSTank{}};

	vector<shared_ptr<SGSRocket>> _rockets;

	vector<shared_ptr<SGSCrate>> _crates;

	CollisionManager _collMan;
	sf::Clock clock{};

	sf::Time p1FireTime = clock.getElapsedTime();
	sf::Time p2FireTime = clock.getElapsedTime();
	sf::Time FireTime = sf::seconds(0.25f);
};

#endif /* GAMELOGIC_H_ */
