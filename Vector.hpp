#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"

class Vector {
    public: 
        float x_, y_, z_;
        float len2_;
        
    public:
        Vector(float x, float y)         : x_(x), y_(y), z_(0), len2_(CalculateLen2Vector()) {}
        Vector(float x, float y, float z): x_(x), y_(y), z_(z), len2_(CalculateLen2Vector()) {}
        ~Vector() {}
    public:
        friend bool operator == (const Vector& lhs, const Vector& rhs);

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
        float CalculateLen2Vector();

        void  CreateTringleForVector(sf::ConvexShape& convex, CoordinateSystem& coordinateSystem) const;
    public:
        void RotateVector(const float angle);
        void ResizeVector(const CoordinateSystem& coordinateSystem, const int xGlobal, const int yGlobal);
        void Draw(sf::RenderWindow& window, CoordinateSystem& coordinateSystem) const;
};

#endif // VECTOR_HPP_
