/*
 * GameObject.h
 *
 *  Created on: 07 Sep 2014
 *      Author: Jacques
 */

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_
#include "GameFundamentals.h"
#include <SFML/Graphics.hpp>

//Exception Classes
class cannot_apply_force_to_Game_Object_with_no_vertices{};

class GameObject : public sf::Sprite
{
public:
	GameObject(){};
	virtual ~GameObject(){};
	void applyForce(const VectorQuantity& force, const Coordinate& pos); // TODO implement this
	void applyForce(const VectorImpulse& force, const Coordinate& pos); // TODO implement this
	void addVertex(const std::shared_ptr<Vertex>& vert); //copy a vertex into the  vertices vector
	void printVertices(); // prints the coordinates and mass of all the vertices
	void glue(); //TODO implement this
	void unglue(); //TODO implement this
	void move(float time);//todo;
	Vertex _centerOfMass{};
	Vertex _center{};
protected:
	float _maxDistFromCoM = 0;
	bool _glued = true; //represents the object's ability to move
	float _angularForce = 0;
	float _initialAngluarVelocity = 0;
	float _frictionAngular = 0;
	float _frictionLinear = 0;
	float _frictionCoeff = 1;
	VectorQuantity _velocityInitialLinear;
	VectorQuantity _forceLinear;
	std::vector<std::shared_ptr<Vertex>> _vertices; // order that vertices are listed define edges.

};


#endif /* GAMEOBJECT_H_ */
