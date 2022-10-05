#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"
#include "MathVector.hpp"
#include "UnitTests.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "Vectors";
const unsigned FRAME_RATE_LIMIT = 60;

const float PI = 3.14159f;

int main()
{
    UnitTests();

	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

	sf::Event event;

    CoordinateSystem coordinateSystem1 = CoordinateSystem(800, 800, 100, 100, -10, 10, -10, 10);
    Vector vector1 = Vector(6, 6);

    CoordinateSystem coordinateSystem2 = CoordinateSystem(800, 800, 1000, 100, -10, 10, -10, 10);
    Vector vector2 = Vector(10, 10);

    bool isRotateVector = false;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
                    window.close();

                if (event.key.code == sf::Keyboard::W)
                    isRotateVector = true;

                if (event.key.code == sf::Keyboard::S)
                    isRotateVector = false;
			}

            if (event.type == sf::Event::MouseButtonPressed) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    vector2.resizeVector(coordinateSystem2, localPosition.x, localPosition.y);
                }
            }
		}

        if (isRotateVector) {
            vector1.rotateVector(PI / 400);
        }

        coordinateSystem1.draw(window);
        vector1.draw(window, coordinateSystem1);

        coordinateSystem2.draw(window);
        vector2.draw(window, coordinateSystem2);

        window.display();
		window.clear();
	}

	return 0;
}
