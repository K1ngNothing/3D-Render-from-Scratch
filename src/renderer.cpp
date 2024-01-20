#include "renderer.h"

#include <iostream>

namespace application {

namespace {

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

void Renderer::rasterizeTriangle(const Triangle& triangle) {
    double min_x = 1, min_y = 1, max_x = -1, max_y = -1;
    for (const Point3d& point : triangle.points) {
        assert(-1 - EPS <= point.x() && point.x() <= 1 + EPS && -1 - EPS <= point.y() &&
               point.y() <= 1 + EPS && "Triangle passed in renderer has unscaled coordinates");
        min_x = std::min(min_x, point.x());
        min_y = std::min(min_y, point.y());

        max_x = std::max(max_x, point.x());
        max_y = std::max(max_y, point.y());
    }
    auto [screen_w, screen_h] = getScreenSize();
    double dx = 2.0 / screen_w, dy = 2.0 / screen_h;
    size_t min_pixel_x = floor((min_x + 1) / dx);
    size_t max_pixel_x = ceil((max_x + 1) / dx);
    size_t min_pixel_y = floor((min_y + 1) / dy);
    size_t max_pixel_y = ceil((max_y + 1) / dy);
    for (size_t pixel_x = min_pixel_x; pixel_x <= max_pixel_x; pixel_x++) {
        for (size_t pixel_y = min_pixel_y; pixel_y <= max_pixel_y; pixel_y++) {
            double double_x = pixel_x * dx - 1;
            double double_y = pixel_y * dy - 1;
            double interpolated_z = interpolateZ(Point2d(double_x, double_y), triangle);
            if (isPointInsideTriangle2D({double_x, double_y}, triangle) &&
                z_buffer_[pixel_x][pixel_y] > interpolated_z + EPS) {
                z_buffer_[pixel_x][pixel_y] = interpolated_z;
                pixel_colors_[pixel_x][pixel_y] = triangle.color;
            }
        }
    }
}

void Renderer::renderImage(sf::RenderWindow& render_window) const {
    auto [screen_w, screen_h] = getScreenSize();
    std::vector<sf::Vertex> pixels;
    for (size_t i = 0; i < screen_w; i++) {
        for (size_t j = 0; j < screen_h; j++) {
            sf::Vector2f position{static_cast<float>(i), static_cast<float>(screen_h - j)};
            sf::Color color = pixel_colors_[i][j];

            // FIXME
            // double shade_coeff = 1 - (z_buffer_[i][j] + 1) / 2;
            double shade_coeff = 1;
            color.r *= shade_coeff;
            color.g *= shade_coeff;
            color.b *= shade_coeff;
            pixels.emplace_back(position, color);
        }
    }
    render_window.draw(&pixels[0], pixels.size(), sf::PrimitiveType::Points);
}

void Renderer::clear() {
    auto [screen_w, screen_h] = getScreenSize();
    for (size_t i = 0; i < screen_w; i++) {
        for (size_t j = 0; j < screen_h; j++) {
            pixel_colors_[i][j] = sf::Color::Black;
            z_buffer_[i][j] = 1;
        }
    }
}

std::pair<size_t, size_t> Renderer::getScreenSize() const {
    assert(!pixel_colors_.empty() && "Empty screen in renderer");
    return {pixel_colors_.size(), pixel_colors_[0].size()};
}

}  // namespace application
