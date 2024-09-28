#pragma once

#include <Eigen/Dense>

namespace render_app {

constexpr double g_eps = 1e-9;

using Point2 = Eigen::Vector2d;
using Point3 = Eigen::Vector3d;
using Point4 = Eigen::Vector4d;

using Matrix3 = Eigen::Matrix3d;
using Matrix4 = Eigen::Matrix4d;

using Plane = Point4;

enum class Side {
    Inner = 1,
    Outer = -1,
};

inline Point4 getHomoPoint(const Point3& point) {
    return Point4{point.x(), point.y(), point.z(), 1};
}

inline Point4 getHomoVec(const Point3& vec) {
    return Point4{vec.x(), vec.y(), vec.z(), 0};
}

inline Point3 transformPoint(const Point3& point, const Matrix4 mat) {
    return (mat * getHomoPoint(point)).head(3);
}

inline Point3 transformVec(const Point3& vec, const Matrix4 mat) {
    return (mat * getHomoVec(vec)).head(3);
}

inline Side getSide(const Point3& point, const Plane& plane) {
    return point.dot(plane.head(3)) + plane.w() > -g_eps ? Side::Inner : Side::Outer;
}

}  // namespace render_app
