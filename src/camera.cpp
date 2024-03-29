#include "camera.h"

#include <cassert>

#include "settings.h"
#include "utils.h"

namespace application {

Camera::Camera() : transform_mat_(constructTransformMatrix()) {
}

std::vector<HTriangle> Camera::transformTriangles(
    const std::vector<Triangle>& triangles) const {
    std::vector<HTriangle> h_triangles;
    h_triangles.reserve(triangles.size());
    for (const Triangle& triangle : triangles) {
        h_triangles.push_back(transformTriangle(triangle));
    }
    return h_triangles;
}

HVertex Camera::transformVertex(const Vertex& P) const {
    Point4 Q = {P.position.x(), P.position.y(), P.position.z(), 1};
    Point4 Q_transformed = transform_mat_ * Q;

    Point3 new_pos = Q_transformed.head(3) / Q_transformed.w();
    double z_rec = 1.0 / Q_transformed.w();
    assert(inRange(new_pos.x(), -1, 1) && inRange(new_pos.y(), -1, 1) &&
           inRange(new_pos.z(), -1, 1) && z_rec > 0 &&
           "vertex transformation failed :(");
    return HVertex(new_pos, z_rec, P.color);
}

HTriangle Camera::transformTriangle(const Triangle& triangle) const {
    return HTriangle(transformVertex(triangle.vertices[0]),
                     transformVertex(triangle.vertices[1]),
                     transformVertex(triangle.vertices[2]));
}

Eigen::Matrix4d Camera::constructTransformMatrix() {
    // Обозначения и формулы из книги
    double n = settings::k_near_plane_dist;
    double f = settings::k_far_plane_dist;
    double e = 1.0 / tan(settings::k_fov_angle / 2);
    double l = -n / e;
    double r = n / e;
    double b = -settings::k_aspect_ratio * n / e;
    double t = settings::k_aspect_ratio * n / e;
    return Eigen::Matrix4d{
        {2 * n / (r - l),               0,  (r + l) / (r - l),                    0},
        {              0, 2 * n / (t - b),  (t + b) / (t - b),                    0},
        {              0,               0, -(f + n) / (f - n), -2 * n * f / (f - n)},
        {              0,               0,                 -1,                    0}
    };
}
}  // namespace application
