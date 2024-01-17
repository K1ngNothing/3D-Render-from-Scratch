#pragma once
#include <SFML/Graphics.hpp>

#include "renderer.h"

namespace application {

class Application {
public:
    Application()
        : render_window_(sf::VideoMode(window_w, window_h), window_name),
          renderer_(window_w, window_h) {
    }

    void run();

private:
    static constexpr size_t window_w = 1000;
    static constexpr size_t window_h = 1000;
    static constexpr char window_name[] = "3D Renderer from Scratch";

    sf::RenderWindow render_window_;
    Renderer renderer_;
};

}  // namespace application
