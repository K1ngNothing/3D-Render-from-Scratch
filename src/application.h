#pragma once

#include <SFML/Graphics.hpp>

#include "camera.h"
#include "frame_movement.h"
#include "renderer.h"
#include "world.h"

namespace application {

class Application {
public:
    Application();
    void run();

private:
    void createScene();
    void checkWindowClosing();
    FrameMovement getUserInputs(double delta_time);
    void drawFrame();

    sf::RenderWindow render_window_;
    Renderer renderer_;
    Camera camera_;
    World world_;
};

}  // namespace application
