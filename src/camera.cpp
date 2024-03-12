#include "camera.h"

#include <cassert>

namespace application {

Camera::Camera(double aspect_ratio)
    : aspect_ratio_(aspect_ratio), transform_mat_(constructTransformMatrix()) {
}

Point3d Camera::transformPoint(const Point3d& P) const {
    Point4d Q = {P.x(), P.y(), P.z(), 1};
    Point4d Q_transformed = transform_mat_ * Q;
    Q_transformed /= Q_transformed.w();
    return Point3d{Q_transformed.x(), Q_transformed.y(), Q_transformed.z()};
}

Triangle Camera::transformTriangle(const Triangle& triangle) const {
    Triangle transformed_triangle = triangle;
    for (Point3d& point : transformed_triangle.points) {
        point = transformPoint(point);
        assert(-1 - EPS <= point.x() && point.x() <= 1 + EPS &&
               -1 - EPS <= point.y() && point.y() <= 1 + EPS &&
               "Transformation failed");
    }
    return transformed_triangle;
}

Eigen::Matrix4d Camera::constructTransformMatrix() {
    // Обозначения и формулы из книги
    double n = k_near_plane_dist_;
    double f = k_far_plane_dist_;
    double e = 1.0 / tan(k_fov_angle_ / 2);
    double l = -n / e;
    double r = n / e;
    double b = -aspect_ratio_ * n / e;
    double t = aspect_ratio_ * n / e;
    return Eigen::Matrix4d{
        {2 * n / (r - l),               0,  (r + l) / (r - l),                    0},
        {              0, 2 * n / (t - b),  (t + b) / (t - b),                    0},
        {              0,               0, -(f + n) / (f - n), -2 * n * f / (f - n)},
        {              0,               0,                 -1,                    0}
    };
}
}  // namespace application
