/*
 * SGSCrate.h
 *
 *  Created on: 23 Sep 2014
 *      Author: Jacques
 */

#ifndef SGSCRATE_H_
#define SGSCRATE_H_
#include "SfmlGameSprite.h"

class SGSCrate : public SfmlGameSprite
{
public:
	SGSCrate();
	virtual ~SGSCrate();

	void Update();
    void changePosition(float x, float y);
    void animate(const float time);

    sf::Texture _texture;
    shared_ptr<Crate> _object{new Crate{}};
};

#endif /* SGSCRATE_H_ */
