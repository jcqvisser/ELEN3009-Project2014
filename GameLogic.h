/*
 * GameLogic.h
 *
 */


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include <list>
#include <time.h>
#include "Tank.h"
#include "Rocket.h"
#include "Crate.h"
#include "ImmovableCrate.h"
#include "Boundary.h"

class Player_Does_not_Exist{};

enum playerControl
{
	FORWARD,
	REVERSE,
	CLOCKWISE,
	ANTI_CLOCKWISE,
	FIRE_ROCKET,
	DROP_MINE
};

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();
	void loadLevel();
	void loadBoundary(const int hres, const int vres);
	void updateCollisionManager();

	void step(const float time);

	void checkRocketDamage();
	void checkTimedDeath();
	void checkHealthDeath();
	void playControl(const playerControl&, const int& player);
	int numObjects() const;

	list<shared_ptr<Tank>> _players;
	list<shared_ptr<Rocket>> _rockets;
	list<shared_ptr<ImmovableCrate>> _immovableCrates;
	list<shared_ptr<Crate>> _crates;
	//do not add to collision manager:
	list<shared_ptr<GameObject>> _explosion01s;

	shared_ptr<Boundary> _topBound;
	shared_ptr<Boundary> _bottomBound;
	shared_ptr<Boundary> _leftBound;
	shared_ptr<Boundary> _rightBound;

	CollisionManager _collMan{};

	float p1FireTime = clock()/CLOCKS_PER_SEC;
	float p2FireTime = clock()/CLOCKS_PER_SEC;
	float FireTime = 0.25;

	int _hres = 1300;
	int _vres = 700;
};

#endif /* GAMELOGIC_H_ */
