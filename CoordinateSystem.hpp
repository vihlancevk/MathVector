#ifndef COORDINATE_SYSTEM_HPP_
#define COORDINATE_SYSTEM_HPP_

#include <SFML/Graphics.hpp>

class CoordinateSystem : public sf::Drawable, public sf::Transformable {
    private:
        const float weight_ = 100, hight_ = 200;
        float xCoordinate_, yCoordinate_;
        int xMin_, xMax_;
        int yMin_, yMax_;
    public:
        CoordinateSystem(float xCoordinate, float yCoordinate, int xMin, int xMax, int yMin, int yMax);
    public:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // COORDINATE_SYSTEM_HPP_
