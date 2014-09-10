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
	void addVertex(const std::shared_ptr<Vertex>& vert); //copy a vertex into the  vertices vector
	void printVertices(); // prints the coordinates and mass of all the vertices
	void glue(); //TODO implement this
	void unglue(); //TODO implement this
	void move(const Coordinate& pos);
	void animate(float time);
	Vertex _centerOfMass{};
	Vertex _center{};
	bool _glued = false; //represents the object's ability to move
	float _frictionCoeff = 1;
	float _frictionForceMagnitude;
	float _dragCoeff = 1;
	VectorQuantity _initialVelocity;
	VectorQuantity _summedForce;
	std::vector<std::shared_ptr<Vertex>> _vertices; // order that vertices are listed define edges.

};



#endif /* GAMEOBJECT_H_ */
