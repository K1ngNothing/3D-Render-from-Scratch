#include "hvertex.h"

#include "settings.h"
#include "utils.h"

namespace render_app {

HVertex::HVertex(
    const Point3& h_position, double z_reciprocal, const VertexAttributes& attr)
    : h_position_(h_position), z_reciprocal_(z_reciprocal), attr_(attr) {
}

Point3 HVertex::hPosition() const {
    return h_position_;
}

sf::Color HVertex::calculateColor() const {
    using namespace settings;
    double z = 1.0 / z_reciprocal_;
    double distant_shade_coeff =
        1.0 - z / k_far_plane_dist * (1.0 - k_min_distant_shade_coeff);
    return attr_.getColor() * distant_shade_coeff;
}

HVertex interpolate(const HVertex A, const HVertex B, double t) {
    double z1_rec = A.z_reciprocal_;
    double z2_rec = B.z_reciprocal_;
    double z3_rec = z1_rec * (1 - t) + z2_rec * t;
    return HVertex(
        A.h_position_ * (1 - t) + B.h_position_ * t, z3_rec,
        interpolate(
            A.attr_, B.attr_, (1 - t) * z1_rec / z3_rec, t * z2_rec / z3_rec));
}

std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex) {
    os << "h_position: " << h_vertex.h_position_
       << ", z:" << 1.0 / h_vertex.z_reciprocal_
       << ", attr: " << h_vertex.attr_;
    return os;
}

// ----- HTriangle -----

HTriangle::HTriangle(const HVertex& A, const HVertex& B, const HVertex& C)
    : h_vertices_({A, B, C}) {
    sortHVerticesByYCoordinate();
}

const std::array<HVertex, 3>& HTriangle::hVertices() const {
    return h_vertices_;
}

std::ostream& operator<<(std::ostream& os, const HTriangle& h_triangle) {
    for (const HVertex& h_vertex : h_triangle.h_vertices_) {
        os << h_vertex << "\n";
    }
    return os;
}

void HTriangle::sortHVerticesByYCoordinate() {
    if (h_vertices_[0].hPosition().y() < h_vertices_[1].hPosition().y()) {
        std::swap(h_vertices_[0], h_vertices_[1]);
    }
    if (h_vertices_[0].hPosition().y() < h_vertices_[2].hPosition().y()) {
        std::swap(h_vertices_[0], h_vertices_[2]);
    }
    if (h_vertices_[1].hPosition().y() < h_vertices_[2].hPosition().y()) {
        std::swap(h_vertices_[1], h_vertices_[2]);
    }
}

}  // namespace render_app
