#pragma once

#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "geometry.h"

namespace application {

class HVertex {
public:
    HVertex() = default;
    HVertex(const Point3& h_position, double z_reciprocal,
            const sf::Color& color);
    Point3 hPosition() const;
    sf::Color calculateColor() const;

    friend HVertex interpolate(const HVertex A, const HVertex B, double t);
    friend std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex);

private:
    Point3 h_position_;
    double z_reciprocal_;
    sf::Color color_;
};

HVertex interpolate(const HVertex A, const HVertex B, double t);
std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex);

// ----- HTriangle -----

class HTriangle {
public:
    HTriangle(HVertex A, HVertex B, HVertex C);

    const std::array<HVertex, 3>& hVertices() const {
        // return vertices in descending y order
        return h_vertices_;
    }
    friend std::ostream& operator<<(std::ostream& os,
                                    const HTriangle& h_triangle);

private:
    std::array<HVertex, 3> h_vertices_;
};

std::ostream& operator<<(std::ostream& os, const HTriangle& h_triangle);

}  // namespace application
