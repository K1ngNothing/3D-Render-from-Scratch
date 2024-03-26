#include "world.h"

namespace application {

void World::addObject(const Object& object) {
    objects.push_back(object);
}

std::vector<Triangle> World::getTriangles() const {
    std::vector<Triangle> triangles;
    for (const Object& obj : objects) {
        for (const Triangle& triangle : obj.getTriangles()) {
            triangles.push_back(triangle);
        }
    }
    return triangles;
}

}  // namespace application
