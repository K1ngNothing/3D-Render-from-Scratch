#include "camera.h"

#include <cassert>

#include "settings.h"

namespace application {

Camera::Camera() : transform_mat_(constructTransformMatrix()) {
}

Point3 Camera::transformPoint(const Point3& P) const {
    Point4 Q = {P.x(), P.y(), P.z(), 1};
    Point4 Q_transformed = transform_mat_ * Q;
    Q_transformed /= Q_transformed.w();
    return Point3{Q_transformed.x(), Q_transformed.y(), Q_transformed.z()};
}

Triangle Camera::transformTriangle(const Triangle& triangle) const {
    Triangle transformed_triangle = triangle;
    for (Point3& point : transformed_triangle.points) {
        point = transformPoint(point);
        assert(-1 - k_eps <= point.x() && point.x() <= 1 + k_eps &&
               -1 - k_eps <= point.y() && point.y() <= 1 + k_eps &&
               "Transformation failed");
    }
    return transformed_triangle;
}

Eigen::Matrix4d Camera::constructTransformMatrix() {
    // Обозначения и формулы из книги
    double n = settings::k_near_plane_dist;
    double f = settings::k_far_plane_dist;
    double e = 1.0 / tan(settings::k_fov_angle / 2);
    double l = -n / e;
    double r = n / e;
    double b = -settings::aspect_ratio * n / e;
    double t = settings::aspect_ratio * n / e;
    return Eigen::Matrix4d{
        {2 * n / (r - l),               0,  (r + l) / (r - l),                    0},
        {              0, 2 * n / (t - b),  (t + b) / (t - b),                    0},
        {              0,               0, -(f + n) / (f - n), -2 * n * f / (f - n)},
        {              0,               0,                 -1,                    0}
    };
}
}  // namespace application
