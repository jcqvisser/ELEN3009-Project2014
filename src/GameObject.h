#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Triangle.h"
#include <time.h>
#include <iterator>

/*!
 * 	\brief Exception Class: gets thrown as an exception when a glued object is moved.
 */
class object_is_glued_and_cannot_move{};

/*!
 * 	\brief Exception Class: thrown as an exception by intersectingLine(const Line& penetratingLine) when no lines intersect.
 */
class No_Line_Intersects{};

/*!
 * \brief TException Class: thrown as an exception by avgCoordInside(const GameObject& gO) when no Coordinates are found inside of the GameObject
 */
class No_Coordinates_Inside{};

/*!
 * \brief Exception Class: thrown as an exception when a rocket is fired during the rocket fire refractory period.
 */
class Rocket_Fire_Frequency_too_High{};

/*!
 * 	\brief Exception Class: thrown as an exception when a mine is planted during the mine plant refractory period.
 */
class Mine_Plant_frequency_too_High{};

/*!
 * 	\brief Exception Class: thrown as an exception when a mine is planted when there are no mines left.
 */
class Out_of_Mines{};

/*!
 * 	\brief The GameObject class represents some element of the game which may or may not have a spatial component and may or may not be drawn on screen
 *
 * 	The GameObject class represents some physical aspect of the game, it is extended to make tanks, boundaries etc.
 * 	It has members relating to it's lifetime, physical appearance and movement.
 */
class GameObject {
public:
	/*!
	 *  \brief GameObject's constructor initialises all the appropriate member variables for an object of type GameObject to be used by GameLogic, Collision and CollisionManager.
	 *  \param mass This value is assigned as the GameObject's mass, to be used in collision resolution.
	 *
	 *  This constructor mainly records the time that an object of this type is created.
	 */
	GameObject(float mass);

	/*!
	 * 	\brief Standard virtual destructor.
	 */
	virtual ~GameObject(){};

	/*!
	*	\brief Reduces the object's health to 0.
	*/
	void kill();

	/*! \brief applies damage to a GameObject
	*	\param dmg amount to reduce the object's health by
	*
	*	Reduces the object's health by the amount specified as dmg
	*/
	void damage(const float& dmg);

	/*!
	 * \brief Restores a GameObject's health.
	 *
	 * 	When run, this makes the object's _health 100.
	 */
	void revive();

	/*!
	 * \brief returns the position of the GameObject's center of mass.
	 * \return Returns a Coordinate object representing the position of the GameObject's center of mass in a 2D plane.
	 */
	Coordinate getCenter();

	/*!
	 * \brief Returns the velocity that the GameObject is currently travelling at.
	 * \return Returns a Coordinate object that represents the GameObject's current velocity vector.
	 */
	Coordinate getVelocity() const;

	/*! \brief Returns the orientation of the GameObject
	 * 	\return Returns a Coordinate object of magnitude 1 representing a unit vector that is oriented with the GameObject.
	 */
	Coordinate getForward() const;

	/*!
	 * 	\brief Returns the force currently applied to the GameObject.
	 * 	\returns Returns the force currently applied to the GameObject as a vector, represented by a Coordinate object.
	 */
	Coordinate getForceLinear() const;

	/*!
	 *	\brief Returns all the Triangles that the GameObject is made up of.
	 *	\return Returns a vector of Triangle objects representing the body of the GameObject.
	 */
	vector<Triangle> getTriangles() const;

	/*!
	 * \brief Returns the GameObject's mass
	 * \return Returns a floating point number representing the mass of the GameObject.
	 */
	float getMass() const;

	/*!
	 * 	\brief Returns the orientation of the GameObject as an angle.
	 * 	\return Returns the angle, in radians, that the GameObject is oriented at as a floating point number.
	 */
	float getRotation() const;

	/*!
	 * \brief Returns the GameObject's health
	 * \return Returns a floating point number representing the health of the GameObject. This may take on any value, positive or negative.
	 */
	float getHealth() const;

	/*!
	 * 	\brief Returns the time at which the GameObject last had 0 or less health.
	 * 	\return Returns a floating point number representing the number of seconds since the game started that the GameObject has last had 0 or less health
	 */
	float getTimeOfDeath() const;

	/*!
	 * 	\brief Returns the time at which the GameObject was created.
	 * 	\return Returns the time, as a floating point number, which represents the seconds since the game started that the GameObject was created.
	 */
	float getBirthTime() const;

	/*!
	 * 	\brief Returns the length of the period that the GameObject had health above 0
	 * 	\return Returns a floating point number representing the number of seconds that the object was alive.
	 */
	float getLifeTime() const;

	/*!
	 * 	\brief Returns the magnitude of the angular force currently applied to the GameObject as a floating point number.
	 */
	float getForceAngular() const;

	/*!
	 * 	\brief Returns true if the object is prevented from moving.
	 */
	bool isGlued() const;

	/*!
	 * 	\brief Assigns a floating point value to the GameObject's drag coefficient.
	 */
	void setDragCoeff(const float& dC);

	/*!
	 * 	\brief Changes the GameObject's position.
	 * 	\param pos The position, represented by a Coordinate, where the GameObject is moved to.
	 */
	void setPosition(const Coordinate& pos);

	/*!
	 * 	\brief Makes all the forces currently acting on the GameObject zero.
	 */
	virtual void clearForce();

	/*!
	 * 	\brief Removes the angular force currently acting on the GameObject.
	 */
	void clearAngularForce();

	/*!
	 * 	\brief Prevents a GameObject from being moved.
	 */
	void glue();

	/*!
	 *  \brief Allows a GameObject to move.
	 */
	void unglue();

	/*!
	 *  \brief Changes the orientation of the GameObject
	 *  \param angle A floating point number representing the angle, in radians, by which the object is rotated about it's center of gravity.
	 *
	 *  The rotate function is run on each of the triangles that make up the GameObject, as well as the Coordinate that represents the orientation.
	 */
	void rotate(const float& angle);

	/*!
	 * 	\brief Adds a Triangle to the body of the GameObject
	 * 	\param tri a shared pointer to a triangle to be added to the GameObject.
	 *
	 * 	Triangles are used to define an area as being part of a GameObject, this is used in collision detection and resolution.
	 * 	Adding triangles expands this area.
	 */
	void addTriangle(shared_ptr<Triangle>& tri);

	/*!
	 * \brief Moves the GameObject in the vertical and horisontal directions by an amount defined by a Coordinate.
	 * \param change A coordinate which is added to all the coordinates that make up the GameObject.
	 */
	void move(const Coordinate& change);

	/*!
	 * 	\brief Increases the current linear force vector acting on the GameObject by a specified amount.
	 * 	\param force A coordinate representing a 2D force vector that is added to the linear force furrently acting on the GameObject
	 */
	void applyForceLinear(const Coordinate& force);

	/*!
	 * 	\brief Increases the current angulat force acting on the GameObject by a specified amount.
	 * 	\param force A floating point number representing a 1D angular force vector that is added to the angular force furrently acting on the GameObject
	 */
	void applyForceAngular(const float& force);

	/*!
	*	\brief Applies a vector impulse to the GameObject, increasing it's velocity
	*	\param impulse A Coordinate representing the amount the GameObject's linear velocity is to be increased by.
	*
	*	Impulse is directly added to the _velocity member variable.
	*/
	void applyImpulseLinear(const Coordinate& impulse);

	/*!
	*	\brief Used to have a GameObject react to a collision
	*	\param rhs A Coordinate representing the normal of a surface multiplied by a constant
	*
	*	rhs Represents the normal of a surface the GameObject has collided with multiplied by a constant that is proportional to the energy of the collision.
	*	This function is overridden by classes that inherit from GameObject so as to implement their own method of reacting to a collision.
	*/
	virtual void react(const Coordinate& rhs) {};

	/*!
	*	\brief Moves the game object depending on the forces currently acting on it and it's velocity.
	*	\param time The time over which the forces is applied and after which to calculate it's new velocity and position. This function makes use of animateLinear(const float& time).
	*/
	bool animate(const float& time);

	/*!
	*	\brief Determines whether a Coordinate from a different GameObject is inside the GameObject.
	*	\param gO A shared pointer to a GameObject.
	*
	*	This function makes use of the Triangle::hasInside(const vector<Triangle> triangles) const function for all the triangles of the GameObject, passing to it the vector of Triangles that make up the other GameObject.
	*/
	bool hasInside(const shared_ptr<GameObject>& gO);

	/*!
	*	\brief Determines whether the supplied coordinate is inside the GameObject.
	*	\param coord The coordinate to check whether it is in the GameObject.
	*
	*	This function makes use of the Triangle::hasInside(const shared_ptr<Coordinate>& coord) const function for all the triangles of the GameObject, passing coord to it.
	*/
	bool hasInside(const Coordinate& coord) const;

	/*!
	*	\brief Determines the average position of all the coordinates from gO found inside the GameObject
	*	\param gO A GameObject object
	*
	*This function makes use of the Triangle::coordsInside(const vector<Triangle> triangles) const function for all the triangles of the GameObject, passing to it the vector of Triangles that make up the other GameObject, and everaging the results.
	*/
	Coordinate avgCoordInside(const GameObject& gO);

	/*!
	*	\brief Determines the edge of GameObject that intersects with the supplied line.
	*	\param penetratingLine A line extending into the GameObject.
	*
	*	This function makes use of the Triangle::getLine(const int LineNo) function and passes the penetratingLine to the Line::intersects(const Line& line) const function. The function returns a copy of the first line it finds in this way that intersects with penetratingLine.
	*/
	Line intersectingLine(const Line& penetratingLine);

protected:
	vector<Triangle> _triangles; //< A vector of Triangle objects that collectively define the GameObject's surface area.

	/*!
	*	\brief Applies linear position and velocity changes to the GameObject.
	*	\param time A floating point number representing the time over which to simulate the object moving.
	*
	*	This function is used in GameObject::animate(const float& time)
	*/
	bool animateLinear(const float& time);

	float _mass = 1; //< Represents the mass of the GameObject.
	Coordinate _centerOfMass{0, 0}; //< A Coordinate representing the center of mass of the GameObject
	Coordinate _forward{0, 1};	//< A Coordinate representing the orientation of the GameObject as a vector.
	Coordinate _velocityLinear{0, 0}; //< A Coordinate representing the linear velocity vector of the GameObject
	Coordinate _forceLinear{0, 0}; //< A Coordinate representing the linear force vector currently acting on the GameObject
	float _dragCoeff = 1; //< A floating point value representing the drag coefficient of the GameObject, used in simluating it's movement.
	float _forceAngular = 0; //< A floating point number representing the angular force currently acting in the GameObject

	float _health = 100; //< The current health of the GameObject
	float _birthTime = 0;	//< The time at which the GameObject is created, realtice to when the program was started
	float _timeOfDeath = 0; //< The time at which the object's health last dropped to 0 or below.
	float _lifeTime = 0; //< A limit on how long the object may have more than 0 health for.

	bool _glued = false; //< A boolean value representing whether the object may move or not. False=may not move.
};
#endif /* GAMEOBJECT_H_ */
