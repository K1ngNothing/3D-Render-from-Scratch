#pragma once
#include "camera.h"
#include "geometry.h"
#include "world.h"

namespace application {

using Image = std::vector<sf::Vertex>;

class Renderer {
public:
    Renderer(size_t screen_w, size_t screen_h)
        : screen_w_(screen_w), screen_h_(screen_h) {
    }

    Image renderImage(const Camera& camera, const World& world);

private:
    struct Pixel {
        double depth = 1;
        sf::Color color = sf::Color::Black;
    };
    using ZBuffer = std::vector<std::vector<Pixel>>;

    ZBuffer zBufferAlgorithm(const Camera& camera, const World& world);
    void rasterizeTriangle(const Triangle& triangle,
                           Renderer::ZBuffer& z_buffer_);
    std::vector<sf::Vertex> createImage(const ZBuffer& z_buffer);

    size_t screen_w_;
    size_t screen_h_;
};

}  // namespace application
