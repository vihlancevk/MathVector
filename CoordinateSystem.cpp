#include <vector>
#include "CoordinateSystem.hpp"

static float CalculateCentreCoordinate(float topLeftCoordinate, float linearSize) {
    return topLeftCoordinate + linearSize / 2;
}

CoordinateSystem::CoordinateSystem(float xCoordinate, float yCoordinate, float xMin, float xMax, float yMin, float yMax):
    xCoordinate_(xCoordinate),
    yCoordinate_(yCoordinate),
    xMin_(xMin),
    xMax_(xMax),
    yMin_(yMin),
    yMax_(yMax),
    xCentre_(CalculateCentreCoordinate(xCoordinate, weight_)),
    yCentre_(CalculateCentreCoordinate(yCoordinate, hight_))
    {}

void CoordinateSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const float pointSize = 4;
    
    states.transform *= getTransform();
    
    sf::RectangleShape shape(sf::Vector2f(weight_, hight_));
	shape.setFillColor(sf::Color::Red);
    shape.setPosition(xCoordinate_, yCoordinate_);

    sf::Vertex lineX[] =
    {
        sf::Vertex(sf::Vector2f(xCentre_ - weight_ / 2, yCentre_), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xCentre_ + weight_ / 2, yCentre_), sf::Color::Black)
    };

    sf::Vertex lineY[] =
    {
        sf::Vertex(sf::Vector2f(xCentre_, yCentre_ - hight_ / 2), sf::Color::Black),
        sf::Vertex(sf::Vector2f(xCentre_, yCentre_ + hight_ / 2), sf::Color::Black)
    };

    sf::CircleShape centre(pointSize);
    centre.setPosition(xCentre_ - pointSize, yCentre_ - pointSize);
    centre.setFillColor(sf::Color::Black);

    std::vector<float> xCoordinates = {xMin_, xMax_};
    std::vector<sf::CircleShape> xPoints;
    for (unsigned i = 0; i < xCoordinates.size(); i++) {
        sf::CircleShape xPoint(pointSize);
        xPoint.setPosition(xCentre_ + (xCoordinates[i]) * weight_ / (xMax_ - xMin_) - pointSize, yCentre_ - pointSize);
        xPoint.setFillColor(sf::Color::Black);

        xPoints.emplace_back(xPoint);
    }

    std::vector<float> yCoordinates = {yMin_, yMax_};
    std::vector<sf::CircleShape> yPoints;
    for (unsigned i = 0; i < yCoordinates.size(); i++) {
        sf::CircleShape yPoint(pointSize);
        yPoint.setPosition(xCentre_ - pointSize, yCentre_ + (yCoordinates[i]) * hight_ / (yMax_ - yMin_) - pointSize);
        yPoint.setFillColor(sf::Color::Black);

        yPoints.emplace_back(yPoint);
    }

	target.draw(shape);
    target.draw(lineX, 2, sf::Lines);
    target.draw(lineY, 2, sf::Lines);
    target.draw(centre);
    for (unsigned i = 0; i < xPoints.size(); i++) {
        target.draw(xPoints[i]);
    }
    for (unsigned i = 0; i < yPoints.size(); i++) {
        target.draw(yPoints[i]);
    }
}
