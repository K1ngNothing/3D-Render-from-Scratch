#pragma once

#include <optional>

#include "texture_coords.h"
#include "utils.h"

namespace render_app {
struct VertexAttributes {
    std::optional<sf::Color> color;
    std::optional<TextureCoords> tcoords;

    sf::Color getColor() const;
};

inline VertexAttributes interpolate(
    const VertexAttributes& A, const VertexAttributes& B, double t1, double t2) {
    VertexAttributes result;
    if (A.color.has_value() && B.color.has_value()) {
        result.color = A.color.value() * t1 + B.color.value() * t2;
    }
    if (A.tcoords.has_value() && B.tcoords.has_value()) {
        assert(A.tcoords->image_ptr == B.tcoords->image_ptr && "Bad texture interpolation");
        result.tcoords = A.tcoords.value() * t1 + B.tcoords.value() * t2;
    }
    return result;
}

inline std::ostream& operator<<(std::ostream& os, const VertexAttributes& attr) {
    if (attr.color.has_value()) {
        os << ", color: " << attr.color.value();
    }
    if (attr.tcoords.has_value()) {
        os << ", texture coordinates: " << attr.tcoords.value();
    }
    return os;
}

inline sf::Color VertexAttributes::getColor() const {
    if (color.has_value()) {
        return color.value();
    }
    if (tcoords.has_value()) {
        return tcoords->getColor();
    }
    assert(false);
    return sf::Color::Black;
}

}  // namespace render_app
