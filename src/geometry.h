#pragma once

#include <Eigen/Dense>

namespace application {

constexpr double g_eps = 1e-9;

using Point2 = Eigen::Vector2d;
using Point3 = Eigen::Vector3d;
using Point4 = Eigen::Vector4d;

using Matrix4 = Eigen::Matrix4d;

}  // namespace application
