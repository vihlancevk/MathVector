#include <cmath>
#include "Vector.hpp"

bool operator == (const Vector& lhs, const Vector& rhs) {
    const float precision = 1e-6f;

    if (fabs(lhs.x_ - rhs.x_) > precision) return false;
    if (fabs(lhs.y_ - rhs.y_) > precision) return false;
    if (fabs(lhs.z_ - rhs.z_) > precision) return false;
    if (fabs(lhs.len2_ - rhs.len2_) > precision) return false;

    return true;
}

Vector operator + (const Vector& lhs, const Vector& rhs) {
    Vector res = lhs;
    return res += rhs;
}

Vector& operator += (Vector& lhs, const Vector& rhs) {
    lhs.x_ += rhs.x_;
    lhs.y_ += rhs.y_;
    lhs.z_ += rhs.z_;

    lhs.len2_ = lhs.CalculateLen2Vector();

    return lhs;
}

Vector operator - (const Vector& lhs, const Vector& rhs) {
    Vector res = lhs;
    return res -= rhs;
}

Vector& operator -= (Vector& lhs, const Vector& rhs) {
    lhs.x_ -= rhs.x_;
    lhs.y_ -= rhs.y_;
    lhs.z_ -= rhs.z_;

    lhs.len2_ = lhs.CalculateLen2Vector();

    return lhs;
}

Vector& operator - (Vector& rhs) {
    rhs.x_ = -rhs.x_;
    rhs.y_ = -rhs.y_;
    rhs.z_ = -rhs.z_;

    return rhs;
}

Vector  operator * (const float multiplier, const Vector& rhs) {
    Vector res = rhs;
    return res *= multiplier;
}

Vector  operator * (const Vector& lhs, const float multiplier) {
    Vector res = lhs;
    return res *= multiplier;
}

Vector& operator *= (Vector& lhs, const float rhs) {
    lhs.x_ *= rhs;
    lhs.y_ *= rhs;
    lhs.z_ *= rhs;

    lhs.len2_ = lhs.CalculateLen2Vector();

    return lhs;
}

float operator * (const Vector& lhs, const Vector& rhs) {
    return lhs.x_ * rhs.x_ + lhs.y_ * rhs.y_ + lhs.z_ * rhs.z_;
}

float Vector::CalculateLen2Vector() {
    return x_ * x_ + y_ * y_ + z_ * z_;
}

void Vector::RotateVector(const float angle) {
    float x = x_;
    float y = y_;
    float cosF = cosf(angle);
    float sinF = sinf(angle);

    x_ = x * cosF - y * sinF;
    y_ = x * sinF + y * cosF;

    len2_ = CalculateLen2Vector();
}

void Vector::ResizeVector(const CoordinateSystem& coordinateSystem, const int xGlobal, const int yGlobal) {
    float xCentre = coordinateSystem.xLeftUp_ + coordinateSystem.weight_ / 2;
    float yCentre = coordinateSystem.yLeftUp_ + coordinateSystem.hight_  / 2;

    float priceDividingScaleX = coordinateSystem.weight_ / (coordinateSystem.xMax_ - coordinateSystem.xMin_);
    float priceDividingScaleY = coordinateSystem.hight_  / (coordinateSystem.yMax_ - coordinateSystem.yMin_);

    x_ =  ((float) xGlobal - xCentre) / priceDividingScaleX;
    y_ = -((float) yGlobal - yCentre) / priceDividingScaleY;

    if (x_ < coordinateSystem.xMin_) { x_ = coordinateSystem.xMin_; }
    if (x_ > coordinateSystem.xMax_) { x_ = coordinateSystem.xMax_; }
    if (y_ < coordinateSystem.yMin_) { y_ = coordinateSystem.yMin_; }
    if (y_ > coordinateSystem.yMax_) { y_ = coordinateSystem.yMax_; }

    len2_ = CalculateLen2Vector();
}

void Vector::CreateTringleForVector(sf::ConvexShape& convex, CoordinateSystem& coordinateSystem) const {
    const float heightTriangle   = 20;
    const float halfSideTriangle = (heightTriangle) / 5;

    const float precision = 1e-6f;

    float x1Global_ = 0, y1Global_ = 0;
    coordinateSystem.ConvertLocalToGlobalVectorCoordinate(0, 0, x1Global_, y1Global_);

    float x2Global_ = 0, y2Global_ = 0;
    coordinateSystem.ConvertLocalToGlobalVectorCoordinate(x_, y_, x2Global_, y2Global_);

    float x0Global = 0, y0Global = 0;
    float x1Global = 0, y1Global = 0;
    float x2Global = 0, y2Global = 0;

    if (fabs(y2Global_ - y1Global_) < precision) {
        if (x_ >= 0) {
            x0Global = x1Global = x2Global = x2Global_ - heightTriangle;
        } else {
            x0Global = x1Global = x2Global = x2Global_ + heightTriangle;
        }
        
        y1Global = y2Global_ - halfSideTriangle;
        y2Global = y2Global_ + halfSideTriangle;
    } else if (fabs(x2Global_ - x1Global_) < precision) {
        if (y_ >= 0) {
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

        if (x_ >= 0 && y_ >= 0) {
            x0Global = x2Global_ - heightTriangle * sqrtf(cos1Squared);
            y0Global = y2Global_ + heightTriangle * sqrtf(sin1Squared);

        } else if (x_ <= 0 && y_ > 0) {
            x0Global = x2Global_ + heightTriangle * sqrtf(cos1Squared);
            y0Global = y2Global_ + heightTriangle * sqrtf(sin1Squared);

        } else if (x_ < 0 && y_ <= 0) {
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

void Vector::Draw(sf::RenderWindow& window, CoordinateSystem& coordinateSystem) const {
    float x1Global = 0, y1Global = 0;
    coordinateSystem.ConvertLocalToGlobalVectorCoordinate(0, 0, x1Global, y1Global);
    
    float x2Global = 0, y2Global = 0;
    coordinateSystem.ConvertLocalToGlobalVectorCoordinate(x_, y_, x2Global, y2Global);
    
    sf::Vertex vector[] =
    {
        sf::Vertex(sf::Vector2f(x1Global, y1Global), sf::Color::Black),
        sf::Vertex(sf::Vector2f(x2Global, y2Global), sf::Color::Black)
    };

    sf::ConvexShape convex;
    CreateTringleForVector(convex, coordinateSystem);

    window.draw(vector, 2, sf::Lines);
    window.draw(convex);
}
