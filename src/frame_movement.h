#pragma once

#include "geometry.h"

namespace render_app {

struct FrameMovement {
    Point3 shift;
    double turn_up;
    double turn_right;
};

inline Matrix4 translateMovementToMatrix(const FrameMovement& movement) {
    double cos_up = cos(movement.turn_up);
    double sin_up = sin(movement.turn_up);
    double cos_right = cos(movement.turn_right);
    double sin_right = sin(movement.turn_right);
    // TODO: fix clang format
    return Matrix4{
        {cos_right, -sin_right * sin_up, -sin_right * cos_up,
         movement.shift.x()                                                     },
        {        0,              cos_up,             -sin_up, movement.shift.y()},
        {sin_right,  cos_right * sin_up,  cos_right * cos_up, movement.shift.z()},
        {        0,                   0,                   0,                  1},
    };
}

}  // namespace render_app
