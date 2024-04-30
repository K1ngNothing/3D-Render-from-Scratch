#pragma once

#include <SFML/Graphics.hpp>

#include "camera.h"
#include "frame_movement.h"
#include "renderer.h"
#include "textures.h"
#include "world.h"

namespace render_app {

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
    TextureManager texture_manager_;
};

}  // namespace render_app
