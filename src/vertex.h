#pragma once

#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

#include "geometry.h"
#include "textures.h"
#include "utils.h"

namespace render_app {

struct Vertex {
    Point3 pos;
    std::optional<sf::Color> color;
    std::optional<TextureCoords> tcoords;
};

inline Vertex interpolate(const Vertex& A, const Vertex& B, double t) {
    assert(inRange(t, -g_eps, 1.0 + g_eps) && "Bad interpolating coefficient");

    Vertex result{.pos = A.pos * (1 - t) + B.pos * t};
    if (A.color.has_value() && B.color.has_value()) {
        result.color = A.color.value() * (1 - t) + B.color.value() * t;
    }
    if (A.tcoords.has_value() && B.tcoords.has_value()) {
        assert(
            A.tcoords->image_ptr == B.tcoords->image_ptr &&
            "Bad texture interpolation");
        result.tcoords = TextureCoords{
            .x = static_cast<size_t>(A.tcoords->x * (1 - t) + B.tcoords->x * t),
            .y = static_cast<size_t>(A.tcoords->y * (1 - t) + B.tcoords->y * t),
            .image_ptr = A.tcoords->image_ptr,
        };
    }
    return result;
}

inline std::ostream& operator<<(std::ostream& os, const Vertex& vert) {
    os << "pos: " << vert.pos;
    if (vert.color.has_value()) {
        os << ", color: " << vert.color.value();
    }
    if (vert.tcoords.has_value()) {
        os << ", texture coordinates: " << vert.tcoords.value();
    }
    return os;
}

// ----- Triangle -----

struct Triangle {
    std::array<Vertex, 3> vertices;
};

inline Triangle& operator+=(Triangle& triangle, const Point3 shift) {
    for (Vertex& vertex : triangle.vertices) {
        vertex.pos += shift;
    }
    return triangle;
}

inline std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
    for (const Vertex& vert : triangle.vertices) {
        os << vert << "\n";
    }
    return os;
}

}  // namespace render_app
