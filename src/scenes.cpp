#include "scenes.h"

namespace render_app {
namespace {
Triangle createTriangleTextures(
    const Point3& A, const Point3& B, const Point3& C, const TextureCoords& t1,
    const TextureCoords& t2, const TextureCoords& t3) {
    return Triangle{
        Vertex{.pos = A, .attr = VertexAttributes{.tcoords = t1}},
        Vertex{.pos = B, .attr = VertexAttributes{.tcoords = t2}},
        Vertex{.pos = C, .attr = VertexAttributes{.tcoords = t3}},
    };
}

Triangle createTriangleColors(
    const Point3& A, const Point3& B, const Point3& C, const sf::Color& c1,
    const sf::Color& c2, const sf::Color& c3) {
    return Triangle{
        Vertex{.pos = A, .attr = VertexAttributes{.color = c1}},
        Vertex{.pos = B, .attr = VertexAttributes{.color = c2}},
        Vertex{.pos = C, .attr = VertexAttributes{.color = c3}},
    };
}

}  // namespace

Object createGradientPyramid() {
    Point3 A{2, 0, -2};
    Point3 B{-2, 0, -2};
    Point3 C{-2, 0, -6};
    Point3 D{2, 0, -6};
    Point3 E{0, 2, -4};

    auto createTriangleGradient = [](const Point3& A, const Point3& B,
                                     const Point3& C) {
        return createTriangleColors(
            A, B, C, sf::Color::Red, sf::Color::Green, sf::Color::Blue);
    };

    std::vector<Triangle> triangles = {
        createTriangleGradient(A, B, E), createTriangleGradient(B, C, E),
        createTriangleGradient(C, D, E), createTriangleGradient(D, A, E),
        createTriangleGradient(A, B, C), createTriangleGradient(A, C, D),
    };
    return Object{std::move(triangles)};
}

Object createObamaPyramid(World& world) {
    // pyramid vertices
    Point3 A{2, 0, -2};
    Point3 B{-2, 0, -2};
    Point3 C{-2, 0, -6};
    Point3 D{2, 0, -6};
    Point3 E{0, 2, -4};

    // path is relative to build folder
    const sf::Image* obama_ptr =
        world.loadTextureFromFile("../../resources/textures/obama.jpg");
    auto [obama_w, obama_h] = obama_ptr->getSize();
    std::vector<TextureCoords> obama_coords{
        TextureCoords{         0, static_cast<double>(obama_h) - 1,obama_ptr                                                                                         },
        TextureCoords{                               0,                                0, obama_ptr},
        TextureCoords{static_cast<double>(obama_w) - 1,                                0, obama_ptr},
        TextureCoords{
                      static_cast<double>(obama_w) - 1, static_cast<double>(obama_h) - 1,
                      obama_ptr                                                                    },
        TextureCoords{
                      static_cast<double>(obama_w) / 2, static_cast<double>(obama_h) / 2,
                      obama_ptr                                                                    },
    };

    auto createFaceTextures = [&obama_coords](
                                  const Point3& A, const Point3& B,
                                  const Point3& C, size_t t1, size_t t2,
                                  size_t t3) {
        return createTriangleTextures(
            A, B, C, obama_coords[t1], obama_coords[t2], obama_coords[t3]);
    };

    sf::Color brown{94, 59, 41};
    std::vector<Triangle> triangles = {
        createFaceTextures(A, B, E, 3, 0, 4),
        createFaceTextures(B, C, E, 0, 1, 4),
        createFaceTextures(C, D, E, 1, 2, 4),
        createFaceTextures(D, A, E, 2, 3, 4),
        createTriangleColors(A, B, C, brown, brown, brown),
        createTriangleColors(A, C, D, brown, brown, brown),
    };
    return Object{std::move(triangles)};
}

Object createEgyptianPyramid(World& world) {
    // pyramid vertices
    Point3 A{2, 0, -2};
    Point3 B{-2, 0, -2};
    Point3 C{-2, 0, -6};
    Point3 D{2, 0, -6};
    Point3 E{0, 2, -4};

    // path is relative to build folder
    const sf::Image* pyramid_ptr =
        world.loadTextureFromFile("../../resources/textures/pyramid.jpg");
    auto [pyramid_w, pyramid_h] = pyramid_ptr->getSize();

    std::vector<TextureCoords> pyramid_coords{
        TextureCoords{           0,static_cast<double>(pyramid_h) - 1, pyramid_ptr                                                         },
        TextureCoords{                                 0,                                  0, pyramid_ptr},
        TextureCoords{static_cast<double>(pyramid_w) - 1,                                  0, pyramid_ptr},
        TextureCoords{
                      static_cast<double>(pyramid_w) - 1,
                      static_cast<double>(pyramid_h) - 1, pyramid_ptr                                    },
        TextureCoords{
                      static_cast<double>(pyramid_w) / 2,
                      static_cast<double>(pyramid_h) / 2, pyramid_ptr                                    },
    };

    auto createFaceTextures = [&pyramid_coords](
                                  const Point3& A, const Point3& B,
                                  const Point3& C, size_t t1, size_t t2,
                                  size_t t3) {
        return createTriangleTextures(
            A, B, C, pyramid_coords[t1], pyramid_coords[t2],
            pyramid_coords[t3]);
    };

    sf::Color yellow{242, 208, 114};
    std::vector<Triangle> triangles = {
        createFaceTextures(A, B, E, 3, 0, 4),
        createFaceTextures(B, C, E, 3, 0, 4),
        createFaceTextures(C, D, E, 3, 0, 4),
        createFaceTextures(D, A, E, 3, 0, 4),
        createTriangleColors(A, B, C, yellow, yellow, yellow),
        createTriangleColors(A, C, D, yellow, yellow, yellow),
    };
    return Object{std::move(triangles)};
}

}  // namespace render_app
