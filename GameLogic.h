/*
 * GameLogic.h
 *
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "SGSTank.h"
#include "SGSRocket.h"
#include "SGSCrate.h"
#include "SGSImmovableCrate.h"
#include "Boundary.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#define MAXROCKETS 50

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();
	void loadLevel();
	void loadBoundary(const int hres, const int vres);
	void coreLoop();
	void updateCollisionManager();

	void step(const float time);
	void controllerInput();

	void checkPlayerDeath();

	float _stepTime = 0.01;

	shared_ptr<SGSTank> _player1{new SGSTank{}};
	shared_ptr<SGSTank> _player2{new SGSTank{}};

	vector<shared_ptr<SGSRocket>> _rockets;
	vector<shared_ptr<SGSImmovableCrate>> _immovableCrates;

	shared_ptr<Boundary> bound;

	CollisionManager _collMan{_stepTime};
	sf::Clock clock{};

	sf::Time p1FireTime = clock.getElapsedTime();
	sf::Time p2FireTime = clock.getElapsedTime();
	sf::Time FireTime = sf::seconds(0.25f);

	int _hres = 1300;
	int _vres = 700;
};

#endif /* GAMELOGIC_H_ */
