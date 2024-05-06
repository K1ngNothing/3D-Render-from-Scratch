#pragma once

#include <vector>

#include "object.h"

namespace render_app {

class World;

class Triangles {
private:
    class Iterator;
    friend class World;

public:
    Triangles(const World& world_ref);

    Iterator begin() const;
    Iterator end() const;
    size_t size() const;

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

    const World& world_ref_;
};

class World {
    friend class Triangles;

public:
    void addObject(Object&& object);
    Triangles getTriangles() const;
    const sf::Image* loadTextureFromFile(const std::string filename);

private:
    std::vector<Object> objects;
    std::map<std::string, sf::Image> textures_;
    size_t triangle_count_ = 0;
};

}  // namespace render_app
