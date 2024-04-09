#include "world.h"

namespace render_app {

World::Iterator::Iterator(const World& world, size_t object_id,
                          size_t triangle_id)
    : world_ref_(world), object_id_(object_id), triangle_id_(triangle_id) {
}

World::Iterator& World::Iterator::operator++() {
    ++triangle_id_;
    if (world_ref_.objects[object_id_].triangles().size() == triangle_id_) {
        triangle_id_ = 0;
        ++object_id_;
    }
    return *this;
}

World::Iterator World::Iterator::operator++(int) {
    Iterator copy = *this;
    ++(*this);
    return copy;
}

bool World::Iterator::operator==(Iterator other) const {
    return (triangle_id_ == other.triangle_id_ &&
            object_id_ == other.object_id_);
}
bool World::Iterator::operator!=(Iterator other) const {
    return !(*this == other);
}
const Triangle& World::Iterator::operator*() const {
    return world_ref_.objects[object_id_].triangles()[triangle_id_];
}

void World::addObject(Object&& object) {
    objects.push_back(object);
    triangle_count_ += object.triangles().size();
}

World::Iterator World::begin() const {
    return Iterator(*this, 0, 0);
}

World::Iterator World::end() const {
    return Iterator(*this, objects.size(), 0);
}

size_t World::trianglesCount() const {
    return triangle_count_;
}

}  // namespace render_app
