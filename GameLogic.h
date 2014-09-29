/*
 * GameLogic.h
 *
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include <list>
#include <time.h>
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
	void checkAllDeath();

	list<shared_ptr<SGSTank>> _players;

	list<shared_ptr<SGSRocket>> _rockets;
	list<shared_ptr<SGSImmovableCrate>> _immovableCrates;

	shared_ptr<Boundary> _topBound;
	shared_ptr<Boundary> _bottomBound;
	shared_ptr<Boundary> _leftBound;
	shared_ptr<Boundary> _rightBound;

	CollisionManager _collMan{_stepTime};


	float p1FireTime = clock()/CLOCKS_PER_SEC;
	float p2FireTime = clock()/CLOCKS_PER_SEC;
	float FireTime = 0.25;
	float _stepTime = 0.01;

	int _hres = 1300;
	int _vres = 700;
};

#endif /* GAMELOGIC_H_ */
