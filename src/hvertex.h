#pragma once

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "geometry.h"
#include "vertex_attributes.h"

namespace render_app {

class HVertex {
public:
    HVertex(
        const Point3& h_position, double z_reciprocal,
        const VertexAttributes& attr);
    Point3 hPosition() const;
    sf::Color calculateColor() const;

    friend HVertex interpolate(const HVertex A, const HVertex B, double t);
    friend std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex);

private:
    Point3 h_position_;
    double z_reciprocal_;
    VertexAttributes attr_;
};

HVertex interpolate(const HVertex A, const HVertex B, double t);
std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex);

// ----- HTriangle -----

class HTriangle {
public:
    HTriangle(const HVertex& A, const HVertex& B, const HVertex& C);

    const std::array<HVertex, 3>& hVertices() const;
    friend std::ostream& operator<<(
        std::ostream& os, const HTriangle& h_triangle);

private:
    // stores vertices in descending y order
    std::array<HVertex, 3> h_vertices_;
};

std::ostream& operator<<(std::ostream& os, const HTriangle& h_triangle);

}  // namespace render_app
