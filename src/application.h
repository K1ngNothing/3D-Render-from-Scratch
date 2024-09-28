#pragma once

#include <optional>

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

    std::optional<FrameMovement> getCameraMovementFromKeyboard() const;
    Point3 getCameraShiftFromKeyboard() const;
    double getCameraPitchFromKeyboard() const;
    double getCameraYawFromKeyboard() const;
    double getCameraRollFromKeyboard() const;

    void draw(const Image& image);
    void closeWindowIfAsked();

    sf::RenderWindow render_window_;
    Renderer renderer_;
    Camera camera_;
    World world_;
};

}  // namespace render_app
