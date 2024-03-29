#pragma once

#include <vector>

#include "object.h"

namespace application {

class World {
public:
    void addObject(const Object& object);
    // TODO: make iterators
    std::vector<Triangle> getTriangles() const;

private:
    std::vector<Object> objects;
};

}  // namespace application
