#pragma once
#include "camera.h"
#include "world.h"

namespace application {

// use sf::VertexBuffer instead?
using Image = std::vector<sf::Vertex>;

class Renderer {
public:
    Image renderImage(const Camera& camera, const World& world);

private:
    struct Pixel {
        static constexpr double k_background_depth = 1.0 + g_eps;

        double depth = k_background_depth;
        sf::Color color = sf::Color::Black;
    };
    using ZBuffer = std::vector<std::vector<Pixel>>;

    std::vector<HTriangle> getHTriangles(const Camera& camera,
                                         const World& world);
    ZBuffer constructZBuffer(const std::vector<HTriangle>& h_triangles);
    std::vector<sf::Vertex> createImage(const ZBuffer& z_buffer);

    void addHTriangleToZBuffer(const HTriangle& h_triangle, ZBuffer& z_buffer);
    void doScanlineIteration(size_t col, HVertex left, HVertex right,
                             ZBuffer& z_buffer);
};

}  // namespace application
