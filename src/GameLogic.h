#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include <list>
#include <time.h>
#include <algorithm>
#include <sstream>
#include "Tank.h"
#include "Rocket.h"
#include "Mine.h"
#include "Crate.h"
#include "Concrete.h"
#include "ImmovableCrate.h"
#include "Turret.h"
#include "Boundary.h"

/*!
*	\brief Thrown when attempting to access a non existant player.
*/
class Player_Does_not_Exist{};

enum playerControl
{
	FORWARD,
	REVERSE,
	CLOCKWISE,
	ANTI_CLOCKWISE,
	FIRE_ROCKET,
	PLANT_MINE,
	RESPAWN
};

/*!
*	\brief A class representing the amalgamation of all the logical elements of this game.
*/
class GameLogic {
public:
	GameLogic(); /**< Default Constructor*/
	virtual ~GameLogic(); /**< Basic Virtual Destructor */

	/*!
	*	\brief Loads the layout of a level.
	*
	*	Creates Player, Concrete, Crate and Tank objects an places them at appropriate positions on the map.
	*/
	void loadLevel();

	/*!
	*	\brief creates the four boundary objects preventing other game objects from leaving the window.
	*/
	void loadBoundary(const int hres, const int vres);

	/*! \brief Passes all the gameobjects that can be collided with to the collision manager.
	*
	* Passed to the collision manager: _players, _rockets, _crates, _concretes, _mines, _turrets
	*
	*/
	void updateCollisionManager();

	/*!
	*	animates all objects over the given time period, checks for rocket and mine damage. Checks whether any objects time out. Updates the Collision manager and uses it to find, resolve and then purge the collisions. Cears all the forces on all game objects, 
	*/
	void step(const float time);

	/*!
	*	\brief runs the GameObject::animate(const float& time) function on all objects that are derived from GameObject.
	* 	\param time A floating point number representing the time over which to simulate the movement of all GameObject derived objects.
	*/
	void animate(const float time);

	/*!
	*	\brief Clears all forces on all game objects
	*/
	void clearForces();

	/*!
	*	\brief Applies rocket damage.
	*
	*	Loops through all damagable game objects to see whether they are in contact with a rocket, if so, they take damage or die.
	*/
	void checkRocketDamage();

	/*!
	*	\brief Applies min damage.
	*
	*	Loops through all damagable game objects to see whether they are in contact with a mine, if so, they take damage or die.
	*/
	void checkMineDamage();

	/*!
	*	\brief Checks all appropriate game objects for a built in time-out.
	*
	*	Some objects are destroyed after a certain period, specifically explosions. This function checks their time-out conditions.
	*/
	void checkTimedDeath();

	/*!
	*	\brief Checks all killable game objects' health and acts if they are dead.
	*
	*	oops through all killable game objects ,erases dead concretes, crates and rockets. Then spawns an explosion in their place.
	*/	
	void checkHealthDeath();

	/*!
	*	\brief Turret AI
	*
	*	Has all the turrets that are alive track their targets and fire rockets when they are within a defined range.
	*/
	void turretAction();

	/*!
	*	\brief Interprets and activates player controls
	*	\param control An enum that represents the player's action.
	*	\param player An integer that identifies the player that sends the player control.
	*/
	void playControl(const playerControl& control, const int& player);

	/*!
	*	\return Returns the amount of drawable game objects
	*/
	int numObjects() const;

	/*!
	*	\brief determines whether a GameObject has health below 0.
	*/
	bool isDead(const shared_ptr<GameObject>&);

	/*!
	*	\return Returns the amount of seconds of the match remaining as a floating point number
	*/
	float getRemainingTime();

	/*!
	*	\return Returns 0 if no players are curretly dead, 1 if player 2 is currently dead, 2 if player 1 is currently dead.
	*/
	int getScorer();

	/*!
	*	\brief reduces the time remaining of the game to 0.
	*/
	void endGame();

	/*!
	*	\brief Assigns the resolution of the playing field.
	*/
	void setResolution(const int, const int);

	/*!
	*	\brief Respawn both players.
	*
	*	Players are returned to their starting positions and their health is increased to 100.
	*/
	void resetPlayers();

	/*!
	*	\brief Gives the current score of a player.
	*	\param player An integer representing the player who's score is requested.
	*	\return Returns the players score as a string to be displayed.
	*/
	string getScore(const int player);

	/*!
	*	\brief Returns the match winner.
	*	\return Returns 0 if the match hasn't timed out/ If the match has timed out, it returns 1 if player 1 has won, returns 2 if player 2 has win
	*/
	int getWinner();

	list<shared_ptr<Tank>> _players; /**< A linked list of shared pointers to Tank objects */
	list<shared_ptr<Rocket>> _rockets; /**< A linked list of shared pointers to Rocket objects */
	list<shared_ptr<Crate>> _crates; /**< A linked list of shared pointers to Crate objects */
	list<shared_ptr<Concrete>> _concretes; /**< A linked list of shared pointers to Concrete objects */
	list<shared_ptr<Mine>> _mines; /**< A linked list of shared pointers to Mine objects */
	list<shared_ptr<Turret>> _turrets; /**< A linked list of shared pointers to Turret objects */
	list<shared_ptr<GameObject>> _explosion01s; /**< A linked list of shared pointers to GameObject objects */

	shared_ptr<Boundary> _topBound; /**< a shared pointer to the top Boundary object*/
	shared_ptr<Boundary> _bottomBound; /**< a shared pointer to the bottom Boundary object*/
	shared_ptr<Boundary> _leftBound; /**< a shared pointer to the laft Boundary object*/
	shared_ptr<Boundary> _rightBound; /**< a shared pointer to the right Boundary object*/

	CollisionManager _collMan{}; /**< A CollisionManager object that creates and handles Collision objects. */

	int _hres = 1330; /**< the horisontal resolution of the playing field */
	int _vres = 630; /**< the vertical resolution of the playing field */

private:
	float _startTime = clock()/CLOCKS_PER_SEC;
	float _roundTime = 120;

	float p1FireTime = clock()/CLOCKS_PER_SEC;
	float p2FireTime = clock()/CLOCKS_PER_SEC;
	float FireTime = 0.25;

	int _p1Score = 0;
	int _p2Score = 0;

	void buildCrate(const Coordinate pos, const bool glued);
	void buildTank(const Coordinate pos);
	void buildTurret(const Coordinate pos);
	void buildConcrete(const Coordinate pos, const float angle);
};

#endif /* GAMELOGIC_H_ */
