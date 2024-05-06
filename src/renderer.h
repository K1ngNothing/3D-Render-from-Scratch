#pragma once
#include "camera.h"
#include "container2d.h"
#include "world.h"

namespace render_app {

using Image = std::vector<sf::Vertex>;

class Renderer {
public:
    Image renderImage(const Camera& camera, const World& world);

private:
    struct Pixel {
        static constexpr double k_background_depth = 1.0 + g_eps;

        double depth = k_background_depth;
        sf::Color color = sf::Color::Black;  // background color
    };
    using ZBuffer = Container2d<Pixel>;

    std::vector<HTriangle> getHTriangles(
        const Camera& camera, const World& world);
    ZBuffer constructZBuffer(const std::vector<HTriangle>& h_triangles);
    std::vector<sf::Vertex> createImage(const ZBuffer& z_buffer);

    void addHTriangleToZBuffer(const HTriangle& h_triangle, ZBuffer& z_buffer);
    void doScanlineIteration(
        size_t row, HVertex left, HVertex right, ZBuffer& z_buffer);
};

}  // namespace render_app
