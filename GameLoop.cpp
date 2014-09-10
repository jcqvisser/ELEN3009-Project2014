/*
 * GameLoop.cpp
 *
 *  Created on: 08 Sep 2014
 *      Author: Jacques
 */

#include "GameLoop.h"

GameLoop::GameLoop(){}

GameLoop::~GameLoop(){}

void GameLoop::addObject(const std::shared_ptr<GameObject> obj)
{	_objects.push_back(obj);}

void GameLoop::addPlayer(const std::shared_ptr<GameObject> obj)
{	_players.push_back(obj);}

void GameLoop::setStepTime(const float& time)
{
	if (time > 0)
		_stepTime = time;
	else
		throw Time_must_be_positive_and_non_zero{};
}

void GameLoop::logic()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//move P1 back
		VectorQuantity backForce{0, 100};
		_players[0]->applyForce(backForce);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//move P1 back
		VectorQuantity backForce{0, -100};
		_players[0]->applyForce(backForce);
	}
	_players[0]->animate(_stepTime);
}

void GameLoop::loop()
{
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();//fdsa
        }

        _window.clear();
        logic();
        draw();
        _window.display();
    }
}

void GameLoop::draw()
{
	for (auto obj : _objects)
	{
		_window.draw(*obj);
	}

	for (auto obj : _players)
	{
		_window.draw(*obj);
	}
}