#pragma once

#include "geometry.h"

namespace application {

class Camera {
public:
    Camera(double near_plane_dist, double far_plane_dist, double fov_angle, double aspect_ratio);
    Point3d transformPoint(const Point3d& P) const;
    Triangle transformTriangle(const Triangle& triangle) const;

private:
    void constructTransformMatrix();

    double near_plane_dist_;
    double far_plane_dist_;
    double fov_angle_;
    double aspect_ratio_;
    Eigen::Matrix4d transform_mat_;
};
}  // namespace application
