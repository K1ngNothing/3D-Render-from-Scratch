#include "renderer.h"

#include <cassert>

#include "settings.h"

namespace render_app {

namespace {

struct PixelCoords {
    size_t x;
    size_t y;
};

PixelCoords homoToPixel(const Point2& P) {
    // ([-1; 1], [-1; 1]) -> ([0; window_w], [0; window_h])
    double raw_x = (P.x() + 1.0) / 2.0 * settings::k_window_w;
    double raw_y = (P.y() + 1.0) / 2.0 * settings::k_window_h;
    auto discretize = [](const double x, const size_t upper_bound) {
        return std::min<size_t>(std::max(0.0, floor(x)), upper_bound - 1);
    };
    return PixelCoords{
        discretize(raw_x, settings::k_window_w),
        discretize(raw_y, settings::k_window_h),
    };
}

sf::Vector2f getPixelPosition(size_t i, size_t j) {
    return sf::Vector2f{static_cast<float>(i),
                        static_cast<float>(settings::k_window_h - j)};
}

double getInterpolateCoeff(size_t x, size_t lb, size_t rb) {
    assert(lb != rb && lb <= x && x <= rb);
    return static_cast<double>(x - lb) / (rb - lb);
}

}  // namespace

Image Renderer::renderImage(const Camera& camera, const World& world) {
    return createImage(constructZBuffer(getHTriangles(camera, world)));
}

std::vector<HTriangle> Renderer::getHTriangles(const Camera& camera,
                                               const World& world) {
    return camera.transformWorldTriangles(world);
}

Renderer::ZBuffer Renderer::constructZBuffer(
    const std::vector<HTriangle>& h_triangles) {
    ZBuffer z_buffer(settings::k_window_w, settings::k_window_h);
    for (const HTriangle& h_triangle : h_triangles) {
        addHTriangleToZBuffer(h_triangle, z_buffer);
    }
    return z_buffer;
}

Image Renderer::createImage(const ZBuffer& z_buffer_) {
    Image image;
    image.reserve(settings::k_window_w * settings::k_window_h);
    for (size_t i = 0; i < settings::k_window_w; i++) {
        for (size_t j = 0; j < settings::k_window_h; j++) {
            image.emplace_back(getPixelPosition(i, j), z_buffer_(i, j).color);
        }
    }
    return image;
}

void Renderer::addHTriangleToZBuffer(const HTriangle& h_triangle,
                                     ZBuffer& z_buffer) {
    auto [top, middle, bottom] = h_triangle.hVertices();
    size_t yTop = homoToPixel(top.hPosition().head(2)).y;
    size_t yMiddle = homoToPixel(middle.hPosition().head(2)).y;
    size_t yBottom = homoToPixel(bottom.hPosition().head(2)).y;

    if (yTop == yBottom) {
        // degenerate case
        doScanlineIteration(yTop, top, middle, z_buffer);
        doScanlineIteration(yTop, middle, bottom, z_buffer);
        doScanlineIteration(yTop, top, bottom, z_buffer);
        return;
    }

    for (size_t row = yBottom; row <= yTop; row++) {
        HVertex left =
            interpolate(bottom, top, getInterpolateCoeff(row, yBottom, yTop));
        HVertex right =
            (row <= yMiddle && yMiddle != yBottom)
                ? interpolate(bottom, middle,
                              getInterpolateCoeff(row, yBottom, yMiddle))
                : interpolate(middle, top,
                              getInterpolateCoeff(row, yMiddle, yTop));
        doScanlineIteration(row, left, right, z_buffer);
    }
}

void Renderer::doScanlineIteration(size_t row, HVertex left, HVertex right,
                                   ZBuffer& z_buffer) {
    auto update_zbuffer = [&z_buffer](const size_t col, const size_t row,
                                      const HVertex& vert) {
        if (z_buffer(col, row).depth > vert.hPosition().z()) {
            z_buffer(col, row) = {.depth = vert.hPosition().z(),
                                  .color = vert.calculateColor()};
        }
    };
    size_t xLeft = homoToPixel(left.hPosition().head(2)).x;
    size_t xRight = homoToPixel(right.hPosition().head(2)).x;

    if (xLeft == xRight) {
        if (left.hPosition().z() > right.hPosition().z()) {
            update_zbuffer(xLeft, row, left);
        } else {
            update_zbuffer(xLeft, row, right);
        }
        return;
    }
    if (xLeft > xRight) {
        std::swap(left, right);
        std::swap(xLeft, xRight);
    }
    for (size_t col = xLeft; col <= xRight; col++) {
        update_zbuffer(
            col, row,
            interpolate(left, right, getInterpolateCoeff(col, xLeft, xRight)));
    }
}

}  // namespace render_app
