
#include "GameLogic.h"

int main()
{
	float hres = 1300;
	float vres = 700;

    sf::RenderWindow window(sf::VideoMode(hres, vres), "Tanks!");
    shared_ptr<SGSTank> tank1{new SGSTank{}};
    tank1->Update();
    shared_ptr<SGSTank> tank2{new SGSTank{}};
    tank2->changePosition(300,100);
    tank2->Update();

    auto mb0 = shared_ptr<SGSMapBorder>{new SGSMapBorder{hres}};


    GameLogic GL{tank1, tank2};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        GL.step();

        float x0 = tank1->_object->_triangles[0]._coordinates[0]->x();
        float x1 = tank1->_object->_triangles[0]._coordinates[1]->x();
        float x2 = tank1->_object->_triangles[0]._coordinates[2]->x();
        float y0 = tank1->_object->_triangles[0]._coordinates[0]->y();
        float y1 = tank1->_object->_triangles[0]._coordinates[1]->y();
        float y2 = tank1->_object->_triangles[0]._coordinates[2]->y();

        sf::Vertex vertices[] =
        {
        sf::Vertex(sf::Vector2f(x0, y0), sf::Color::Red, sf::Vector2f( 0, 0)),
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Red, sf::Vector2f( 0, 10)),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Red, sf::Vector2f(10, 10)),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Red, sf::Vector2f(10, 0))
        };

        float x01 = tank2->_object->_triangles[0]._coordinates[0]->x();
        float x11 = tank2->_object->_triangles[0]._coordinates[1]->x();
        float x21 = tank2->_object->_triangles[0]._coordinates[2]->x();
        float y01 = tank2->_object->_triangles[0]._coordinates[0]->y();
        float y11 = tank2->_object->_triangles[0]._coordinates[1]->y();
        float y21 = tank2->_object->_triangles[0]._coordinates[2]->y();

        sf::Vertex vertices1[] =
        {
        sf::Vertex(sf::Vector2f(x01, y01), sf::Color::Blue, sf::Vector2f( 0, 0)),
        sf::Vertex(sf::Vector2f(x11, y11), sf::Color::Blue, sf::Vector2f( 0, 10)),
        sf::Vertex(sf::Vector2f(x21, y21), sf::Color::Blue, sf::Vector2f(10, 10)),
        sf::Vertex(sf::Vector2f(x21, y21), sf::Color::Blue, sf::Vector2f(10, 0))
        };


        window.clear();
        window.draw(*tank1);
        window.draw(*tank2);
        window.draw(*mb0);
        window.draw(vertices, 4, sf::Quads);
        window.draw(vertices1, 4, sf::Quads);
        window.display();
    }
    return 0;
}
