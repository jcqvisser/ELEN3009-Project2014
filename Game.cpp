/*
 * Game.cpp
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#include "Game.h"

Game::Game() {

	_player1 = shared_ptr<SGSTank>{new SGSTank{}};
	_player2 = shared_ptr<SGSTank>{new SGSTank{}};
	_gameObjects.push_back(_player1);
	_gameObjects.push_back(_player2);
	_logic.setSfmlGameObjects(_gameObjects);
	_logic.setPlayers(_player1, _player2);
}

Game::~Game() {
	// TODO Auto-generated destructor stub
}

void Game::draw()
{
	for (auto SFObj : _gameObjects)
	{
		window.draw(*SFObj);
	}
}

void Game::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();//fdsa
        }

        _logic.step(_stepTime);
        window.clear();
        draw();
        window.display();
    }
}

