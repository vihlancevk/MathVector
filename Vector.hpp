#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"

const float pi = 3.14f;

class Vector : public sf::Drawable, public sf::Transformable {
    private: 
        CoordinateSystem& coordinateSystem_;

        float x1_, y1_;
        bool isBeginVectorChange_ = false;

        float x2_, y2_;
        bool isEndVectorChange_ = false;
        
        float x1Real_, y1Real_;
        float x2Real_, y2Real_;
        
        float len2_;
        bool isLen2VectorChange = false;
        
        float angularVelocity_ = 2*pi / 800;
    public:
        bool isRotateVector_ = false;
    private:
        void CalculateTringleForVector(sf::ConvexShape& convex) const;
        float CalculateRealVectorCoordinate(float coordinate, bool isXCoordinate = true);
        float CalculateVectorLen2();
        void RecalculateVector();
    public:
        Vector(CoordinateSystem& coordinateSystem, float x1, float y1, float x2, float y2);
        void RotateVector();
        void RecalculateVector(int x2Real, int y2Real);
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // VECTOR_HPP_
