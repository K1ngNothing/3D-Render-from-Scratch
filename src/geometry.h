#pragma once

#include <array>
#include <Eigen/Dense>
#include <SFML/Graphics.hpp>

namespace application {

constexpr double g_eps = 1e-9;

using Point2 = Eigen::Vector2d;
using Point3 = Eigen::Vector3d;
using Point4 = Eigen::Vector4d;

using TransformMatrix = Eigen::Matrix4d;

struct Triangle {
    std::array<Point3, 3> points;
    sf::Color color = sf::Color(0, 0, 0);

    Triangle& operator+=(const Point3& shift);
};

bool isPointInsideTriangle2D(const Point2& X, const Triangle& triangle);

}  // namespace application
