#pragma once

#include <vector>

#include "vertex.h"

namespace render_app {

class Object {
public:
    // TODO: support more transformations
    Object(
        std::vector<Triangle>&& triangles,
        const Point3& position = Point3::Zero());
    const std::vector<Triangle>& triangles() const;

private:
    std::vector<Triangle> triangles_;
};

}  // namespace render_app
