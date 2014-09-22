/*
 * SGSMapBorder.h
 *
 *  Created on: 22 Sep 2014
 *      Author: Jacques
 */

#ifndef SGSMAPBORDER_H_
#define SGSMAPBORDER_H_
#include "MapBorder.h"
#include "SfmlGameSprite.h"

class SGSMapBorder : public SfmlGameSprite
{
public:
	SGSMapBorder(const float hres);
	virtual ~SGSMapBorder();

	void Update();
    void changePosition(float x, float y);
    void animate(const float time);
    void addRotation(const float angle);

    sf::Texture _texture;
    shared_ptr<MapBorder> _object;
};

#endif /* SGSMAPBORDER_H_ */
