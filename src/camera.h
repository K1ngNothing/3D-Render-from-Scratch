#pragma once

#include "geometry.h"

namespace application {

class Camera {
public:
    Camera();
    Point3d transformPoint(const Point3d& P) const;
    Triangle transformTriangle(const Triangle& triangle) const;

private:
    Eigen::Matrix4d constructTransformMatrix();
    Eigen::Matrix4d transform_mat_;
};
}  // namespace application
