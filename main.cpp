// #include <iostream>
#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"
#include "Vector.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "Vectors";
const unsigned FRAME_RATE_LIMIT = 60;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

	sf::Event event;

    CoordinateSystem coordinateSystem = CoordinateSystem(460, 0, -100, 100, -100, 100);
    Vector vector = Vector(coordinateSystem, -23, -17, 21, 53);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::KeyPressed)
			{
            
				if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                if (event.key.code == sf::Keyboard::W)
                    vector.isRotateVector_ = true;

                if (event.key.code == sf::Keyboard::S)
                    vector.isRotateVector_ = false;
			}

            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    vector.RecalculateVector(localPosition.x, localPosition.y);
                }
            }
		}

        if (vector.isRotateVector_)
            vector.RotateVector();

		window.clear();
        window.draw(coordinateSystem);
        window.draw(vector);
		window.display();
	}

	return 0;
}
