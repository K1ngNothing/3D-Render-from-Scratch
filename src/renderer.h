#pragma once
#include "camera.h"
#include "geometry.h"
#include "settings.h"
#include "world.h"

namespace application {

// use sf::VertexBuffer instead?
using Image = std::vector<sf::Vertex>;

class Renderer {
public:
    Image renderImage(const Camera& camera, const World& world);

private:
    struct Pixel {
        // TODO: remove magic constants

        double depth = 1;
        sf::Color color = sf::Color::Black;
    };
    // TODO: use container with linear memory layout
    using ZBuffer = std::vector<std::vector<Pixel>>;

    ZBuffer constructZBuffer(const Camera& camera, const World& world);
    void addTriangleToZBuffer(const Triangle& triangle, ZBuffer& z_buffer);
    std::vector<sf::Vertex> createImage(const ZBuffer& z_buffer);

    static constexpr size_t screen_w_ = settings::k_window_w;
    static constexpr size_t screen_h_ = settings::k_window_h;
};

}  // namespace application
