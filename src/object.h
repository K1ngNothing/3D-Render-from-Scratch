#pragma once

#include <vector>

#include "geometry.h"

namespace application {

class Object {
public:
    // TODO: support more transformations
    Object(std::vector<Triangle> triangles,
           const Point3& position = Point3::Zero());
    const std::vector<Triangle>& getTriangles() const;

private:
    std::vector<Triangle> triangles_;
};

}  // namespace application
