/*
 * SGSTank.h
 *
 *  Created on: 21 Sep 2014
 *      Author: Jacques
 */

#ifndef SGSTANK_H_
#define SGSTANK_H_
#include "SfmlGameSprite.h"

class SGSTank : public SfmlGameSprite
{
public:
	SGSTank();
	virtual ~SGSTank();

	void Update();
    void changePosition(float x, float y);
    void animate(const float time);

    sf::Texture _texture;
    shared_ptr<Tank> _object{new Tank{}};

};

#endif /* SGSTANK_H_ */
