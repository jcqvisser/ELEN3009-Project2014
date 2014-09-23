/*
 * SGSRocket.h
 *
 */

#ifndef SGSROCKET_H_
#define SGSROCKET_H_
#include "SfmlGameSprite.h"

class SGSRocket : public SfmlGameSprite
{
public:
	SGSRocket();
	virtual ~SGSRocket();

	void Update();
    void changePosition(float x, float y);
    void animate(const float time);
    void setDirection(const float angle);

    sf::Texture _texture;
    shared_ptr<Rocket> _object{new Rocket{}};
};

#endif /* SGSROCKET_H_ */
