#pragma once

#include "Geometry.h"

namespace Renderer3D {

struct FrameMovement {
    Point3 shift;
    double pitch;
    double yaw;
    double roll;

    FrameMovement operator-() const;
    FrameMovement& operator*=(double scalar);
    bool operator==(const FrameMovement& other) const = default;
};


FrameMovement emptyMovement();

Matrix4 translateMovementToMatrix(const FrameMovement& movement);

}  // namespace Renderer3D
