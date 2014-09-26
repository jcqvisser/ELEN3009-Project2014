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
	float getMass() const;
	float getRotation() const;

	void addTriangle(shared_ptr<Triangle>& tri);

	void glue();
	void unglue();

	void applyForceLinear(const Coordinate& force);
	void applyImpulseLinear(const Coordinate& impulse);
	void applyForceAngular(const float& force);
	bool animate(const float& time);
	virtual void clearForce();

	bool hasInside(const shared_ptr<GameObject>& gO);
	bool hasInside(const Coordinate& coord) const;
	Coordinate avgCoordInside(const GameObject& gO);
	Line intersectingLine(const Line& penetratingLine);

	void setDragCoeffLinear(const float& dC);
	void setDragCoeffAngular(const float& dC);
	void setPosition(const Coordinate& pos);

	virtual void react(const Coordinate& rhs) {};

//protected:
	vector<Triangle> _triangles;

	void move(const Coordinate& change);
	void rotate(const float& angle);
	bool animateLinear(const float& time);
	bool animateAngular(const float& time);

	float _mass = 1;
	Coordinate _centerOfMass{0, 0};
	bool _glued = false;

	Coordinate _forward{0, 1};
	Coordinate _velocityLinear{0, 0};
	float _vThresholdLinear{0};
	Coordinate _forceLinear{0, 0};
	float _dragCoeffLinear = 1;
	float _forceLinearThreshold = 0.1;

	float _velocityAngular = 0.0;
	float _forceAngular = 0.0;
	float _vThresholdAngular{0};
	float _dragCoeffAngular = 5;
	float _forceAngularThreshold = 0.1;

	float _health = 100;
};

#endif /* GAMEOBJECT_H_ */
