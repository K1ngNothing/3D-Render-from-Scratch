#pragma once
#include <math.h>

#include <SFML/Graphics.hpp>

#include "camera.h"
#include "renderer.h"
#include "world.h"

namespace application {

class Application {
public:
    Application();

    void run();
    void addObjects(std::vector<Triangle> triangles, Point3d position = Point3d::Zero());

private:
    static constexpr char window_name[] = "3D Renderer from Scratch";
    static constexpr size_t window_w = 1000;
    static constexpr size_t window_h = 1000;
    static constexpr double aspect_ratio = static_cast<double>(window_w) / window_h;
    static constexpr double fov_angle = M_PI / 2;
    static constexpr double near_plane_dist = 1.0;
    static constexpr double far_plane_dist = 10.0;

    void checkEvents();
    void updateRenderWindow();
    void displayImage();

    sf::RenderWindow render_window_;
    Renderer renderer_;
    Camera camera_;
    World world_;
};

}  // namespace application
