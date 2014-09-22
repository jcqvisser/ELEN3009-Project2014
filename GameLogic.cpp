/*
 * GameLogic.cpp
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */

#include "GameLogic.h"

GameLogic::GameLogic(const shared_ptr<SGSTank>& player1,
		const shared_ptr<SGSTank>& player2) :
	_player1(player1),
	_player2(player2)
{
	shared_ptr<GameObject> p1 = _player1->_object;
	shared_ptr<GameObject> p2 = _player2->_object;

	vector<shared_ptr<GameObject>> temp;
	temp.push_back(p1);
	temp.push_back(p2);

	_collMan.setGameObjecs(temp);
}

GameLogic::~GameLogic() {}

void GameLogic::step()
{
	controllerInput();
	_collMan.findCollisions();
	_collMan.ResolveCollisions();
	_collMan.purgeCollisions();
	_player1->animate(0.1);
	_player2->animate(0.1);
	_player1->Update();
	_player2->Update();
}

void GameLogic::controllerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_player1->_object->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_player1->_object->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_player1->_object->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_player1->_object->turnLeft();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_player2->_object->driveForward();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_player2->_object->driveReverse();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_player2->_object->turnRight();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_player2->_object->turnLeft();
}
