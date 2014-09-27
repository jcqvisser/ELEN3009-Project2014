/*
 * GameObject.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Triangle.h"
#include <iterator>

class object_is_glued_and_cannot_move{};
class No_Line_Intersects{};
class No_Coordinates_Inside{};

class GameObject {
public:
	GameObject(float mass);
	virtual ~GameObject(){};

	Coordinate getCenter();
	Coordinate getVelocity() const;
	Coordinate getForward() const;
	Coordinate getForceLinear() const;
	vector<Triangle> getTriangles() const;
	float getMass() const;
	float getRotation() const;

	void setDragCoeff(const float& dC);
	void setPosition(const Coordinate& pos);
	void clearForce();

	void addTriangle(shared_ptr<Triangle>& tri);

	void move(const Coordinate& change);
	void applyForceLinear(const Coordinate& force);
	void applyForceAngular(const float& force);
	void applyImpulseLinear(const Coordinate& impulse);
	virtual void react(const Coordinate& rhs) {};
	bool animate(const float& time);

	bool hasInside(const shared_ptr<GameObject>& gO);
	bool hasInside(const Coordinate& coord) const;
	Coordinate avgCoordInside(const GameObject& gO);
	Line intersectingLine(const Line& penetratingLine);

protected:
	vector<Triangle> _triangles;

	void rotate(const float& angle);
	bool animateLinear(const float& time);

	float _mass = 1;
	Coordinate _centerOfMass{0, 0};

	Coordinate _forward{0, 1};
	Coordinate _velocityLinear{0, 0};
	Coordinate _forceLinear{0, 0};
	float _dragCoeff = 1;

	float _forceAngular = 0;

	float _health = 100;
};

#endif /* GAMEOBJECT_H_ */
