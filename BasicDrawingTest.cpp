
#include "SGSTank.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1300,700), "Tanks!");

    SGSTank tank1{};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(tank1);

        window.display();
    }

    return 0;
}
