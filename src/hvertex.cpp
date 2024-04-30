#include "hvertex.h"

#include "settings.h"
#include "utils.h"

namespace render_app {

HVertex::HVertex(
    const Point3& h_position, double z_reciprocal,
    const std::optional<sf::Color>& color,
    const std::optional<TextureCoords>& tcoords)
    : h_position_(h_position),
      z_reciprocal_(z_reciprocal),
      color_(color),
      tcoords_(tcoords) {
}

Point3 HVertex::hPosition() const {
    return h_position_;
}

sf::Color HVertex::calculateColor() const {
    using namespace settings;
    double z = 1.0 / z_reciprocal_;
    double distant_shade_coeff =
        1.0 - z / k_far_plane_dist * (1.0 - k_min_distant_shade_coeff);
    return getColor() * distant_shade_coeff;
}

HVertex interpolate(const HVertex A, const HVertex B, double t) {
    double z1_rec = A.z_reciprocal_;
    double z2_rec = B.z_reciprocal_;
    double z3_rec = z1_rec * (1 - t) + z2_rec * t;
    Point3 pos3 = A.h_position_ * (1 - t) + B.h_position_ * t;

    // Scalar values interpolation
    std::optional<sf::Color> color3;
    std::optional<TextureCoords> tcoords3;
    double t_scalar = z2_rec / z3_rec * t;
    if (A.color_.has_value() && B.color_.has_value()) {
        color3 =
            A.color_.value() * (1 - t_scalar) + B.color_.value() * t_scalar;
    }
    if (A.tcoords_.has_value() && B.tcoords_.has_value()) {
        tcoords3 =
            A.tcoords_.value() * (1 - t_scalar) + B.tcoords_.value() * t_scalar;
    }
    return HVertex(pos3, z3_rec, color3, tcoords3);
}

std::ostream& operator<<(std::ostream& os, const HVertex& h_vertex) {
    os << "h_position: (" << h_vertex.hPosition().x() << ' '
       << h_vertex.hPosition().y() << ' ' << h_vertex.hPosition().z()
       << "), z:" << 1.0 / h_vertex.z_reciprocal_;
    if (h_vertex.color_) {
        os << ", color: " << h_vertex.color_.value();
    }
    return os;
}

sf::Color HVertex::getColor() const {
    if (color_.has_value()) {
        return color_.value();
    }
    if (tcoords_.has_value()) {
        return tcoords_->getColor();
    }
    throw std::runtime_error("HVertex::getColor: no color available");
}

// ----- HTriangle -----

HTriangle::HTriangle(HVertex A, HVertex B, HVertex C) {
    // store vertices in descending y order
    if (A.hPosition().y() < B.hPosition().y()) {
        std::swap(A, B);
    }
    if (A.hPosition().y() < C.hPosition().y()) {
        std::swap(A, C);
    }
    if (B.hPosition().y() < C.hPosition().y()) {
        std::swap(B, C);
    }
    h_vertices_ = {A, B, C};
}

std::ostream& operator<<(std::ostream& os, const HTriangle& h_triangle) {
    for (const HVertex& h_vertex : h_triangle.h_vertices_) {
        os << h_vertex << "\n";
    }
    return os;
}

}  // namespace render_app
