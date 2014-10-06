#include "SfmlInterface.h"


SfmlInterface::SfmlInterface(const float& hres, const float& vres) :
	_hres(hres),
	_vres(vres),
	_window(sf::VideoMode(hres, vres), "Tanks!")
{
	_tankTexture.setSmooth(true);
	_tankTexture.loadFromFile("tank.png", sf::IntRect(0, 0, 50, 50));

	_tank2Texture.setSmooth(true);
	_tank2Texture.loadFromFile("tank2.png", sf::IntRect(0, 0, 50, 50));

	_rocketTexture.setSmooth(true);
	_rocketTexture.loadFromFile("rocket.png", sf::IntRect(0,0, 10,34));

	_explosionTexture01.setSmooth(true);
	_explosionTexture01.loadFromFile("explosion01.png",  sf::IntRect(0, 0, 100,100));

	_crateTexture.setSmooth(true);
	_crateTexture.loadFromFile("crate.png", sf::IntRect(0, 0, 60, 60));

	_mineTexture.setSmooth(true);
	_mineTexture.loadFromFile("mine.png", sf::IntRect(0, 0, 20,20));

	_turretTexture.setSmooth(true);
	_turretTexture.loadFromFile("turret.png", sf::IntRect(0, 0, 50, 50));

	_turretDeadTexture.setSmooth(true);
	_turretDeadTexture.loadFromFile("turret_dead.png", sf::IntRect(0, 0, 50, 50));

	_tankDeadTexture.setSmooth(true);
	_tankDeadTexture.loadFromFile("tank_dead.png", sf::IntRect(0, 0, 50, 50));

	_tank2DeadTexture.setSmooth(true);
	_tank2DeadTexture.loadFromFile("tank2_dead.png", sf::IntRect(0, 0, 50, 50));

	_concrete1Texture.setSmooth(true);
	_concrete1Texture.loadFromFile("concrete1.png", sf::IntRect(0, 0, 100, 50));

	_concrete2Texture.setSmooth(true);
	_concrete2Texture.loadFromFile("concrete2.png", sf::IntRect(0, 0, 100, 50));

	_concrete3Texture.setSmooth(true);
	_concrete3Texture.loadFromFile("concrete3.png", sf::IntRect(0, 0, 100, 50));

	_background.setSmooth(true);
	_background.loadFromFile("grass.png", sf::IntRect(0, 0, 1366, 705));
	_backSprite.setTexture(_background,true);
	_backSprite.setOrigin(683,353);
	_backSprite.setPosition(683,353);

	_font.loadFromFile("OpenSans-Bold.ttf");
	_timeRemaingText.setFont(_font);
	_p1Win.setFont(_font);
	_p2Win.setFont(_font);
	_timeUp.setFont(_font);
	_p1Score.setFont(_font);
	_p2Score.setFont(_font);
	_p1Scores.setFont(_font);
	_p2Scores.setFont(_font);
	_noWin.setFont(_font);

	_timeRemaingText.setCharacterSize(30);
	_timeRemaingText.setPosition(683,30);
	_timeRemaingText.setColor(Color::Black);

	_noWin.setCharacterSize(50);
	_noWin.setString("Nobody Wins!");
	_noWin.setOrigin(_noWin.getLocalBounds().left +
			_noWin.getLocalBounds().width/2,
			_noWin.getLocalBounds().top  +
			_noWin.getLocalBounds().height/2);
	_noWin.setPosition(_hres/2,_vres/2);
	_noWin.setColor(Color::Black);

	_p1Win.setCharacterSize(50);
	_p1Win.setString("Red Wins!");
	_p1Win.setOrigin(_p1Win.getLocalBounds().left +
			_p1Win.getLocalBounds().width/2,
			_p1Win.getLocalBounds().top  +
			_p1Win.getLocalBounds().height/2);
	_p1Win.setPosition(_hres/2,_vres/2);
	_p1Win.setColor(Color::Black);

	_p1Scores.setCharacterSize(50);
	_p1Scores.setString("Red Scores!");
	_p1Scores.setOrigin(_p1Win.getLocalBounds().left +
			_p1Scores.getLocalBounds().width/2,
			_p1Scores.getLocalBounds().top  +
			_p1Scores.getLocalBounds().height/2);
	_p1Scores.setPosition(_hres/2,_vres/2);
	_p1Scores.setColor(Color::Black);

	_p2Win.setCharacterSize(50);
	_p2Win.setString(" Purple Wins!");
	_p2Win.setOrigin(_p2Win.getLocalBounds().left +
			_p2Win.getLocalBounds().width/2,
			_p2Win.getLocalBounds().top  +
			_p2Win.getLocalBounds().height/2);
	_p2Win.setPosition(_hres/2,_vres/2);
	_p2Win.setColor(Color::Black);

	_p2Scores.setCharacterSize(50);
	_p2Scores.setString(" Purple Scores!");
	_p2Scores.setOrigin(_p2Win.getLocalBounds().left +
			_p2Scores.getLocalBounds().width/2,
			_p2Scores.getLocalBounds().top  +
			_p2Scores.getLocalBounds().height/2);
	_p2Scores.setPosition(_hres/2,_vres/2);
	_p2Scores.setColor(Color::Black);

	_timeUp.setCharacterSize(50);
	_timeUp.setString("Time is Up!");
	_timeUp.setOrigin(_p2Win.getLocalBounds().left +
			_timeUp.getLocalBounds().width/2,
			_timeUp.getLocalBounds().top  +
			_timeUp.getLocalBounds().height/2);
	_timeUp.setPosition(_hres/2,_vres/2+300);
	_timeUp.setColor(Color::Black);


	_p1Score.setCharacterSize(30);
	_p1Score.setString(_gameLogic.getScore(1));
	_p1Score.setOrigin(_p1Score.getLocalBounds().left +
			_p1Score.getLocalBounds().width/2,
			_p1Score.getLocalBounds().top  +
			_p1Score.getLocalBounds().height/2);
	_p1Score.setPosition(3*_hres/4,30);
	_p1Score.setColor(Color::Black);

	_p2Score.setCharacterSize(30);
	_p2Score.setString(_gameLogic.getScore(2));
	_p2Score.setOrigin(_p2Score.getLocalBounds().left +
			_p2Score.getLocalBounds().width/2,
			_p2Score.getLocalBounds().top  +
			_p2Score.getLocalBounds().height/2);
	_p2Score.setPosition(_hres/4,30);
	_p2Score.setColor(Color::Black);


	_gameLogic.setResolution(_hres, _vres);
	_gameLogic.loadLevel();

}

SfmlInterface::~SfmlInterface() {}

void SfmlInterface::updateSprites()
{
	_sprites.resize(_gameLogic.numObjects(), Sprite{});

	unsigned int n = 0;
	for (auto tank : _gameLogic._players)
	{
		_sprites[n].setPosition(tank->getCenter().x(), tank->getCenter().y());
		_sprites[n].setRotation(tank->getRotation()*180/PI+90);
		if (n==0)
		{

			if (tank->getHealth() > 0)
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tankTexture,true);
			}
			else
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tankDeadTexture,true);
			}
		}
		else
		{
			if (tank->getHealth() > 0)
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tank2Texture,true);
			}
			else
			{
				_sprites[n].setOrigin(25,25);
				_sprites[n].setTexture(_tank2DeadTexture,true);
			}
		}

		n++;
	}

	for (auto rocket : _gameLogic._rockets)
	{
		_sprites[n].setPosition(rocket->getCenter().x(), rocket->getCenter().y());
		_sprites[n].setRotation(rocket->getRotation()*180/PI+90);
		_sprites[n].setOrigin(5,17);
		_sprites[n].setTexture(_rocketTexture,true);
		n++;
	}

	for (auto crate : _gameLogic._crates)
	{
		_sprites[n].setPosition(crate->getCenter().x(), crate->getCenter().y());
		_sprites[n].setRotation(crate->getRotation()*180/PI+90);
		_sprites[n].setOrigin(30,30);
		_sprites[n].setTexture(_crateTexture,true);
		n++;
	}

	for (auto concrete : _gameLogic._concretes)
	{
		_sprites[n].setPosition(concrete->getCenter().x(), concrete->getCenter().y());
		_sprites[n].setRotation(concrete->getRotation()*180/PI+90);
		_sprites[n].setOrigin(50,25);

		if (concrete->getHealth() > 270)
			_sprites[n].setTexture(_concrete1Texture,true);
		else if (concrete->getHealth() > 100)
			_sprites[n].setTexture(_concrete2Texture,true);
		else if (concrete->getHealth() > 0)
			_sprites[n].setTexture(_concrete3Texture,true);
		n++;
	}

	for (auto explosion01 : _gameLogic._explosion01s)
	{
		_sprites[n].setPosition(explosion01->getCenter().x(), explosion01->getCenter().y());
		_sprites[n].setOrigin(20,40);
		_sprites[n].setTexture(_explosionTexture01,true);
		n++;
	}

	for (auto mine : _gameLogic._mines)
	{
		_sprites[n].setPosition(mine->getCenter().x(), mine->getCenter().y());
		_sprites[n].setOrigin(10,10);
		_sprites[n].setRotation(0);
		_sprites[n].setTexture(_mineTexture,true);
		n++;
	}

	for (auto turret : _gameLogic._turrets)
	{
		_sprites[n].setPosition(turret->getCenter().x(), turret->getCenter().y());
		_sprites[n].setOrigin(25,25);
		_sprites[n].setRotation(turret->getRotation()*180/PI+90);
		if (turret->getHealth() <= 0)
			_sprites[n].setTexture(_turretDeadTexture,true);
		else
			_sprites[n].setTexture(_turretTexture,true);

		n++;
	}
}

void SfmlInterface::step(const sf::Time& stepTime)
{
	float time = stepTime.asSeconds();
	_gameLogic.step(time);

	if (_gameLogic.getRemainingTime() >= 0)
	{
		 std::ostringstream buff;
		buff<<_gameLogic.getRemainingTime();
		_timeRemaingText.setString(buff.str());
		_p1Score.setString(_gameLogic.getScore(1));
		_p2Score.setString(_gameLogic.getScore(2));
	}
}

void SfmlInterface::display()
{
	_window.clear();
	_window.draw(_backSprite);
	for (auto sprite : _sprites)
	{
		_window.draw(sprite);

	}

	_window.draw(_p1Score);
	_window.draw(_p2Score);

//this in a function------------------------------------------------------------
	_window.draw(_timeRemaingText);

	displayAnnouncements();
//------------------------------------------------------------------------------


	_window.display();
}

void SfmlInterface::controllerInput()
{
	//player1
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_gameLogic.playControl(FORWARD, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_gameLogic.playControl(REVERSE, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_gameLogic.playControl(ANTI_CLOCKWISE, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_gameLogic.playControl(CLOCKWISE, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			_gameLogic.playControl(FIRE_ROCKET, 1);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
			_gameLogic.playControl(PLANT_MINE, 1);

	//player2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		_gameLogic.playControl(FORWARD, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		_gameLogic.playControl(REVERSE, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		_gameLogic.playControl(ANTI_CLOCKWISE, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		_gameLogic.playControl(CLOCKWISE, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			_gameLogic.playControl(FIRE_ROCKET, 2);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			_gameLogic.playControl(PLANT_MINE, 2);

	//misc
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		_gameLogic.playControl(RESPAWN, 1);
		updateSprites();
	}

}

void SfmlInterface::displayAnnouncements()
{
	if (_gameLogic.getRemainingTime() > 0)
		{
			_scorer = _gameLogic.getScorer();
			if (_scorer == 1)
				_window.draw(_p1Scores);
			else if (_scorer == 2)
				_window.draw(_p2Scores);
		}
		else
		{
			_window.draw(_timeUp);
			int winner = _gameLogic.getWinner();
			switch (winner)
			{
			case 0:
				_window.draw(_noWin);
				break;
			case 1:
				_window.draw(_p1Win);
				break;
			case 2:
				_window.draw(_p2Win);
				break;
			}
		}
}

