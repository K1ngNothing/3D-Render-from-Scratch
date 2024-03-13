#pragma once

#include <SFML/Graphics.hpp>

#include "camera.h"
#include "renderer.h"
#include "world.h"

namespace application {

class Application {
public:
    Application();
    void run();

private:
    void handleEvents();
    void drawFrame();

    sf::RenderWindow render_window_;
    Renderer renderer_;
    Camera camera_;
    World world_;
};

}  // namespace application
