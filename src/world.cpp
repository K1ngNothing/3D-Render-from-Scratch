#include "world.h"

namespace application {

void World::addObject(const Object& object) {
    objects.push_back(object);
}

std::vector<Triangle> World::getTriangles() const {
    std::vector<Triangle> triangles;
    for (const Object& obj : objects) {
        for (const Triangle& triangle : obj.getTriangles()) {
            triangles.emplace_back(std::move(triangle));
        }
    }
    return triangles;
}

}  // namespace application
