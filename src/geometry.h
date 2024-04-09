#pragma once

#include <Eigen/Dense>

namespace render_app {

constexpr double g_eps = 1e-9;

using Point2 = Eigen::Vector2d;
using Point3 = Eigen::Vector3d;
using Point4 = Eigen::Vector4d;

using Matrix4 = Eigen::Matrix4d;

using Plane = Point4;

enum Side {
    INNER = 1,
    OUTER = -1,
};

inline Point4 getHomoPoint(const Point3& point) {
    return Point4{point.x(), point.y(), point.z(), 1};
}

inline Side getSide(const Point3& point, const Plane& plane) {
    return point.dot(plane.head(3)) + plane.w() > -g_eps ? Side::INNER
                                                         : Side::OUTER;
}

}  // namespace render_app
