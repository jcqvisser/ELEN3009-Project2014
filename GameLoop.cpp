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

void GameLoop::setStepTime(const float& time)
{
	if (time > 0)
		_stepTime = time;
	else
		throw Time_must_be_positive_and_non_zero{};
}

void GameLoop::logic()
{
	//check keypresses
	//apply keypress actions

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		float x = _objects[0]->getPosition().x;
		float y = _objects[0]->getPosition().y;
		_objects[0]->setPosition(x+1,y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		float x = _objects[0]->getPosition().x;
		float y = _objects[0]->getPosition().y;
		_objects[0]->setPosition(x-1,y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		float x = _objects[0]->getPosition().x;
		float y = _objects[0]->getPosition().y;
		_objects[0]->setPosition(x,y+1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		float x = _objects[0]->getPosition().x;
		float y = _objects[0]->getPosition().y;
		_objects[0]->setPosition(x,y-1);
	}


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
}
