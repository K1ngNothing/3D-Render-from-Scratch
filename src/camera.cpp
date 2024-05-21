#include "camera.h"

#include <cassert>

#include "settings.h"
#include "utils.h"

namespace render_app {

namespace {
Vertex intersectEdgeWithPlane(
    const Vertex& A, const Vertex& B, const Plane& plane) {
    const Point3 norm = plane.head(3);
    const double d = plane.w();
    double denominator = A.pos.dot(norm) - B.pos.dot(norm);
    assert(abs(denominator) > g_eps && "Edge doesn't intersect plane");
    double t = (A.pos.dot(norm) + d) / denominator;
    assert(-g_eps < t && t < 1.0 + g_eps && "Edge doesn't intersect plane");
    return interpolate(A, B, t);
}

std::vector<Vertex> clipWithPlane(
    const std::vector<Vertex>& vertices, const Plane& plane) {
    // Sutherland–Hodgman algorithm
    assert(vertices.size() >= 3 || vertices.empty());
    std::vector<Vertex> result;
    for (size_t i = 0; i < vertices.size(); i++) {
        Vertex cur = vertices[i];
        Vertex prev = (i == 0 ? vertices.back() : vertices[i - 1]);
        if (getSide(cur.pos, plane) == Side::Inner) {
            if (getSide(prev.pos, plane) == Side::Outer) {
                result.push_back(intersectEdgeWithPlane(cur, prev, plane));
            }
            result.push_back(cur);
        } else if (getSide(prev.pos, plane) == Side::Inner) {
            result.push_back(intersectEdgeWithPlane(cur, prev, plane));
        }
    }
    return result;
}
}  // namespace

Camera::Camera()
    : movement_mat_(Matrix4::Identity()),
      transform_mat_(constructTransformMatrix()),
      clipping_planes_(constructClippingPlanes()) {
}

std::vector<HTriangle> Camera::transformWorldTriangles(
    const World& world) const {
    Triangles triangles = world.triangles();
    std::vector<HTriangle> result;
    result.reserve(triangles.size());
    for (const Triangle& triangle : triangles) {
        for (const HTriangle& h_triangle : transformTriangle(triangle)) {
            result.push_back(h_triangle);
        }
    }
    return result;
}

void Camera::moveCamera(FrameMovement movement) {
    movement_mat_ = translateMovementToMatrix(-movement) * movement_mat_;
}

HVertex Camera::transformVertex(const Vertex& P) const {
    Point4 Q = {P.pos.x(), P.pos.y(), P.pos.z(), 1};
    Point4 Q_transformed = transform_mat_ * Q;

    Point3 new_pos = Q_transformed.head(3) / Q_transformed.w();
    double z_rec = 1.0 / Q_transformed.w();
    assert(
        inRange(new_pos.x(), -1, 1) && inRange(new_pos.y(), -1, 1) &&
        inRange(new_pos.z(), -1, 1) && z_rec > 0 &&
        "vertex transformation failed :(");
    return HVertex(new_pos, z_rec, P.attr);
}

std::vector<HTriangle> Camera::transformTriangle(
    const Triangle& triangle) const {
    Triangle shifted_triangle = moveTriangleToCameraSpace(triangle);
    std::vector<Triangle> clipped_triangles = clipTriangle(shifted_triangle);
    std::vector<HTriangle> result;
    result.reserve(clipped_triangles.size());
    for (const Triangle& clipped_triangle : clipped_triangles) {
        result.emplace_back(
            transformVertex(clipped_triangle.vertices[0]),
            transformVertex(clipped_triangle.vertices[1]),
            transformVertex(clipped_triangle.vertices[2]));
    }
    return result;
}

Triangle Camera::moveTriangleToCameraSpace(const Triangle& triangle) const {
    Triangle result = triangle;
    for (Vertex& vert : result.vertices) {
        vert.pos = transformPoint(vert.pos, movement_mat_);
    }
    return result;
}

std::vector<Triangle> Camera::clipTriangle(const Triangle& triangle) const {
    std::vector<Vertex> vertices{
        triangle.vertices.begin(), triangle.vertices.end()};
    for (const Plane& plane : clipping_planes_) {
        vertices = clipWithPlane(vertices, plane);
    }
    if (vertices.empty()) {
        return {};
    }

    assert(
        vertices.size() >= 3 &&
        "Triangle clipping result has inadequate vertex count");
    std::vector<Triangle> result;
    result.reserve(vertices.size() - 2);
    for (size_t i = 2; i < vertices.size(); i++) {
        result.emplace_back(Triangle{
            .vertices = {vertices[0], vertices[i - 1], vertices[i]}
        });
    }
    return result;
}

Eigen::Matrix4d Camera::constructTransformMatrix() const {
    // Обозначения и формулы из книги
    constexpr double n = settings::k_near_plane_dist;
    constexpr double f = settings::k_far_plane_dist;
    constexpr double a = settings::k_aspect_ratio;
    constexpr double alpha = settings::k_fov_angle;
    const double e = 1.0 / tan(alpha / 2);
    const double l = -n / e;
    const double r = n / e;
    const double b = -a * n / e;
    const double t = a * n / e;
    return Eigen::Matrix4d{
        {2 * n / (r - l),               0,  (r + l) / (r - l),                    0},
        {              0, 2 * n / (t - b),  (t + b) / (t - b),                    0},
        {              0,               0, -(f + n) / (f - n), -2 * n * f / (f - n)},
        {              0,               0,                 -1,                    0}
    };
}

std::array<Plane, 6> Camera::constructClippingPlanes() const {
    // Обозначения и формулы из книги
    constexpr double n = settings::k_near_plane_dist;
    constexpr double f = settings::k_far_plane_dist;
    constexpr double a = settings::k_aspect_ratio;
    constexpr double alpha = settings::k_fov_angle;
    const double e = 1.0 / tan(alpha / 2);
    return std::array<Plane, 6>{
        Plane{                   0,                        0,                       -1, -n}, // near
        Plane{                   0,                        0,                        1,  f}, // far
        Plane{ e / sqrt(e * e + 1),                        0,   -1.0 / sqrt(e * e + 1),  0}, // left
        Plane{-e / sqrt(e * e + 1),                        0,   -1.0 / sqrt(e * e + 1),  0}, // right
        Plane{                   0,  e / sqrt(e * e + a * a), -a / sqrt(e * e + a * a),  0}, // bot
        Plane{                   0, -e / sqrt(e * e + a * a), -a / sqrt(e * e + a * a),  0}, // top
    };
}
}  // namespace render_app
