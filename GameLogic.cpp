/*
 * GameLogic.cpp
 *
 */

#include "GameLogic.h"

GameLogic::GameLogic()
{
	//all this must be done by a level loading function
	_player1->Update();
	_player2->changePosition(300,100);
	_player2->Update();


	_immovableCrates.push_back(shared_ptr<SGSImmovableCrate>{new SGSImmovableCrate{}});
	_immovableCrates[0]->changePosition(500,500);
}

GameLogic::~GameLogic() {}

void GameLogic::step()
{
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
	float hres = 1300;
	float vres = 700;
    sf::RenderWindow window(sf::VideoMode(hres, vres), "Tanks!");

    while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            checkPlayerDeath();
            step();

            sf::VertexArray p1box(sf::LinesStrip, 4);
            p1box[0].position = sf::Vector2f(_player1->_object->getTriangles()[0].getCoordinate(0)->x(), _player1->_object->getTriangles()[0].getCoordinate(0)->y());
            p1box[1].position = sf::Vector2f(_player1->_object->getTriangles()[0].getCoordinate(1)->x(), _player1->_object->getTriangles()[0].getCoordinate(1)->y());
            p1box[2].position = sf::Vector2f(_player1->_object->getTriangles()[0].getCoordinate(2)->x(), _player1->_object->getTriangles()[0].getCoordinate(2)->y());
            p1box[3].position = sf::Vector2f(_player1->_object->getTriangles()[0].getCoordinate(0)->x(), _player1->_object->getTriangles()[0].getCoordinate(0)->y());

            sf::VertexArray p2box(sf::LinesStrip, 4);
			p2box[0].position = sf::Vector2f(_player2->_object->getTriangles()[0].getCoordinate(0)->x(), _player2->_object->getTriangles()[0].getCoordinate(0)->y());
			p2box[1].position = sf::Vector2f(_player2->_object->getTriangles()[0].getCoordinate(1)->x(), _player2->_object->getTriangles()[0].getCoordinate(1)->y());
			p2box[2].position = sf::Vector2f(_player2->_object->getTriangles()[0].getCoordinate(2)->x(), _player2->_object->getTriangles()[0].getCoordinate(2)->y());
			p2box[3].position = sf::Vector2f(_player2->_object->getTriangles()[0].getCoordinate(0)->x(), _player2->_object->getTriangles()[0].getCoordinate(0)->y());

            window.clear();
            window.draw(*_player1);
            window.draw(*_player2);
            window.draw(p1box);
            window.draw(p2box);
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
