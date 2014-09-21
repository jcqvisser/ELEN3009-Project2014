/*
 * GameLogic.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "SGSTank.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

class GameLogic {
public:
	GameLogic() {};
	void setSfmlGameObjects(const vector<shared_ptr<SfmlGameSprite>>& SfmlGameObjects);
	void setPlayers(const shared_ptr<SGSTank>& player1, const shared_ptr<SGSTank> player2);
	virtual ~GameLogic();
	void animate(const float& stepTime);
	void step(const float& stepTime);
private:
	void controlInput();
	shared_ptr<Tank> _player1;
	shared_ptr<Tank> _player2;
	vector<shared_ptr<SfmlGameSprite>> _sfmlGameObjects;
	vector<shared_ptr<GameObject>> _gameObjects;
	CollisionManager _collMan;
};

#endif /* GAMELOGIC_H_ */
