#pragma once

#include <vector>

#include "object.h"

namespace application {

class World {
public:
    void addObject(std::vector<Triangle> triangles, Point3d position);
    std::vector<Triangle> getTriangles() const;

private:
    std::vector<Object> objects;
};

}  // namespace application
