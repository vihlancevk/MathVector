#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <SFML/Graphics.hpp>
#include "CoordinateSystem.hpp"

const float pi = 3.14f;

class Vector : public sf::Drawable, public sf::Transformable {
    private: 
        CoordinateSystem& coordinateSystem_;

        float x1Local_, y1Local_;

        float x2Local_, y2Local_;
        
        float x1Global_, y1Global_;
        float x2Global_, y2Global_;
        
        float len2_;
        
        const float angularVelocity_ = 2*pi / 800;
        bool isRotateVector_ = false;
    private:
        void CalculateTringleForVector(sf::ConvexShape& convex) const;
        float ConvertLocalToGlobalVectorCoordinate(float localCoordinate, bool isXCoordinate = true);
        float CalculateVectorLen2();
    public:
        CoordinateSystem& GetCoordinateSystem() const { return coordinateSystem_; }
        
        float Getx1Local() const { return x1Local_; }
        void  Setx1Local(float x1Local) { x1Local_ = x1Local; }

        float Gety1Local() const { return y1Local_; }
        void  Sety1Local(float y1Local) { y1Local_ = y1Local; }
        
        float Getx2Local() const { return x2Local_; }
        void  Setx2Local(float x2Local) { x2Local_ = x2Local; }
        
        float Gety2Local() const { return y2Local_; }
        void  Sety2Local(float y2Local) { y2Local_ = y2Local; }

        Vector(CoordinateSystem& coordinateSystem, float x1Local, float y1Local, float x2Local, float y2Local);
        void RotateVector(bool isRotateVector);
        void RotateVector();        
        void ConvertGlobalToLocalVectorCoordinates(int x2Global, int y2Global);
        void RecalculateVector(bool isBeginVectorChange = false,
                               bool isEndVectorChange   = false,
                               bool isLen2VectorChange  = false);

        friend Vector  operator +  (const Vector& lhs, const Vector& rhs);
        friend Vector& operator += (Vector& lhs, const Vector& rhs);
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // VECTOR_HPP_
