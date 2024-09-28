#pragma once

#include <optional>

#include <Camera.h>
#include <Renderer.h>
#include <Scene.h>
#include <SFML/Graphics.hpp>

#include "FrameMovement.h"

namespace Renderer3D {

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

}  // namespace Renderer3D
