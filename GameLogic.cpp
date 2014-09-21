/*
 * GameLogic.cpp
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#include "GameLogic.h"

void GameLogic::setSfmlGameObjects(const vector<shared_ptr<SfmlGameSprite>>& sfmlGameObjects)
{
	_sfmlGameObjects = sfmlGameObjects;
	for(auto obj : _sfmlGameObjects)
	{
		_gameObjects.push_back(obj->_object);
	}
	_collMan.setGameObjecs(_gameObjects);
}

void GameLogic::setPlayers(const shared_ptr<SGSTank>& player1, const shared_ptr<SGSTank> player2)
{
	_player1 = player1->_object;
	_player2 = player2->_object;
}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stud
}

void GameLogic::controlInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_player1->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_player1->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_player1->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_player1->turnLeft();
}

void GameLogic::animate(const float& stepTime)
{
	for (auto obj : _gameObjects)
	{
		obj->animate(stepTime);
	}
}

void GameLogic::step(float const& stepTime)
{
	controlInput();
	_collMan.findCollisions();
	if (_collMan.numCollisions() > 0)
	{
		_collMan.ResolveCollisions();
	}
	animate(stepTime);
	for (auto SFObj : _sfmlGameObjects)
	{
		SFObj->Update();
	}
}

