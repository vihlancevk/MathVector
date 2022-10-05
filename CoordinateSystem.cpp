#include "CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(float weight, float hight,
                                   float xLeftUp, float yLeftUp,
                                   float xMin, float xMax, float yMin, float yMax):
    weight_(weight),
    hight_(hight),
    xLeftUp_(xLeftUp),
    yLeftUp_(yLeftUp),
    xMin_(xMin),
    xMax_(xMax),
    yMin_(yMin),
    yMax_(yMax)
    {}

void CoordinateSystem::convertLocalToGlobalVectorCoordinate(float xLocal, float yLocal,
                                                            float& xGlobal, float& yGlobal) const {
    xGlobal = xLeftUp_ + (weight_ / (xMax_ - xMin_)) * (xLocal - xMin_);
    yGlobal = yLeftUp_ - (hight_  / (yMax_ - yMin_)) * (yLocal + yMin_);
}

void CoordinateSystem::draw(sf::RenderWindow& window) const {
    const float pointSize = 4;

    const float xCentre = xLeftUp_ + weight_ / 2;
    const float yCentre = yLeftUp_ + hight_  / 2;

    sf::RectangleShape shape(sf::Vector2f(weight_, hight_));
	shape.setFillColor(sf::Color::Red);
    shape.setPosition(xLeftUp_, yLeftUp_);

    sf::Vertex lineX[] =
    {
        sf::Vertex(sf::Vector2f(xCentre - weight_ / 2, yCentre), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xCentre + weight_ / 2, yCentre), sf::Color::Black)
    };

    sf::Vertex lineY[] =
    {
        sf::Vertex(sf::Vector2f(xCentre, yCentre - hight_ / 2), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xCentre, yCentre + hight_ / 2), sf::Color::Black)
    };

    sf::CircleShape centre(pointSize);
    centre.setPosition(xCentre - pointSize, yCentre - pointSize);
    centre.setFillColor(sf::Color::Black);

	window.draw(shape);
    window.draw(lineX, 2, sf::Lines);
    window.draw(lineY, 2, sf::Lines);
    window.draw(centre);
}
