#pragma once

#include <vector>

#include "object.h"

namespace render_app {

class World {
private:
    class Iterator {
    public:
        Iterator(const World& world, size_t object_id, size_t triangle_id);
        Iterator& operator++();
        Iterator operator++(int);
        bool operator==(Iterator other) const;
        bool operator!=(Iterator other) const;
        const Triangle& operator*() const;

    private:
        const World& world_ref_;
        size_t object_id_;
        size_t triangle_id_;
    };

public:
    void addObject(Object&& object);
    Iterator begin() const;
    Iterator end() const;
    size_t trianglesCount() const;

private:
    std::vector<Object> objects;
    size_t triangle_count_ = 0;
};

}  // namespace render_app
