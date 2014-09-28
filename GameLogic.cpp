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
	_player1->animate(_stepTime);
	_player2->animate(_stepTime);
	_player1->Update();
	_player2->Update();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_player1->_object->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_player1->_object->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_player1->_object->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_player1->_object->turnLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		if (clock.getElapsedTime() - p1FireTime >= FireTime)
		{
			shared_ptr<SGSRocket> rocket{new SGSRocket{}};
			Coordinate origin{_player1->_object->getCenter()};
			origin = origin + _player1->_object->getForward()*50.0;
			rocket->changePosition(origin.x(), origin.y());
			rocket->setDirection(-_player1->_object->getForward().angle() + PI);
			_rockets.push_back(rocket);
			p1FireTime = clock.getElapsedTime();
		}
	}

	//---P2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_player2->_object->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_player2->_object->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_player2->_object->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_player2->_object->turnLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (clock.getElapsedTime() - p2FireTime >= FireTime)
		{
			shared_ptr<SGSRocket> rocket{new SGSRocket{}};
			Coordinate origin{_player2->_object->getCenter()};
			origin = origin + _player2->_object->getForward()*50.0;
			rocket->changePosition(origin.x(), origin.y());
			rocket->setDirection(-_player2->_object->getForward().angle() + PI);
			_rockets.push_back(rocket);
			p2FireTime = clock.getElapsedTime();
		}
	}
}

void GameLogic::coreLoop()
{

    sf::RenderWindow window(sf::VideoMode(_hres, _vres), "Tanks!");
    sf::Time t1 = clock.getElapsedTime();
    sf::Time t2;

    while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            t2 = clock.getElapsedTime();
            float t3 = t2.asSeconds() - t1.asSeconds();
            checkPlayerDeath();
            step(t3);
            t1 = t2;


            window.clear();
            window.draw(*_player1);
            window.draw(*_player2);
            for (auto rocket : _rockets)
            {
            	window.draw(*rocket);
            }
            for (auto crate : _immovableCrates)
            {
            	window.draw(*crate);
            }
            window.display();
        }
}

void GameLogic::updateCollisionManager()
{
	_collMan.purgeCollisions();
	_collMan.purgeObjects();

	vector<shared_ptr<GameObject>> tempGOs;

	tempGOs.push_back(_player1->_object);
	tempGOs.push_back(_player2->_object);
	tempGOs.push_back(_topBound);
	tempGOs.push_back(_bottomBound);
	tempGOs.push_back(_rightBound);
	tempGOs.push_back(_leftBound);

    for (auto rocket : _rockets)
    {
    	tempGOs.push_back(rocket->_object);
    }
    for (auto crate : _immovableCrates)
    {
    	tempGOs.push_back(crate->_object);
    }
    _collMan.setGameObjecs(tempGOs);
}

void GameLogic::checkPlayerDeath()
{
	for(auto rocket : _rockets)
	{
		if (_player1->_object->hasInside(rocket->_object))
		{
			_player1->_texture.loadFromFile("explosion.png", sf::IntRect(0, 0, 100,100));
			_player1->setOrigin(50,50);
			_player1->setTexture(_player1->_texture, true);
			return;
		}

		if (_player2->_object->hasInside(rocket->_object))
		{
			_player2->_texture.loadFromFile("explosion.png", sf::IntRect(0,0,100,100));
			_player2->setTexture(_player2->_texture, true);
			_player2->setOrigin(50,50);
			return;
		}
	}
}

void GameLogic::loadLevel()
{
	_player1->changePosition(100,350);
	_player2->changePosition(1200,350);
	_player1->Update();
	_player2->Update();

	loadBoundary(_hres, _vres);
}

void GameLogic::loadBoundary(const int hres, const int vres)
{
	_topBound = shared_ptr<Boundary>{new Boundary{hres, vres, NORTH}};
	_bottomBound = shared_ptr<Boundary>{new Boundary{hres, vres, SOUTH}};
	_leftBound = shared_ptr<Boundary>{new Boundary{hres, vres, WEST}};
	_rightBound = shared_ptr<Boundary>{new Boundary{hres, vres, EAST}};
}
