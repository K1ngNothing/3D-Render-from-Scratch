#pragma once
#include "camera.h"
#include "geometry.h"
#include "settings.h"
#include "world.h"

namespace application {

using Image = std::vector<sf::Vertex>;

class Renderer {
public:
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

    static constexpr size_t screen_w_ = settings::k_window_w;
    static constexpr size_t screen_h_ = settings::k_window_h;
};

}  // namespace application
