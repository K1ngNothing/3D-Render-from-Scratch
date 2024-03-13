#include "renderer.h"

#include <cassert>

namespace application {

namespace {

// FIXME
double interpolateZ(const Point2d& X, const Triangle& triangle) {
    double sum_of_distances = 0;
    for (const Point3d& point : triangle.points) {
        sum_of_distances += (X - Point2d(point.x(), point.y())).norm();
    }
    double result = 0;
    for (const Point3d& point : triangle.points) {
        double distance = (X - Point2d(point.x(), point.y())).norm();
        double coeff = (sum_of_distances - distance) / (2 * sum_of_distances);
        result += point.z() * coeff;
    }
    return result;
}

}  // namespace

Image Renderer::renderImage(const Camera& camera, const World& world) {
    return createImage(zBufferAlgorithm(camera, world));
}

Renderer::ZBuffer Renderer::zBufferAlgorithm(const Camera& camera,
                                             const World& world) {
    ZBuffer z_buffer(screen_w_, std::vector<Pixel>(screen_h_));
    for (const Triangle& triangle : world.getTriangles()) {
        rasterizeTriangle(camera.transformTriangle(triangle), z_buffer);
    }
    return z_buffer;
}

void Renderer::rasterizeTriangle(const Triangle& triangle,
                                 Renderer::ZBuffer& z_buffer_) {
    double min_x = 1, min_y = 1, max_x = -1, max_y = -1;
    for (const Point3d& point : triangle.points) {
        assert(-1 - k_eps <= point.x() && point.x() <= 1 + k_eps &&
               -1 - k_eps <= point.y() && point.y() <= 1 + k_eps &&
               "Triangle passed in renderer has unscaled coordinates");
        min_x = std::min(min_x, point.x());
        min_y = std::min(min_y, point.y());

        max_x = std::max(max_x, point.x());
        max_y = std::max(max_y, point.y());
    }
    double dx = 2.0 / screen_w_, dy = 2.0 / screen_h_;
    size_t min_pixel_x = floor((min_x + 1) / dx);
    size_t max_pixel_x = ceil((max_x + 1) / dx);
    size_t min_pixel_y = floor((min_y + 1) / dy);
    size_t max_pixel_y = ceil((max_y + 1) / dy);
    for (size_t pixel_x = min_pixel_x; pixel_x <= max_pixel_x; pixel_x++) {
        for (size_t pixel_y = min_pixel_y; pixel_y <= max_pixel_y; pixel_y++) {
            double double_x = pixel_x * dx - 1;
            double double_y = pixel_y * dy - 1;
            double interpolated_z =
                interpolateZ(Point2d(double_x, double_y), triangle);
            if (isPointInsideTriangle2D({double_x, double_y}, triangle) &&
                z_buffer_[pixel_x][pixel_y].depth > interpolated_z + k_eps) {
                z_buffer_[pixel_x][pixel_y].depth = interpolated_z;
                z_buffer_[pixel_x][pixel_y].color = triangle.color;
            }
        }
    }
}

Image Renderer::createImage(const ZBuffer& z_buffer_) {
    Image image;
    image.reserve(screen_h_ * screen_w_);
    for (size_t i = 0; i < screen_w_; i++) {
        for (size_t j = 0; j < screen_h_; j++) {
            sf::Vector2f position{static_cast<float>(i),
                                  static_cast<float>(screen_h_ - j)};
            sf::Color color = z_buffer_[i][j].color;

            // FIXME
            // double shade_coeff = 1 - (z_buffer_[i][j] + 1) / 2;
            double shade_coeff = 1;
            color.r *= shade_coeff;
            color.g *= shade_coeff;
            color.b *= shade_coeff;
            image.emplace_back(position, color);
        }
    }
    return image;
}

}  // namespace application
