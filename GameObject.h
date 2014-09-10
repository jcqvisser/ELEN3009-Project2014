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
	void applyForce(const VectorQuantity& force); // TODO implement this
	void addVertex(const std::shared_ptr<Vertex>& vert); //copy a vertex into the  vertices vector
	void printVertices(); // prints the coordinates and mass of all the vertices
	void glue(); //TODO implement this
	void unglue(); //TODO implement this
	void move(const Coordinate& pos);
	void moveBy(const VectorQuantity& d);
	void animate(float time);
	void clearForce();
	Vertex _centerOfMass{};
	bool _glued = false; //represents the object's ability to move
	float _frictionCoeff = 0.7;
	float _frictionForceMagnitude = 0;
	float _dragCoeff = 1;
	VectorQuantity _velocity{Coordinate{0,0}};
	VectorQuantity _summedForce{Coordinate{0,0}};
	std::vector<std::shared_ptr<Vertex>> _vertices; // order that vertices are listed define edges.

};



#endif /* GAMEOBJECT_H_ */
