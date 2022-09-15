#include <iostream>
#include <cmath>
#include "Vector.hpp"

float Vector::CalculateRealVectorCoordinate(float coordinate, bool isXCoordinate) {
    if (isXCoordinate)
        return coordinateSystem_.xCentre_ + coordinate * coordinateSystem_.priceDividingScaleX_;

    return coordinateSystem_.yCentre_ - coordinate * coordinateSystem_.priceDividingScaleY_;
}

float Vector::CalculateVectorLen2() {
    return (x2_ - x1_)*(x2_ - x1_) + (y2_ - y1_)*(y2_ - y1_);
}

void Vector::RecalculateVectorInNewCoordinateSystem() {
    if (isBeginVectorChange_) {
        x1Real_ = CalculateRealVectorCoordinate(x1_);
        y1Real_ = CalculateRealVectorCoordinate(y1_, false);
        isBeginVectorChange_ = false;
    }

    if (isEndVectorChange_) {
        x2Real_ = CalculateRealVectorCoordinate(x2_);
        y2Real_ = CalculateRealVectorCoordinate(y2_, false);
        isEndVectorChange_ = false;
    }

    if (isLen2VectorChange) {
        isLen2VectorChange = false;
        len2_ = (x2_ - x1_)*(x2_ - x1_) + (y2_ - y1_)*(y2_ - y1_);
    }
}

void Vector::RotateVector() {
    float x = x2_ - x1_;
    float y = y2_ - y1_;
    float cosF = cosf(angularVelocity_);
    float sinF = sinf(angularVelocity_);

    x2_ = x * cosF - y * sinF + x1_;
    y2_ = x * sinF + y * cosF + y1_;

    isEndVectorChange_ = true;

    RecalculateVectorInNewCoordinateSystem();
}

Vector::Vector(CoordinateSystem& coordinateSystem, float x1, float y1, float x2, float y2):
    coordinateSystem_(coordinateSystem),
    x1_(x1),
    y1_(y1),
    x2_(x2),
    y2_(y2),
    x1Real_(CalculateRealVectorCoordinate(x1_)),
    y1Real_(CalculateRealVectorCoordinate(y1_, false)),
    x2Real_(CalculateRealVectorCoordinate(x2_)),
    y2Real_(CalculateRealVectorCoordinate(y2_, false)),
    len2_(CalculateVectorLen2())
    {}

void Vector::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const float beginPointSize = 4;
    const float endPointSize = 8;
    
    states.transform *= getTransform();

    sf::Vertex vector[] =
    {
        sf::Vertex(sf::Vector2f(x1Real_, y1Real_), sf::Color::Black),
        sf::Vertex(sf::Vector2f(x2Real_, y2Real_), sf::Color::Black)
    };

    sf::CircleShape beginVectorPoint(beginPointSize);
    beginVectorPoint.setPosition(x1Real_ - beginPointSize, y1Real_ - beginPointSize);
    beginVectorPoint.setFillColor(sf::Color::Black);

    sf::CircleShape endVectorPoint(endPointSize);
    endVectorPoint.setPosition(x2Real_ - endPointSize, y2Real_ - endPointSize);
    endVectorPoint.setFillColor(sf::Color::Black);

    target.draw(vector, 2, sf::Lines);
    target.draw(beginVectorPoint);
    target.draw(endVectorPoint);
}
