#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cmath>
#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"

class Vector {
    public: 
        float x_, y_, z_;
    private:
        float len_;
    public:
        Vector() : x_(0.f), y_(0.f), z_(0.f), len_(NAN) {}
        Vector(float x, float y)         : x_(x), y_(y), z_(0.f), len_(NAN) {}
        Vector(float x, float y, float z): x_(x), y_(y), z_(z),   len_(NAN) {}
        ~Vector() {}
    public:
        friend bool    operator == (Vector& lhs, Vector& rhs);

        friend Vector  operator +  (const Vector& lhs, const Vector& rhs);
        friend Vector& operator += (Vector& lhs, const Vector& rhs);

        friend Vector  operator -  (const Vector& lhs, const Vector& rhs);
        friend Vector& operator -= (Vector& lhs, const Vector& rhs);
        friend Vector& operator -  (Vector& rhs);

        friend Vector  operator *  (const float multiplier, const Vector& lhs);
        friend Vector  operator *  (const Vector& lhs, const float multiplier);
        friend Vector& operator *= (Vector& lhs, const float rhs);

        friend float operator * (const Vector& lhs, const Vector& rhs);
    private:
        float calculateLenVector();
        
        void  createTringleForVector(sf::ConvexShape& convex, CoordinateSystem& coordinateSystem) const;
    public:
        float getVectorLen();

        Vector& normalizeVector();
        Vector& rotateVector(const float angle);
        Vector& resizeVector(const CoordinateSystem& coordinateSystem, const int xGlobal, const int yGlobal);

        void draw(sf::RenderWindow& window, CoordinateSystem& coordinateSystem) const;
};

#endif // VECTOR_HPP_
