#include "world.h"

namespace render_app {

// ----- Triangles -----

Triangles::Triangles(const World& world_ref) : world_(world_ref) {
}

Triangles::Iterator Triangles::begin() const {
    return Iterator(world_, 0, 0);
}

Triangles::Iterator Triangles::end() const {
    return Iterator(world_, world_.get().objects.size(), 0);
}

size_t Triangles::size() const {
    return world_.get().triangle_count_;
}

// ----- Triangles::Iterator -----

Triangles::Iterator::Iterator(
    const World& world, size_t object_id, size_t triangle_id)
    : world_(world), object_id_(object_id), triangle_id_(triangle_id) {
}

Triangles::Iterator& Triangles::Iterator::operator++() {
    ++triangle_id_;
    if (world_.get().objects[object_id_].triangles().size() == triangle_id_) {
        triangle_id_ = 0;
        ++object_id_;
    }
    return *this;
}

Triangles::Iterator Triangles::Iterator::operator++(int) {
    Iterator copy = *this;
    ++(*this);
    return copy;
}

bool Triangles::Iterator::operator==(Iterator other) const {
    return (
        triangle_id_ == other.triangle_id_ && object_id_ == other.object_id_);
}

bool Triangles::Iterator::operator!=(Iterator other) const {
    return !(*this == other);
}

const Triangle& Triangles::Iterator::operator*() const {
    return world_.get().objects[object_id_].triangles()[triangle_id_];
}

const Triangle* Triangles::Iterator::operator->() const {
    return &world_.get().objects[object_id_].triangles()[triangle_id_];
}

// ----- World -----

void World::addObject(Object&& object) {
    triangle_count_ += object.triangles().size();
    objects.push_back(std::move(object));
}

Triangles World::triangles() const {
    return Triangles(*this);
}

const sf::Image* World::loadTextureFromFile(const std::string filename) {
    auto it = textures_.find(filename);
    if (it != textures_.end()) {
        return &it->second;
    }
    sf::Image& texture = textures_[filename];
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error(
            "TextureManager::loadFromFile: invalid filename");
    }
    return &texture;
}

}  // namespace render_app
