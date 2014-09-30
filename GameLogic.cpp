/*
 * GameLogic.cpp
 *
 */

#include "GameLogic.h"

GameLogic::GameLogic()
{
	loadLevel();
}

GameLogic::~GameLogic() {}

void GameLogic::step(const float time)
{
	checkRocketDamage();
	checkMineDamage();
	checkTimedDeath();

	updateCollisionManager();
	_collMan.findCollisions();
	_collMan.ResolveCollisions();
	_collMan.purgeCollisions();

	for (auto player : _players)
		player->animate(time);
	for (auto rocket : _rockets)
		rocket->animate(time);
	for (auto crate : _immovableCrates)
		crate->animate(time);
	for (auto crate : _crates)
		crate->animate(time);

	checkHealthDeath();

}

void GameLogic::playControl(const playerControl& control, const int& playerNo)
{
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
		break;
	case PLANT_MINE:
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
		break;
	default:
		//This should not happen
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
    for (auto crate : _immovableCrates)
    	tempGOs.push_back(crate);
    for (auto crate : _crates)
        tempGOs.push_back(crate);
    for (auto mine : _mines)
    	tempGOs.push_back(mine);

    _collMan.setGameObjecs(tempGOs);
}

void GameLogic::checkRocketDamage()
{
	for(auto rocket : _rockets)
	{
		for (auto player : _players)
		{
			if (player->hasInside(rocket))
			{
				player->kill();
				rocket->kill();
				return;
			}
		}
		for (auto crate : _crates)
		{
			if (crate->hasInside(rocket))
			{
				crate->damage(34);
				if (crate->getHealth() <= 0)
				{
					crate->kill();
				}

				return;
			}
		}
	}
}

void GameLogic::checkMineDamage()
{
	for (auto mine : _mines)
	{
		for (auto player : _players)
			if (player->hasInside(mine))
			{
				player->damage(50);
				if (player->getHealth() <=0)
					player->kill();
			}

		for (auto crate : _crates)
			if (crate->hasInside(mine))
			{
				crate->damage(50);
				if (crate->getHealth() <=0)
					crate->kill();
			}

		for (auto rocket : _rockets)
			if (rocket->hasInside(mine))
				rocket->kill();
	}
}

void GameLogic::checkTimedDeath()
{
	for (auto rocket : _rockets)
	{
		if (rocket->getBirthTime() + rocket->getLifeTime() < clock()/CLOCKS_PER_SEC ||
			rocket->getHealth() <= 0)
			rocket->kill();
	}

	for (auto expl01 : _explosion01s)
	{
		if (expl01->getBirthTime() + expl01->getLifeTime() < clock()/CLOCKS_PER_SEC ||
			expl01->getHealth() <= 0)
			_explosion01s.remove(expl01);
	}
}


void GameLogic::checkHealthDeath()
{
	for (auto rocket : _rockets)
		if (rocket->getHealth() <= 0)
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(Coordinate{rocket->getCenter()});
			_explosion01s.push_back(expl01);
			_rockets.remove(rocket);
		}

	for (auto crate : _crates)
		if (crate->getHealth() <= 0)
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(crate->getCenter());
			_explosion01s.push_back(expl01);
			_crates.remove(crate);
		}

	for (auto mine : _mines)
		if (mine->getHealth() <= 0)
		{
			shared_ptr<GameObject> expl01{new GameObject{1}};
			expl01->setPosition(mine->getCenter());
			_explosion01s.push_back(expl01);
			_mines.remove(mine);
		}
}

void GameLogic::loadLevel()
{
	shared_ptr<Tank> p1{new Tank{}};
	shared_ptr<Tank> p2{new Tank{}};
	p1->setPosition(Coordinate{1200,350});// TODO magic numbers
	p2->setPosition(Coordinate{100,350});
	_players.push_back(p1);
	_players.push_back(p2);

	shared_ptr<Crate> c1{new Crate{}};
	c1->setPosition(Coordinate{500,500});
	_crates.push_back(c1);

	loadBoundary(_hres, _vres);
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
	total += _immovableCrates.size();
	total += _crates.size();
	total += _explosion01s.size();
	total += _mines.size();

	return total;
}
