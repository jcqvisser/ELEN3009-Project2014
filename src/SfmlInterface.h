#ifndef SFMLINTERFACE_H_
#define SFMLINTERFACE_H_
#include "GameLogic.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

class SfmlInterface {
public:
	SfmlInterface(const float& hres=1330, const float& vres=630);
	virtual ~SfmlInterface();

	float _hres;
	float _vres;
	sf::RenderWindow _window;
	GameLogic _gameLogic{};

	vector<Sprite> _sprites{};

	Texture _tankTexture;
	Texture _tankDeadTexture;
	Texture _tank2Texture;
	Texture _tank2DeadTexture;
	Texture _rocketTexture;
	Texture _explosionTexture01;
	Texture _crateTexture;
	Texture _mineTexture;
	Texture _turretTexture;
	Texture _turretDeadTexture;

	Texture _concrete1Texture;
	Texture _concrete2Texture;
	Texture _concrete3Texture;

	Texture _background;
	Sprite _backSprite;

	Font _font;

	Text _timeRemaingText;
	Text _noWin;
	Text _p1Win;
	Text _p2Win;
	Text _p1Scores;
	Text _p2Scores;
	Text _timeUp;
	Text _p1Score;
	Text _p2Score;

	void step(const sf::Time& stepTime);
	void updateSprites();
	void display();
	void displayAnnouncements();

	void controllerInput();
	Clock _clock{};

	int _scorer = 0;
};

#endif /* SFMLINTERFACE_H_ */
