#pragma once

#include <array>
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

namespace application {

constexpr double k_eps = 1e-9;

using Point2d = Eigen::Vector2d;
using Point3d = Eigen::Vector3d;
using Point4d = Eigen::Vector4d;

using TransformMatrix = Eigen::Matrix4d;

struct Triangle {
    std::array<Point3d, 3> points;
    sf::Color color = sf::Color(0, 0, 0);

    void operator+=(const Point3d& shift);
};

bool isPointInsideTriangle2D(const Point2d& X, const Triangle& triangle);

}  // namespace application
