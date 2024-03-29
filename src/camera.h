#pragma once

#include "hvertex.h"
#include "vertex.h"

namespace application {

class Camera {
public:
    Camera();

    std::vector<HTriangle> transformTriangles(
        const std::vector<Triangle>& triangles) const;

private:
    HVertex transformVertex(const Vertex& P) const;
    HTriangle transformTriangle(const Triangle& triangle) const;

    Eigen::Matrix4d constructTransformMatrix();
    Eigen::Matrix4d transform_mat_;
};
}  // namespace application
