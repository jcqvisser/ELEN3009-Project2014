
#include "SfmlInterface.h"
#include <SFML/System/Sleep.hpp>
using namespace sf;

int main()
{
	SfmlInterface interface{};
	Clock clock{};
	Time frameTime = seconds(0.01);
	Time elapsedTime = clock.getElapsedTime();
	Time loopStartTime = elapsedTime;
	Time lastDisplayTime = elapsedTime;
	Time lastLogicTime = elapsedTime;

    while (interface._window.isOpen())
        {
    		loopStartTime = clock.getElapsedTime();
				sf::Event event;
				while (interface._window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						interface._window.close();
				}

				interface.controllerInput();
				interface.step(frameTime);
			lastLogicTime = clock.getElapsedTime();
            if (loopStartTime - lastLogicTime < frameTime)
            {
            	interface.updateSprites();
            	interface.display();
            	lastDisplayTime = clock.getElapsedTime();
            }
            if (loopStartTime - lastDisplayTime < frameTime)
            	sleep(frameTime - (loopStartTime - lastDisplayTime));

        }

    return 0;
}
