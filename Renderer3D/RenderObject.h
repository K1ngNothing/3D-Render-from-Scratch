#pragma once

#include <vector>

#include "Vertex.h"

namespace Renderer3D {

class Object {
public:
    // TODO: support more transformations
    Object(std::vector<Triangle>&& triangles, const Point3& position = Point3::Zero());
    const std::vector<Triangle>& triangles() const;

private:
    std::vector<Triangle> triangles_;
};

}  // namespace Renderer3D
