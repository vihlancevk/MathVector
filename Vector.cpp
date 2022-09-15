// #include <iostream>
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

void Vector::RecalculateVector() {
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

void Vector::RotateVector() {
    float x = x2_ - x1_;
    float y = y2_ - y1_;
    float cosF = cosf(angularVelocity_);
    float sinF = sinf(angularVelocity_);

    x2_ = x * cosF - y * sinF + x1_;
    y2_ = x * sinF + y * cosF + y1_;

    isEndVectorChange_ = true;

    RecalculateVector();
}

void Vector::RecalculateVector(int x2Real, int y2Real) {
    x2Real_ = (float) x2Real;
    y2Real_ = (float) y2Real;

    x2_ =  (x2Real_ - coordinateSystem_.xCentre_) / coordinateSystem_.priceDividingScaleX_;
    y2_ = -(y2Real_ - coordinateSystem_.yCentre_) / coordinateSystem_.priceDividingScaleY_;

    isLen2VectorChange = true;

    RecalculateVector();
}

void Vector::CalculateTringleForVector(sf::ConvexShape& convex) const {
    const float heightTriangle = 20;
    const float halfSideTriangle = (heightTriangle) / 5;
    const float precision = 1e-6f;

    float x0Real = 0, y0Real = 0;
    float x1Real = 0, y1Real = 0;
    float x2Real = 0, y2Real = 0;

    if (fabs(y2Real_ - y1Real_) < precision) {
        if ((x2_ - x1_) >= 0) {
            x0Real = x1Real = x2Real = x2Real_ - heightTriangle;
        } else {
            x0Real = x1Real = x2Real = x2Real_ + heightTriangle;
        }
        
        y1Real = y2Real_ - halfSideTriangle;
        y2Real = y2Real_ + halfSideTriangle;
    } else if (fabs(x2Real_ - x1Real_) < precision) {
        if ((y2_ - y1_) >= 0) {
            y0Real = y1Real = y2Real = y2Real_ + heightTriangle;
        } else {
            y0Real = y1Real = y2Real = y2Real_ - heightTriangle;
        }

        x1Real = x2Real_ - halfSideTriangle;
        x2Real = x2Real_ + halfSideTriangle;
    } else {
        float tg1 = (y2Real_ - y1Real_) / (x2Real_ - x1Real_);
        float tg1Squared = tg1 * tg1;
        float cos1Squared = 1 / (1 + tg1Squared);
        float sin1Squared = 1 - cos1Squared;

        if ((x2_ - x1_) >= 0 && (y2_ - y1_) >= 0) {
            x0Real = x2Real_ - heightTriangle * sqrtf(cos1Squared);
            y0Real = y2Real_ + heightTriangle * sqrtf(sin1Squared);

        } else if ((x2_ - x1_) <= 0 && (y2_ - y1_) > 0) {
            x0Real = x2Real_ + heightTriangle * sqrtf(cos1Squared);
            y0Real = y2Real_ + heightTriangle * sqrtf(sin1Squared);

        } else if ((x2_ - x1_) < 0 && (y2_ - y1_) <= 0) {
            x0Real = x2Real_ + heightTriangle * sqrtf(cos1Squared);
            y0Real = y2Real_ - heightTriangle * sqrtf(sin1Squared);
        } else {
            x0Real = x2Real_ - heightTriangle * sqrtf(cos1Squared);
            y0Real = y2Real_ - heightTriangle * sqrtf(sin1Squared);
        }

        float tg2 = -1 / tg1;
        float b2 = y0Real - tg2 * x0Real;
        float tg2Squared = tg2 * tg2;
        float cos2Squared = 1 / (1 + tg2Squared);

        x1Real = x0Real - halfSideTriangle * sqrtf(cos2Squared);
        y1Real = tg2 * x1Real + b2;

        x2Real = x0Real + halfSideTriangle * sqrtf(cos2Squared);;
        y2Real = tg2 * x2Real + b2;
    }

    convex.setPointCount(3);

    convex.setPoint(0, sf::Vector2f(x2Real_, y2Real_));
    convex.setPoint(1, sf::Vector2f(x1Real, y1Real));
    convex.setPoint(2, sf::Vector2f(x2Real, y2Real));

    convex.setFillColor(sf::Color::Black);
}

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

    sf::ConvexShape convex;
    CalculateTringleForVector(convex);

    target.draw(vector, 2, sf::Lines);
    target.draw(beginVectorPoint);
    target.draw(convex);
}
