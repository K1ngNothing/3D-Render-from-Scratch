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
    void addObjects(std::vector<Triangle> triangles,
                    Point3d position = Point3d::Zero());

private:
    static constexpr char window_name[] = "3D Renderer from Scratch";
    static constexpr size_t k_window_w_ = 1000;
    static constexpr size_t k_window_h_ = 1000;

    void handleEvents();
    void updateRenderWindow();
    void displayRenderWindow();

    sf::RenderWindow render_window_;
    Renderer renderer_;
    Camera camera_;
    World world_;
};

}  // namespace application
