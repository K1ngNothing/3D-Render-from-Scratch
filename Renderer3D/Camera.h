#pragma once

#include <array>

#include "FrameMovement.h"
#include "Geometry.h"
#include "HVertex.h"
#include "Vertex.h"
#include "Scene.h"

namespace Renderer3D {

class Camera {
public:
    Camera();

    std::vector<HTriangle> transformWorldTriangles(const World& world) const;
    void moveCamera(FrameMovement movement);

private:
    HVertex transformVertex(const Vertex& P) const;
    std::vector<HTriangle> transformTriangle(const Triangle& triangle) const;

    Triangle moveTriangleToCameraSpace(const Triangle& triangle) const;
    std::vector<Triangle> clipTriangle(const Triangle& triangle) const;

    Eigen::Matrix4d constructTransformMatrix() const;
    std::array<Plane, 6> constructClippingPlanes() const;

    Eigen::Matrix4d movement_mat_;
    Eigen::Matrix4d transform_mat_;
    std::array<Plane, 6> clipping_planes_;
};
}  // namespace Renderer3D
