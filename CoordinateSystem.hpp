#ifndef COORDINATE_SYSTEM_HPP_
#define COORDINATE_SYSTEM_HPP_

#include <SFML/Graphics.hpp>

class CoordinateSystem : public sf::Drawable, public sf::Transformable {
    friend class Vector;

    private:
        const float weight_ = 1000, hight_ = 1000;
        float xCoordinate_, yCoordinate_;
        float xMin_, xMax_;
        float yMin_, yMax_;
        float xCentre_, yCentre_;
        float priceDividingScaleX_, priceDividingScaleY_;
    public:
        CoordinateSystem(float xCoordinate, float yCoordinate, float xMin, float xMax, float yMin, float yMax);
        void RotateVector();
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // COORDINATE_SYSTEM_HPP_
