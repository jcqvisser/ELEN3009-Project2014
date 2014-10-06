#ifndef SFMLINTERFACE_H_
#define SFMLINTERFACE_H_
#include "GameLogic.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

class SfmlInterface {
public:
	/*!
	*	Imports all the sprite textures, creates the sf::Text objects used to display announcements, sets the map resolution in _gameLogic and loads the level layout using _gameLogic.
	*/
	SfmlInterface(const float& hres=1330, const float& vres=630);

	virtual ~SfmlInterface(); /**< Basic virtual destructor.*/

	float _vres; /**< Window horizontal resolution */
	float _hres; /**< Window vertical resolution */
	sf::RenderWindow _window; /**< Sfml Window to display game*/

	GameLogic _gameLogic{}; /**< A GameLogic object which manager all GameObject type and collision objects.*/

	vector<Sprite> _sprites{}; /**< A vector holding the sprites to be rendered in the window. */

	Texture _tankTexture; /**< The texture used by sprites to represent player 1's Tank object */
	Texture _tankDeadTexture; /**< The texture used by sprites to represent player 1's Tank object when it has been reduced to a dessicated husk of it's former self */
	Texture _tank2Texture; /**< The texture used by sprites to represent player 2's Tank object */
	Texture _tank2DeadTexture; /**< The texture used by sprites to represent player 2's dead Tank object */
	Texture _rocketTexture; /**< The texture used by sprites to represent a Rocket object */
	Texture _explosionTexture01; /**< The texture used by sprites to represent a GameObject that represents an explosion.*/
	Texture _crateTexture; /**< The texture used by sprites to represent a Crate or ImmovableCrate object */
	Texture _mineTexture; /**< The texture used by sprites to represent a Mine object */
	Texture _turretTexture; /**< The texture used by sprites to represent a living Turret object */
	Texture _turretDeadTexture; /**< The texture used by sprites to represent a dead Turret object */
	Texture _concrete1Texture; /**< The texture used by sprites to represent a Concrete object with maximum health */
	Texture _concrete2Texture; /**< The texture used by sprites to represent a Concrete object with medium health */
	Texture _concrete3Texture; /**< The texture used by sprites to represent a Concrete object with low health*/

	Texture _background; /**< The texture used by a sprite to draw the background to the battlefield*/
	Sprite _backSprite;/**< The sprite that holds the background texture*/

	Font _font;	/**< The font used to display announcements */

	Text _timeRemaingText; /**< The Text object that displays the amount of time remaining*/
	Text _noWin;/**< The Text object that displays the announcement that no-one has won */
	Text _p1Win; /**< The Text object that displays the announcement that player 1 has won */
	Text _p2Win; /**< The Text object that displays the announcement that player 2 has won */
	Text _p1Scores; /**< The Text object that displays the announcement that player 1 has scored */
	Text _p2Scores; /**< The Text object that displays the announcement that player 2 has scored */
	Text _timeUp; /**< The Text object that displays the announcement that the match time is up */
	Text _p1Score; /**< The Text object that displays player 1's score*/
	Text _p2Score; /**< The Text object that displays player 2's score*/
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
