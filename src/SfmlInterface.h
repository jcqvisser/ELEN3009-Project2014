#ifndef SFMLINTERFACE_H_
#define SFMLINTERFACE_H_
#include "GameLogic.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

using namespace sf;
using namespace std;

/*!
*	\brief A class that acts as the connection between SFML and the logic layer.
*/
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

	/*!
	*	\brief Steps the state of the game forward by a defined steptime.
	*	\param stepTime An SFML time object representing the amount of time to step the game forward by.
	*
	*	This function runs the underlying GameLogic::step(const float time) function of the _gameObject member variable.
	*	In addition to this it also gets and displays the time remaining of the match and the players' scores.
	*/
	void step(const sf::Time& stepTime);

	/*!
	*	\brief Updates the _sprites vector to reflect the drawable game objects in _gameLogic.
	*
	*	This function requests the amount of drawable objects from _gameObject and resizes the _sprites vector appropriately. It then loops through all the drawable GameObjects in _gameLogic and updates the Textures of the Sprite objects in _sprites to represent all the types of game object in _gameLogic.
	*/
	void updateSprites();

	/*!
	*	\brief Updates the display window.
	*
	*	Clears the display window, draws the background sprite, then all the Sprite objects in _sprite, followed by player 1 and 2's scores and the time remaining. This is followed by the Announcements being drawn. Finally everything that was drawn is dispayed.
	*/
	void display();

	/*!
	*	\brief Displays the appropriate announcement for the game state
	*/
	void displayAnnouncements();

	/*!
	*	\brief Interprets controller input and passes commands to the Tank objects in the _gameLogic object.
	*/
	void controllerInput();

	Clock _clock{}; /**< An SFML clock object*/

	int _scorer = 0;/**< represents the last player to have scored. */
};

#endif /* SFMLINTERFACE_H_ */
