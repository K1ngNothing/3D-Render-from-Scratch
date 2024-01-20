#include "camera.h"

namespace application {

Camera::Camera(double near_plane_dist, double far_plane_dist, double fov_angle, double aspect_ratio)
    : near_plane_dist_(near_plane_dist),
      far_plane_dist_(far_plane_dist),
      fov_angle_(fov_angle),
      aspect_ratio_(aspect_ratio) {
    constructTransformMatrix();
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
        assert(-1 - EPS <= point.x() && point.x() <= 1 + EPS && -1 - EPS <= point.y() &&
               point.y() <= 1 + EPS && "Transformation failed");
    }
    return transformed_triangle;
}

void Camera::constructTransformMatrix() {
    // Обозначения и формулы из книги
    double n = near_plane_dist_;
    double f = far_plane_dist_;
    double e = 1.0 / tan(fov_angle_ / 2);
    double l = -n / e;
    double r = n / e;
    double b = -aspect_ratio_ * n / e;
    double t = aspect_ratio_ * n / e;
    transform_mat_ = Eigen::Matrix4d{
        {2 * n / (r - l),               0,  (r + l) / (r - l),                    0},
        {              0, 2 * n / (t - b),  (t + b) / (t - b),                    0},
        {              0,               0, -(f + n) / (f - n), -2 * n * f / (f - n)},
        {              0,               0,                 -1,                    0}
    };
}
}  // namespace application
