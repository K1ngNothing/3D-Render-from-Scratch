#pragma once

#include "geometry.h"

namespace application {

class Camera {
public:
    Camera(double aspect_ratio);
    Point3d transformPoint(const Point3d& P) const;
    Triangle transformTriangle(const Triangle& triangle) const;

private:
    Eigen::Matrix4d constructTransformMatrix();
    static constexpr double k_fov_angle_ = M_PI / 2;
    static constexpr double k_near_plane_dist_ = 1.0;
    static constexpr double k_far_plane_dist_ = 10.0;
    // FIXME: make me constexpr
    const double aspect_ratio_;
    Eigen::Matrix4d transform_mat_;
};
}  // namespace application
