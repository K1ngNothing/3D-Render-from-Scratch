#include "RenderObject.h"

namespace Renderer3D {

Object::Object(std::vector<Triangle>&& triangles, const Point3& position)
    : triangles_(std::move(triangles)) {
    for (Triangle& triangle : triangles_) {
        triangle += position;
    }
}

const std::vector<Triangle>& Object::triangles() const {
    return triangles_;
}

}  // namespace Renderer3D
