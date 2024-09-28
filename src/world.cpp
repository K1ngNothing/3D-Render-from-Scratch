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

Triangles::Iterator::Iterator(const World& world, size_t object_id, size_t triangle_id)
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
    return (triangle_id_ == other.triangle_id_ && object_id_ == other.object_id_);
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

std::optional<size_t> World::loadTextureFromFile(const std::filesystem::path& filename) {
    sf::Image texture;
    if (!texture.loadFromFile(filename)) {
        return std::nullopt;
    }
    textures_.push_back(std::move(texture));
    return textures_.size() - 1;
}

const sf::Image* World::getTexture(size_t id) const {
    if (textures_.size() <= id) {
        return nullptr;
    }
    return &textures_[id];
}

}  // namespace render_app
