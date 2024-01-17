#pragma once

#include <array>
#include <SFML/Graphics.hpp>
// #include <Eigen/Dense>
#include "../Eigen/Eigen/Dense"

namespace application {

constexpr double EPS = 1e-9;

using Point2d = Eigen::Vector2d;
using Point3d = Eigen::Vector3d;

struct Triangle {
    std::array<Point3d, 3> points;
    sf::Color color = sf::Color(0, 0, 0);
};

bool isPointInsideTriangle2D(const Point2d& X, const Triangle& triangle);

}  // namespace application
