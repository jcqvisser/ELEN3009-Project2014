/*
 * GameLoop.h
 *
 *  Created on: 08 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMELOOP_H_
#define GAMELOOP_H_
#include "GameObject.h"
#include <SFML/Window/Keyboard.hpp>

//Exception classes
class Time_must_be_positive_and_non_zero{};


class GameLoop {
public:
	GameLoop();
	virtual ~GameLoop();
	void addObject(const std::shared_ptr<GameObject> obj);
	void addPlayer(const std::shared_ptr<GameObject> obj);
	void logic();
	void loop();
	void draw();
	void setStepTime(const float& time);
	float _stepTime = 0.02; //sec
private:
	sf::RenderWindow _window{sf::VideoMode(1000,500), "Project Test 07"};
	std::vector<std::shared_ptr<GameObject>> _objects;
	std::vector<std::shared_ptr<GameObject>> _players;
};

#endif /* GAMELOOP_H_ */
