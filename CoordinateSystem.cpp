#include "CoordinateSystem.hpp"

CoordinateSystem::CoordinateSystem(float xCoordinate, float yCoordinate, int xMin, int xMax, int yMin, int yMax):
    xCoordinate_(xCoordinate),
    yCoordinate_(yCoordinate),
    xMin_(xMin),
    xMax_(xMax),
    yMin_(yMin),
    yMax_(yMax)
    {}

void CoordinateSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    
    sf::RectangleShape shape(sf::Vector2f(weight_, hight_));
	shape.setFillColor(sf::Color::Red);
    shape.setPosition(xCoordinate_, yCoordinate_);

	target.draw(shape, states);
}
