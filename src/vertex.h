#pragma once

#include <array>
#include <SFML/Graphics.hpp>

#include "geometry.h"

namespace application {

struct Vertex {
    Point3 position;
    sf::Color color;
};

struct Triangle {
    std::array<Vertex, 3> vertices;
};

inline Triangle& operator+=(Triangle& triangle, const Point3 shift) {
    for (Vertex& vertex : triangle.vertices) {
        vertex.position += shift;
    }
    return triangle;
}

}  // namespace application
