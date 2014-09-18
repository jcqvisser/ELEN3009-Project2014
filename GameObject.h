/*
 * GameObject.h
 *
 *  Created on: 17 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "Triangle.h"

class object_is_glued_and_cannot_move{};

class GameObject {
public:
	GameObject(float mass);
	virtual ~GameObject(){};

	Coordinate getCenter() const;

	void addTriangle(const shared_ptr<Triangle>& tri);

	void glue();
	void unglue();

	void applyForceLinear(const Coordinate& force);
	void applyForceAngular(const float& force);
	bool animate(const float& time);

private:
	void move(const Coordinate& change);
	void rotate(const float& angle);
	bool animateLinear(const float& time);
	bool animateAngular(const float& time);

	float _mass;
	Coordinate _centerOfMass{0, 0};
	bool _glued = false;
	float _coeffOfRestitution = 0.5;
	vector<shared_ptr<Triangle>> _triangles;

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
};

#endif /* GAMEOBJECT_H_ */
