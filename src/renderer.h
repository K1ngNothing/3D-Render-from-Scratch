#pragma once
#include "geometry.h"

namespace application {

class Renderer {
public:
    Renderer(size_t screen_w, size_t screen_h)
        : pixel_colors_(screen_w, std::vector<sf::Color>(screen_h, sf::Color::Black)),
          z_buffer_(screen_w, std::vector<double>(screen_h, 1)) {
    }

    void rasterizeTriangle(const Triangle& triangle);
    void renderImage(sf::RenderWindow& render_window) const;
    void clear();

private:
    std::pair<size_t, size_t> getScreenSize() const;

    std::vector<std::vector<sf::Color>> pixel_colors_;
    std::vector<std::vector<double>> z_buffer_;
};

}  // namespace application
