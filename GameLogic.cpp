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
	_stepTime = time;
	controllerInput();
	updateCollisionManager();
	_collMan.findCollisions();
	_collMan.ResolveCollisions();
	_collMan.purgeCollisions();

	for (auto player : _players)
	{
		player->animate(_stepTime);
		player->Update();
	}
	for (auto rocket : _rockets)
	{
		rocket->animate(_stepTime);
		rocket->Update();
	}
	for (auto crate : _immovableCrates)
	{
		crate->animate(_stepTime);
		crate->Update();
	}

}

void GameLogic::controllerInput()
{
	//----P1
	shared_ptr<SGSTank> player1 = (*_players.begin());
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		player1->_object->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		player1->_object->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player1->_object->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player1->_object->turnLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		if (clock()/CLOCKS_PER_SEC - p1FireTime >= FireTime)
		{
			shared_ptr<SGSRocket> rocket{new SGSRocket{}};
			Coordinate origin{player1->_object->getCenter()};
			origin = origin + player1->_object->getForward()*50.0;
			rocket->changePosition(origin.x(), origin.y());
			rocket->setDirection(-player1->_object->getForward().angle() + PI);
			_rockets.push_back(rocket);
			p1FireTime = clock()/CLOCKS_PER_SEC;
		}
	}

	//---P2
	shared_ptr<SGSTank> player2 = (*next(_players.begin()));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player2->_object->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player2->_object->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player2->_object->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player2->_object->turnLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (clock()/CLOCKS_PER_SEC - p2FireTime >= FireTime)
		{
			shared_ptr<SGSRocket> rocket{new SGSRocket{}};
			Coordinate origin{player2->_object->getCenter()};
			origin = origin + player2->_object->getForward()*50.0;
			rocket->changePosition(origin.x(), origin.y());
			rocket->setDirection(-player2->_object->getForward().angle() + PI);
			_rockets.push_back(rocket);
			p2FireTime = clock()/CLOCKS_PER_SEC;
		}
	}
}

void GameLogic::coreLoop()
{

    sf::RenderWindow window(sf::VideoMode(_hres, _vres), "Tanks!");

    while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            checkPlayerDeath();
            step(0.002);


            window.clear();

            for (auto player : _players)
            	window.draw(*player);
            for (auto rocket : _rockets)
            	window.draw(*rocket);
            for (auto crate : _immovableCrates)
            	window.draw(*crate);

            window.display();
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
		tempGOs.push_back(player->_object);
    for (auto rocket : _rockets)
    	tempGOs.push_back(rocket->_object);
    for (auto crate : _immovableCrates)
    	tempGOs.push_back(crate->_object);

    _collMan.setGameObjecs(tempGOs);
}

void GameLogic::checkPlayerDeath()
{
	for(auto rocket : _rockets)
	{
		for (auto player : _players)
		{
			if (player->_object->hasInside(rocket->_object))
			{
				player->_texture.loadFromFile("explosion.png", sf::IntRect(0, 0, 100,100));;
				player->setTexture(player->_texture, true);
				player->setOrigin(50,50);
				_rockets.remove(rocket); //TODO place explosion
				return;
			}

		}
	}
}

void GameLogic::loadLevel()
{
	shared_ptr<SGSTank> p1{new SGSTank{}};
	shared_ptr<SGSTank> p2{new SGSTank{}};

	p1->changePosition(1200,350);
	p1->Update();
	p2->changePosition(100,350);
	p2->Update();

	_players.push_back(p1);
	_players.push_back(p2);

	loadBoundary(_hres, _vres);
}

void GameLogic::loadBoundary(const int hres, const int vres)
{
	_topBound = shared_ptr<Boundary>{new Boundary{hres, vres, NORTH}};
	_bottomBound = shared_ptr<Boundary>{new Boundary{hres, vres, SOUTH}};
	_leftBound = shared_ptr<Boundary>{new Boundary{hres, vres, WEST}};
	_rightBound = shared_ptr<Boundary>{new Boundary{hres, vres, EAST}};
}
