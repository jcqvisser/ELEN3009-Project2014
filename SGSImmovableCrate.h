/*
 * SGSImmovableCrate.h
 *
 *  Created on: 27 Sep 2014
 *      Author: Jacques
 */

#ifndef SGSIMMOVABLECRATE_H_
#define SGSIMMOVABLECRATE_H_
#include "SfmlGameSprite.h"

class SGSImmovableCrate : public SfmlGameSprite
{
public:
	SGSImmovableCrate();
	virtual ~SGSImmovableCrate();

	void Update();
    void changePosition(float x, float y);
    void animate(const float time);

    sf::Texture _texture;
    shared_ptr<ImmovableCrate> _object{new ImmovableCrate{}};
};

#endif /* SGSIMMOVABLECRATE_H_ */
