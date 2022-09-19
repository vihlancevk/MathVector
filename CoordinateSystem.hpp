#ifndef COORDINATE_SYSTEM_HPP_
#define COORDINATE_SYSTEM_HPP_

#include <SFML/Graphics.hpp>

class CoordinateSystem {
    public:
        float weight_, hight_;
        float xLeftUp_, yLeftUp_;
        float xMin_, xMax_;
        float yMin_, yMax_;
    public:
        CoordinateSystem(float weight, float hight,
                         float xLeftUp, float yLeftUp,
                         float xMin, float xMax, float yMin, float yMax);
        ~CoordinateSystem() {}
    public:
        void ConvertLocalToGlobalVectorCoordinate(float xLocal, float yLocal, float& xGlobal, float& yGlobal) const;
        void Draw(sf::RenderWindow& window) const;
};

#endif // COORDINATE_SYSTEM_HPP_
