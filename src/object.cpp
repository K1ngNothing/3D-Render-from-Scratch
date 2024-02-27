#include "object.h"

namespace application {

Object::Object(std::vector<Triangle> triangles, const Point3d& position)
    : triangles_(std::move(triangles)) {
    for (Triangle& triangle : triangles_) {
        for (Point3d& point : triangle.points) {
            point += position;
        }
    }
}

std::vector<Triangle> Object::getTriangles() const {
    return triangles_;
}

}  // namespace application
