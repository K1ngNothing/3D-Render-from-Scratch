#pragma once

#include <SFML/Graphics.hpp>

#include "camera.h"
#include "frame_movement.h"
#include "renderer.h"
#include "world.h"

namespace render_app {

class Application {
public:
    Application();
    void run();

private:
    void createScene();

    FrameMovement calculateCameraMovement(double delta_time) const;
    void draw(const Image& image);
    void closeWindowIfAsked();

    sf::RenderWindow render_window_;
    Renderer renderer_;
    Camera camera_;
    World world_;
};

}  // namespace render_app
