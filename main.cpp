#include <cmath>
#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"
#include "Vector.hpp"
#include "UnitTests.hpp"

const unsigned SCREEN_WEIGHT = 1920;
const unsigned SCREEN_HIGHT = 1080;
const char *SCREEN_TITLE = "Vectors";
const unsigned FRAME_RATE_LIMIT = 60;

void RotateVector(Vector& vector);
void ResizeVector(Vector& vector, const CoordinateSystem& coordinateSystem, const int xGlobal, const int yGlobal);

int main()
{
    UnitTests();

	sf::RenderWindow window(sf::VideoMode(SCREEN_WEIGHT, SCREEN_HIGHT), SCREEN_TITLE);
	window.setFramerateLimit(FRAME_RATE_LIMIT);

	sf::Event event;

    CoordinateSystem coordinateSystem1 = CoordinateSystem(800, 800, 100, 100, -10, 10, -10, 10);
    Vector vector1 = Vector(5, 5);

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
                    ResizeVector(vector2, coordinateSystem2, localPosition.x, localPosition.y);
                }
            }
		}

        if (isRotateVector) {
            RotateVector(vector1);
        }

        coordinateSystem1.Draw(window);
        vector1.Draw(window, coordinateSystem1);

        coordinateSystem2.Draw(window);
        vector2.Draw(window, coordinateSystem2);

        window.display();
		window.clear();
	}

	return 0;
}

void RotateVector(Vector& vector) {
    const float angularVelocity = 2 * 3.14f / 800;

    float x = vector.x_;
    float y = vector.y_;
    float cosF = cosf(angularVelocity);
    float sinF = sinf(angularVelocity);

    vector.x_ = x * cosF - y * sinF;
    vector.y_ = x * sinF + y * cosF;

    vector.len2_ = vector.CalculateLen2Vector();
}

void ResizeVector(Vector& vector, const CoordinateSystem& coordinateSystem, const int xGlobal, const int yGlobal) {
    float xCentre = coordinateSystem.xLeftUp_ + coordinateSystem.weight_ / 2;
    float yCentre = coordinateSystem.yLeftUp_ + coordinateSystem.hight_  / 2;

    float priceDividingScaleX = coordinateSystem.weight_ / (coordinateSystem.xMax_ - coordinateSystem.xMin_);
    float priceDividingScaleY = coordinateSystem.hight_  / (coordinateSystem.yMax_ - coordinateSystem.yMin_);

    vector.x_ =  ((float) xGlobal - xCentre) / priceDividingScaleX;
    vector.y_ = -((float) yGlobal - yCentre) / priceDividingScaleY;

    if (vector.x_ < coordinateSystem.xMin_) { vector.x_ = coordinateSystem.xMin_; }
    if (vector.x_ > coordinateSystem.xMax_) { vector.x_ = coordinateSystem.xMax_; }
    if (vector.y_ < coordinateSystem.yMin_) { vector.y_ = coordinateSystem.yMin_; }
    if (vector.y_ > coordinateSystem.yMax_) { vector.y_ = coordinateSystem.yMax_; }

    vector.len2_ = vector.CalculateLen2Vector();
}
