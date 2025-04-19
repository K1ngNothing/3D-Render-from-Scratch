#pragma once

#include <array>
#include <cassert>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "Geometry.h"
#include "Utils.h"
#include "VertexAttributes.h"

namespace Renderer3D {

struct Vertex {
    Point3 pos;
    VertexAttributes attr;
};

inline Vertex interpolate(const Vertex& A, const Vertex& B, double t) {
    assert(inRange(t, -g_eps, 1.0 + g_eps) && "Bad interpolating coefficient");

    return Vertex{
        .pos = A.pos * (1 - t) + B.pos * t, .attr = interpolate(A.attr, B.attr, 1 - t, t)};
}

inline std::ostream& operator<<(std::ostream& os, const Vertex& vert) {
    os << "pos: " << vert.pos << ", attr: " << vert.attr;
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

}  // namespace Renderer3D
