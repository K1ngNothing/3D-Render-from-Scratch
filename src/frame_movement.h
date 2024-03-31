#pragma once

#include "geometry.h"

namespace application {

struct FrameMovement {
    Point3 shift;
};

inline Matrix4 translateMovementToMatrix(const FrameMovement& movement) {
    return Matrix4{
        {1, 0, 0, movement.shift.x()},
        {0, 1, 0, movement.shift.y()},
        {0, 0, 1, movement.shift.z()},
        {0, 0, 0,                  1},
    };
}

}  // namespace application
