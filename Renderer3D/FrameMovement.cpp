#include "FrameMovement.h"

namespace Renderer3D {

FrameMovement FrameMovement::operator-() const {
    return FrameMovement{
        .shift = -shift,
        .pitch = -pitch,
        .yaw = -yaw,
        .roll = -roll
    };
}

FrameMovement& FrameMovement::operator*=(double scalar) {
    shift *= scalar;
    pitch *= scalar;
    yaw *= scalar;
    roll *= scalar;
    return *this;
}

FrameMovement emptyMovement() {
    return FrameMovement{
        .shift = Point3::Zero(),
        .pitch = 0.0,
        .yaw = 0.0,
        .roll = 0.0
    };
}

Matrix4 translateMovementToMatrix(const FrameMovement& movement) {
    double cos_a = cos(movement.pitch);
    double sin_a = sin(movement.pitch);
    double cos_b = cos(movement.yaw);
    double sin_b = sin(movement.yaw);
    double cos_c = cos(movement.roll);
    double sin_c = sin(movement.roll);

    double a11 = cos_b * cos_c;
    double a12 = -cos_b * sin_c;
    double a13 = -sin_b;

    double a21 = cos_a * sin_c - sin_a * sin_b * cos_c;
    double a22 = sin_a * sin_b * sin_c + cos_a * cos_c;
    double a23 = -sin_a * cos_b;

    double a31 = cos_a * sin_b * cos_c + sin_a * sin_c;
    double a32 = sin_a * cos_c - cos_a * sin_b * sin_c;
    double a33 = cos_a * cos_b;
    return Matrix4{
        {a11, a12, a13, movement.shift.x()},
        {a21, a22, a23, movement.shift.y()},
        {a31, a32, a33, movement.shift.z()},
        {  0,   0,   0,                  1},
    };
}

}  // namespace Renderer3D
