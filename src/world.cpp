#include "world.h"

namespace application {

void World::addObjects(std::vector<Triangle> triangles, Point3d position) {
    objects.emplace_back(std::move(triangles), std::move(position));
}

std::vector<Triangle> World::getTriangles() const {
    std::vector<Triangle> triangles;
    for (const Object& obj : objects) {
        for (Triangle& triangle : obj.getTriangles()) {
            triangles.emplace_back(std::move(triangle));
        }
    }
    return triangles;
}

}  // namespace application
