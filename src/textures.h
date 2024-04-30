#pragma once

#include <cassert>
#include <iostream>
#include <map>
#include <SFML/Graphics/Image.hpp>
#include <stdexcept>

namespace render_app {
struct TextureCoords {
    size_t x;
    size_t y;
    const sf::Image* image_ptr;

    sf::Color getColor() const {
        return image_ptr->getPixel(x, y);
    }
};

inline TextureCoords operator*(const TextureCoords& tcoords, double t) {
    return TextureCoords{
        .x = static_cast<size_t>(tcoords.x * t),
        .y = static_cast<size_t>(tcoords.y * t),
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

// ----- TextureManager -----

class TextureManager {
public:
    const sf::Image* loadFromFile(const std::string filename) {
        auto it = textures_.find(filename);
        if (it != textures_.end()) {
            return &it->second;
        }
        sf::Image& texture = textures_[filename];
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error(
                "TextureManager::loadFromFile: invalid filename");
        }
        return &texture;
    }

private:
    std::map<std::string, sf::Image> textures_;
};

}  // namespace render_app
