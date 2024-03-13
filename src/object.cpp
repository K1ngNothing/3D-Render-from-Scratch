#include "object.h"

namespace application {

Object::Object(std::vector<Triangle> triangles, const Point3d& position)
    : triangles_(std::move(triangles)) {
    for (Triangle& triangle : triangles_) {
        triangle += position;
    }
}

const std::vector<Triangle>& Object::getTriangles() const {
    return triangles_;
}

}  // namespace application
