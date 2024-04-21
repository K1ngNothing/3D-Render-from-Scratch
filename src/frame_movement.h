#pragma once

#include "geometry.h"

namespace render_app {

struct FrameMovement {
    Point3 shift;
    double turn_up;
    double turn_right;
    double turn_clockwise;
};

inline FrameMovement operator-(const FrameMovement& movement) {
    return FrameMovement{
        .shift = -movement.shift,
        .turn_up = -movement.turn_up,
        .turn_right = -movement.turn_right,
        .turn_clockwise = -movement.turn_clockwise};
}

inline Matrix4 translateMovementToMatrix(const FrameMovement& movement) {
    double cos_a = cos(movement.turn_up);
    double sin_a = sin(movement.turn_up);
    double cos_b = cos(movement.turn_right);
    double sin_b = sin(movement.turn_right);
    double cos_c = sin(movement.turn_clockwise);
    double sin_c = cos(movement.turn_clockwise);

    double a11 = cos_b * sin_c;
    double a12 = -cos_b * cos_c;
    double a13 = -sin_b;

    double a21 = cos_a * cos_c - sin_a * sin_b * sin_c;
    double a22 = sin_a * sin_b * cos_c + cos_a * sin_c;
    double a23 = -sin_a * cos_b;

    double a31 = cos_a * sin_b * sin_c + sin_a * cos_c;
    double a32 = sin_a * sin_c - cos_a * sin_b * cos_c;
    double a33 = cos_a * cos_b;
    return Matrix4{
        {a11, a12, a13, movement.shift.x()},
        {a21, a22, a23, movement.shift.y()},
        {a31, a32, a33, movement.shift.z()},
        {  0,   0,   0,                  1}
    };
}

}  // namespace render_app
