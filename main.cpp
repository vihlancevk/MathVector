#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "Vectors";
const unsigned FRAME_RATE_LIMIT = 60;

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

	sf::Event event;

    CoordinateSystem coordinateSystem = CoordinateSystem(100, 100, -10, 10, -10, 10);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
                window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
                    window.close();
			}
		}

		window.clear();
        window.draw(coordinateSystem);
		window.display();
	}

	return 0;
}
