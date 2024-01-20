#include "application.h"

#include <chrono>
#include <iostream>

namespace application {

Application::Application()
    : render_window_(sf::VideoMode(window_w, window_h), window_name),
      renderer_(window_w, window_h),
      camera_(near_plane_dist, far_plane_dist, fov_angle, aspect_ratio) {
}

void Application::run() {
    // At the moment produces static image
    updateRenderWindow();
    displayImage();
    while (render_window_.isOpen()) {
        checkEvents();
    }
}

void Application::addObjects(std::vector<Triangle> triangles, Point3d position) {
    world_.addObjects(std::move(triangles), std::move(position));
}

void Application::checkEvents() {
    // At the moment checks only for closing a window
    sf::Event event;
    while (render_window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            render_window_.close();
            exit(0);
        }
    }
}

void Application::updateRenderWindow() {
    renderer_.clear();
    for (Triangle& triangle : world_.getTriangles()) {
        triangle = camera_.transformTriangle(triangle);
        renderer_.rasterizeTriangle(triangle);
    }
    renderer_.renderImage(render_window_);
}

void Application::displayImage() {
    render_window_.display();
}

}  // namespace application
