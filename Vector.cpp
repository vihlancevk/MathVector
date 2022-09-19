#include <iostream>
#include <cmath>
#include "Vector.hpp"

Vector operator + (const Vector& lhs, const Vector& rhs) {
    // TODO: check that this vector int one system coordinat
    Vector res = lhs;
    return res += rhs;
}

Vector& operator += (Vector& lhs, const Vector& rhs) {
    // TODO: check that this vector int one system coordinat
    lhs.Setx1Local(lhs.Getx1Local() + rhs.Getx1Local());
    lhs.Sety1Local(lhs.Gety1Local() + rhs.Gety1Local());

    lhs.Setx2Local(lhs.Getx2Local() + rhs.Getx2Local());
    lhs.Sety2Local(lhs.Gety2Local() + rhs.Gety2Local());

    lhs.RecalculateVector(true, true);

    return lhs;
}

// Vector Vector::operator - (const Vector& vector) const {
//     // TODO: check that this vector int one system coordinat
//     return Vector(coordinateSystem_, x1Local_ - vector.Getx1Local(),
//                                      y1Local_ - vector.Gety1Local(),
//                                      x2Local_ - vector.Getx2Local(),
//                                      y2Local_ - vector.Gety2Local());
// }

// void Vector::operator -= (const Vector& vector) {
//     // TODO: check that this vector int one system coordinat
//     x1Local_ -= vector.Getx1Local();
//     y1Local_ -= vector.Gety1Local();

//     x2Local_ -= vector.Getx2Local();
//     y2Local_ -= vector.Gety2Local();

//     RecalculateVector(true, true);
// }

float Vector::ConvertLocalToGlobalVectorCoordinate(float localCoordinate, bool isXCoordinate) {
    if (isXCoordinate)
        return coordinateSystem_.xCentre_ + localCoordinate * coordinateSystem_.priceDividingScaleX_;

    return coordinateSystem_.yCentre_ - localCoordinate * coordinateSystem_.priceDividingScaleY_;
}

float Vector::CalculateVectorLen2() {
    return (x2Local_ - x1Local_)*(x2Local_ - x1Local_) + (y2Local_ - y1Local_)*(y2Local_ - y1Local_);
}

Vector::Vector(CoordinateSystem& coordinateSystem, float x1Local, float y1Local, float x2Local, float y2Local):
    coordinateSystem_(coordinateSystem),
    x1Local_(x1Local),
    y1Local_(y1Local),
    x2Local_(x2Local),
    y2Local_(y2Local),
    x1Global_(ConvertLocalToGlobalVectorCoordinate(x1Local_)),
    y1Global_(ConvertLocalToGlobalVectorCoordinate(y1Local_, false)),
    x2Global_(ConvertLocalToGlobalVectorCoordinate(x2Local_)),
    y2Global_(ConvertLocalToGlobalVectorCoordinate(y2Local_, false)),
    len2_(CalculateVectorLen2())
    {}

void Vector::RecalculateVector(bool isBeginVectorChange, bool isEndVectorChange, bool isLen2VectorChange) {
    if (isBeginVectorChange) {
        x1Global_ = ConvertLocalToGlobalVectorCoordinate(x1Local_);
        y1Global_ = ConvertLocalToGlobalVectorCoordinate(y1Local_, false);
    }

    if (isEndVectorChange) {
        x2Global_ = ConvertLocalToGlobalVectorCoordinate(x2Local_);
        y2Global_ = ConvertLocalToGlobalVectorCoordinate(y2Local_, false);
    }

    if (isLen2VectorChange) {
        len2_ = CalculateVectorLen2();
    }
}

void Vector::RotateVector(bool isRotateVector) {
    isRotateVector_ = isRotateVector;
}

void Vector::RotateVector() {
    if (isRotateVector_) {
        float x = x2Local_ - x1Local_;
        float y = y2Local_ - y1Local_;
        float cosF = cosf(angularVelocity_);
        float sinF = sinf(angularVelocity_);

        x2Local_ = x * cosF - y * sinF + x1Local_;
        y2Local_ = x * sinF + y * cosF + y1Local_;

        RecalculateVector(false, true);
    }
}

void Vector::ConvertGlobalToLocalVectorCoordinates(int x2Global, int y2Global) {
    x2Global_ = (float) x2Global;
    y2Global_ = (float) y2Global;

    x2Local_ =  (x2Global_ - coordinateSystem_.xCentre_) / coordinateSystem_.priceDividingScaleX_;
    y2Local_ = -(y2Global_ - coordinateSystem_.yCentre_) / coordinateSystem_.priceDividingScaleY_;

    RecalculateVector(false, false, true);
}

void Vector::CalculateTringleForVector(sf::ConvexShape& convex) const {
    const float heightTriangle = 20;
    const float halfSideTriangle = (heightTriangle) / 5;
    const float precision = 1e-6f;

    float x0Global = 0, y0Global = 0;
    float x1Global = 0, y1Global = 0;
    float x2Global = 0, y2Global = 0;

    if (fabs(y2Global_ - y1Global_) < precision) {
        if ((x2Local_ - x1Local_) >= 0) {
            x0Global = x1Global = x2Global = x2Global_ - heightTriangle;
        } else {
            x0Global = x1Global = x2Global = x2Global_ + heightTriangle;
        }
        
        y1Global = y2Global_ - halfSideTriangle;
        y2Global = y2Global_ + halfSideTriangle;
    } else if (fabs(x2Global_ - x1Global_) < precision) {
        if ((y2Local_ - y1Local_) >= 0) {
            y0Global = y1Global = y2Global = y2Global_ + heightTriangle;
        } else {
            y0Global = y1Global = y2Global = y2Global_ - heightTriangle;
        }

        x1Global = x2Global_ - halfSideTriangle;
        x2Global = x2Global_ + halfSideTriangle;
    } else {
        float tg1 = (y2Global_ - y1Global_) / (x2Global_ - x1Global_);
        float tg1Squared = tg1 * tg1;
        float cos1Squared = 1 / (1 + tg1Squared);
        float sin1Squared = 1 - cos1Squared;

        if ((x2Local_ - x1Local_) >= 0 && (y2Local_ - y1Local_) >= 0) {
            x0Global = x2Global_ - heightTriangle * sqrtf(cos1Squared);
            y0Global = y2Global_ + heightTriangle * sqrtf(sin1Squared);

        } else if ((x2Local_ - x1Local_) <= 0 && (y2Local_ - y1Local_) > 0) {
            x0Global = x2Global_ + heightTriangle * sqrtf(cos1Squared);
            y0Global = y2Global_ + heightTriangle * sqrtf(sin1Squared);

        } else if ((x2Local_ - x1Local_) < 0 && (y2Local_ - y1Local_) <= 0) {
            x0Global = x2Global_ + heightTriangle * sqrtf(cos1Squared);
            y0Global = y2Global_ - heightTriangle * sqrtf(sin1Squared);
        } else {
            x0Global = x2Global_ - heightTriangle * sqrtf(cos1Squared);
            y0Global = y2Global_ - heightTriangle * sqrtf(sin1Squared);
        }

        float tg2 = -1 / tg1;
        float b2 = y0Global - tg2 * x0Global;
        float tg2Squared = tg2 * tg2;
        float cos2Squared = 1 / (1 + tg2Squared);

        x1Global = x0Global - halfSideTriangle * sqrtf(cos2Squared);
        y1Global = tg2 * x1Global + b2;

        x2Global = x0Global + halfSideTriangle * sqrtf(cos2Squared);;
        y2Global = tg2 * x2Global + b2;
    }

    convex.setPointCount(3);

    convex.setPoint(0, sf::Vector2f(x2Global_, y2Global_));
    convex.setPoint(1, sf::Vector2f(x1Global, y1Global));
    convex.setPoint(2, sf::Vector2f(x2Global, y2Global));

    convex.setFillColor(sf::Color::Black);
}

void Vector::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    const float beginPointSize = 4;
    const float endPointSize = 8;
    
    states.transform *= getTransform();

    sf::Vertex vector[] =
    {
        sf::Vertex(sf::Vector2f(x1Global_, y1Global_), sf::Color::Black),
        sf::Vertex(sf::Vector2f(x2Global_, y2Global_), sf::Color::Black)
    };

    sf::CircleShape beginVectorPoint(beginPointSize);
    beginVectorPoint.setPosition(x1Global_ - beginPointSize, y1Global_ - beginPointSize);
    beginVectorPoint.setFillColor(sf::Color::Black);

    sf::CircleShape endVectorPoint(endPointSize);
    endVectorPoint.setPosition(x2Global_ - endPointSize, y2Global_ - endPointSize);
    endVectorPoint.setFillColor(sf::Color::Black);

    sf::ConvexShape convex;
    CalculateTringleForVector(convex);

    target.draw(vector, 2, sf::Lines);
    target.draw(beginVectorPoint);
    target.draw(convex);
}
