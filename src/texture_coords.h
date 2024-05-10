#pragma once

#include <cassert>
#include <iostream>
#include <SFML/Graphics/Image.hpp>

namespace render_app {
struct TextureCoords {
    double x;
    double y;
    const sf::Image* image_ptr;

    sf::Color getColor() const {
        return image_ptr->getPixel(
            static_cast<unsigned int>(x), static_cast<unsigned int>(y));
    }
};

inline TextureCoords operator*(const TextureCoords& tcoords, double t) {
    return TextureCoords{
        .x = tcoords.x * t,
        .y = tcoords.y * t,
        .image_ptr = tcoords.image_ptr,
    };
}

inline TextureCoords operator+(
    const TextureCoords& tcoords1, const TextureCoords& tcoords2) {
    assert(tcoords1.image_ptr == tcoords2.image_ptr);
    return TextureCoords{
        .x = tcoords1.x + tcoords2.x,
        .y = tcoords1.y + tcoords2.y,
        .image_ptr = tcoords1.image_ptr,
    };
}

inline std::ostream& operator<<(
    std::ostream& os, const TextureCoords& tcoords) {
    return os << "(" << tcoords.x << ", " << tcoords.y << ")";
}

}  // namespace render_app
