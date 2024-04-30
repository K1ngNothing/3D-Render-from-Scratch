#pragma once

#include <array>
#include <iostream>
#include <optional>
#include <SFML/Graphics.hpp>

#include "geometry.h"
#include "textures.h"

namespace render_app {

class HVertex {
public:
    HVertex() = default;
    HVertex(
        const Point3& h_position, double z_reciprocal,
        const std::optional<sf::Color>& color,
        const std::optional<TextureCoords>& tcoords);
    Point3 hPosition() const;
    sf::Color calculateColor() const;

    friend HVertex interpolate(const HVertex A, const HVertex B, double t);
    friend std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex);

private:
    sf::Color getColor() const;

    Point3 h_position_;
    double z_reciprocal_;
    std::optional<sf::Color> color_;
    std::optional<TextureCoords> tcoords_;
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
    friend std::ostream& operator<<(
        std::ostream& os, const HTriangle& h_triangle);

private:
    std::array<HVertex, 3> h_vertices_;
};

std::ostream& operator<<(std::ostream& os, const HTriangle& h_triangle);

}  // namespace render_app
