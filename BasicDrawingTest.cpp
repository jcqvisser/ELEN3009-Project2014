
#include "SfmlInterface.h"

int main()
{
	SfmlInterface interface{};

    while (interface._window.isOpen())
        {
            sf::Event event;
            while (interface._window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                	interface._window.close();
            }

            interface.controllerInput();
            interface.step();
            interface.updateSprites();
            interface.display();
        }

    return 0;
}
