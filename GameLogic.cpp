/*
 * GameLogic.cpp
 *
 */

#include "GameLogic.h"

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic() {}

void GameLogic::step(const float time)
{
	animate(time);
	checkRocketDamage();
	checkMineDamage();
	checkTimedDeath();

	updateCollisionManager();
	_collMan.findCollisions();
	_collMan.ResolveCollisions(time);
	_collMan.purgeCollisions();

	clearForces();

	turretAction();
	checkHealthDeath();
}

void GameLogic::playControl(const playerControl& control, const int& playerNo)
{

	if (getScorer() != 0 && control == RESPAWN)
	{
		resetPlayers();
	}

	if (getRemainingTime() <= 0)
		return;

	if (playerNo >= _players.size()+1 || playerNo < 1)
		throw Player_Does_not_Exist{};

	auto player = _players.begin();

	for (int n = 1; n < playerNo; ++n) //this is O(n), but it is okay, n stays very small (2 players)
		player = next(player);

	switch (control)
	{
	case FORWARD:
		(*player)->driveForward();
		break;
	case REVERSE:
		(*player)->driveReverse();
		break;
	case CLOCKWISE:
		(*player)->turnRight();
		break;
	case ANTI_CLOCKWISE:
		(*player)->turnLeft();
		break;
	case FIRE_ROCKET:
		if ((*player)->getHealth() > 0)
		{
			try
			{
				(*player)->fireRocket();
				shared_ptr<Rocket> rocket{new Rocket{}};
				Coordinate origin{(*player)->getCenter()};
				origin = origin + (*player)->getForward()*50.0;
				rocket->setPosition(origin);
				rocket->setDirection(-(*player)->getForward().angle() + PI);
				_rockets.push_back(rocket);
			}
			catch (Rocket_Fire_Frequency_too_High&)
			{
				//Do nothing.
				//really though, stop firing rockets for a bit.
			}
		}
		break;
	case PLANT_MINE:
		if ((*player)->getHealth() > 0)
		{
			try
			{
				(*player)->plantMine();
				shared_ptr<Mine> mine{new Mine{}};
				Coordinate origin{(*player)->getCenter()};
				origin = origin + (*player)->getForward()*-50.0;
				mine->setPosition(origin);
				_mines.push_back(mine);
			}
			catch(Mine_Plant_frequency_too_High&)
			{
				//Do Nothing
			}
			catch(Out_of_Mines&)
			{
				//Do nothing
			}
		}
		break;
	default:
		//This happens when restart is passed
		break;
	}
}

void GameLogic::updateCollisionManager()
{
	_collMan.purgeCollisions();
	_collMan.purgeObjects();

	vector<shared_ptr<GameObject>> tempGOs;

	tempGOs.push_back(_topBound);
	tempGOs.push_back(_bottomBound);
	tempGOs.push_back(_rightBound);
	tempGOs.push_back(_leftBound);

	for (auto player : _players)
		tempGOs.push_back(player);
    for (auto rocket : _rockets)
    	tempGOs.push_back(rocket);
    for (auto crate : _crates)
        tempGOs.push_back(crate);
    for (auto concrete : _concretes)
    	tempGOs.push_back(concrete);
    for (auto mine : _mines)
    	tempGOs.push_back(mine);
    for (auto turret : _turrets)
    	tempGOs.push_back(turret);

    _collMan.setGameObjecs(tempGOs);
}

void GameLogic::checkRocketDamage()
{
	for(auto rocket : _rockets)
	{
		int n = 0;
		for (auto player : _players)
		{
			n++;
			if (player->hasInside(rocket))
			{
				player->damage(51);
				rocket->kill();
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(player)->getCenter()});
				_explosion01s.push_back(expl01);
				if (player->getHealth() <= 0)
				{
					player->kill();
					switch (n)
					{
					case 1:
						_p2Score++;
						break;
					case 2:
						_p1Score++;
						break;
					}
				}
				return;
			}
		}
		for (auto crate : _crates)
		{
			if (crate->hasInside(rocket))
			{
				crate->damage(51);
				if (crate->getHealth() <= 0)
					crate->kill();
				return;
			}
		}
		for (auto concrete : _concretes)
		{
			if (concrete->hasInside(rocket))
			{
				concrete->damage(34);
				if (concrete->getHealth() <= 0)
					concrete->kill();
				return;
			}
		}
		for (auto turret : _turrets)
		{
			if (turret->hasInside(rocket))
			{
				rocket->kill();
				turret->damage(51);
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(turret)->getCenter()});
				_explosion01s.push_back(expl01);
				if (turret->getHealth() <= 0)
					turret->kill();
				return;
			}
		}
	}
}

void GameLogic::checkMineDamage()
{
	for (auto mine : _mines)
	{
		int n =0;
		for (auto player : _players)
		{
			n++;
			if (player->hasInside(mine))
			{
				player->damage(51);
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(player)->getCenter()});
				_explosion01s.push_back(expl01);
				if (player->getHealth() <=0)
				{
					player->kill();
					switch (n)
					{
					case 1:
						_p2Score++;
						break;
					case 2:
						_p1Score++;
						break;
					}
				}
				mine->kill();
			}
		}

		for (auto crate : _crates)
			if (crate->hasInside(mine))
			{
				crate->damage(35);
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(crate)->getCenter()});
				_explosion01s.push_back(expl01);
				if (crate->getHealth() <=0)
					crate->kill();
				mine->kill();
			}

		for (auto rocket : _rockets)
			if (rocket->hasInside(mine))
			{
				rocket->kill();
				mine->kill();
			}
	}
}

void GameLogic::checkTimedDeath()
{
	auto n = _explosion01s.begin();
	while (n != _explosion01s.end())
	{
		if ((*n)->getBirthTime() + (*n)->getLifeTime() < clock()/CLOCKS_PER_SEC)
			n = _explosion01s.erase(n);
		else
			++n;
	}

	if (getRemainingTime() < 0 && getWinner() == 0)
	{
		for (auto tank : _players)
		{
			if (!isDead(tank))
			{
				tank->kill();
				shared_ptr<GameObject> expl01{new GameObject{1}};
				expl01->setPosition(Coordinate{(tank)->getCenter()});
				_explosion01s.push_back(expl01);
			}
		}
	}
}


void GameLogic::checkHealthDeath()
{
	auto rocket = _rockets.begin();
	while (rocket != _rockets.end())
	{
		if (isDead(*rocket))
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(*rocket)->getCenter()});
			_explosion01s.push_back(expl01);
			rocket = _rockets.erase(rocket);
		}
		else
			++rocket;
	}

	auto crate = _crates.begin();
	while (crate != _crates.end())
	{
		if (isDead(*crate))
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(*crate)->getCenter()});
			_explosion01s.push_back(expl01);
			crate = _crates.erase(crate);
		}
		else
			++crate;
	}

	auto concrete = _concretes.begin();
	while (concrete != _concretes.end())
	{
		if (isDead(*concrete))
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(*concrete)->getCenter()});
			_explosion01s.push_back(expl01);
			concrete = _concretes.erase(concrete);
		}
		else
			++concrete;
	}

	auto mine = _mines.begin();
	while (mine != _mines.end())
	{
		if (isDead(*mine))
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{(*mine)->getCenter()});
			_explosion01s.push_back(expl01);
			mine = _mines.erase(mine);
		}
		else
			++mine;
	}
}

void GameLogic::loadLevel()
{
	buildConcrete(Coordinate{633, 282},0);
	buildConcrete(Coordinate{683, 232},0);
	buildConcrete(Coordinate{733, 282},0);

	buildConcrete(Coordinate{633, 423},PI);
	buildConcrete(Coordinate{683, 473},PI);
	buildConcrete(Coordinate{733, 423},PI);

	buildCrate(Coordinate{683, 352},false);

	buildConcrete(Coordinate{341,352},PI/2);
	buildConcrete(Coordinate{396,252},PI/4);
	buildConcrete(Coordinate{396,452},-PI/4);

	buildConcrete(Coordinate{1030,352},-PI/2);
	buildConcrete(Coordinate{978,252},-PI/4);
	buildConcrete(Coordinate{978,452},PI/4);

	buildTank(Coordinate{1225,315});
	buildTank(Coordinate{105,315});


	buildTurret(Coordinate{683,141});
	buildTurret(Coordinate{683,564});

	loadBoundary(_hres, _vres);

	_startTime = clock()/CLOCKS_PER_SEC;
}

void GameLogic::loadBoundary(const int hres, const int vres)
{
	_topBound = shared_ptr<Boundary>{new Boundary{hres, vres, NORTH}};
	_bottomBound = shared_ptr<Boundary>{new Boundary{hres, vres, SOUTH}};
	_leftBound = shared_ptr<Boundary>{new Boundary{hres, vres, WEST}};
	_rightBound = shared_ptr<Boundary>{new Boundary{hres, vres, EAST}};
}

int GameLogic::numObjects() const
{
	int total = 0;
	total += _players.size();
	total += _rockets.size();
	total += _crates.size();
	total += _explosion01s.size();
	total += _mines.size();
	total += _turrets.size();
	total += _concretes.size();

	return total;
}

void GameLogic::turretAction()
{
	vector<Coordinate> targets;
	for (auto player : _players)
		targets.push_back(player->getCenter());

	for (auto turret : _turrets)
	{
		turret->setTargets(targets);
		if (turret->getHealth() >0)
			if (turret->aim())
			{
				try
				{
					turret->fireRocket();
					shared_ptr<Rocket> rocket{new Rocket{}};
					Coordinate origin{turret->getCenter()};
					origin = origin + turret->getForward()*50.0;
					rocket->setPosition(origin);
					rocket->setDirection(-turret->getForward().angle() + PI);
					_rockets.push_back(rocket);
				}
				catch (Rocket_Fire_Frequency_too_High&)
				{
					//do nothing
				}
			}
	}
}

bool GameLogic::isDead(const shared_ptr<GameObject>& a)
{
	if (a->getHealth() <= 0)
		return true;
	return false;
}

void GameLogic::animate(const float time)
{
	for (auto player : _players)
		player->animate(time);
	for (auto rocket : _rockets)
		rocket->animate(time);
	for (auto crate : _crates)
		crate->animate(time);
	for (auto turret : _turrets)
		turret->animate(time);
}

void GameLogic::clearForces()
{
	for (auto player : _players)
		player->clearForce();
	for (auto rocket : _rockets)
		rocket->clearForce();
	for (auto crate : _crates)
		crate->clearForce();
	for (auto turret : _turrets)
		turret->clearForce();
}

void GameLogic::buildCrate(const Coordinate pos, const bool glued)
{
	shared_ptr<Crate> c1(new Crate{});
	c1->setPosition(pos);
	if (glued)
		c1->glue();
	_crates.push_back(c1);
}

void GameLogic::buildConcrete(const Coordinate pos, const float angle)
{
	shared_ptr<Concrete> c1(new Concrete{});
	c1->setPosition(pos);
	c1->rotate(angle);
	_concretes.push_back(c1);
}

void GameLogic::buildTank(const Coordinate pos)
{
	shared_ptr<Tank> t{new Tank{}};
	t->setPosition(pos);
	_players.push_back(t);
}

void GameLogic::buildTurret(const Coordinate pos)
{
	shared_ptr<Turret> t{new Turret{}};
	t->setPosition(pos);
	_turrets.push_back(t);
}

float GameLogic::getRemainingTime()
{
	float time = clock()/CLOCKS_PER_SEC;
	return _roundTime -(time -_startTime);
}

int GameLogic::getScorer()
{

		int playersAlive = 0;
		int winner = 0;
		int player = 0;
		for (auto tank : _players)
		{
			player++;
			if (!isDead(tank))
			{
				winner = player;
				playersAlive++;
			}
		}
		if (playersAlive == 1)
		{
			//endGame();
			return winner;
		}
	return 0;
}

void GameLogic::endGame()
{
	_startTime = clock()/CLOCKS_PER_SEC - _roundTime;
}

void GameLogic::setResolution(const int hres, const int vres)
{
	_hres = hres;
	_vres = vres;
}

void GameLogic::resetPlayers()
{
	int n = 1;
	for (auto player : _players)
	{
		switch (n)
		{
		case 1:
			player->setPosition(Coordinate{1225,315});
			player->revive();
			break;
		case 2:
			player->setPosition(Coordinate{105,315});
			player->revive();
			break;
		}
		n++;
	}
}

string GameLogic::getScore(const int player)
{
	if (player == 1)
	{
		std::ostringstream ss;
		ss << _p1Score;
		return ss.str();
	}
	else if (player == 2)
	{
		std::ostringstream ss;
		ss << _p2Score;
		return ss.str();
	}

	return "0";
}

int GameLogic::getWinner()
{
	if (_p1Score > _p2Score)
		return 1;
	else if (_p1Score < _p2Score)
		return 2;

	return 0;
}
