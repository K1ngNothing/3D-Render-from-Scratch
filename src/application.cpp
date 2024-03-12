#include "application.h"

namespace application {

Application::Application()
    : render_window_(sf::VideoMode(k_window_w_, k_window_h_), window_name),
      renderer_(k_window_w_, k_window_h_),
      camera_(static_cast<double>(k_window_w_) / k_window_h_) {
}

void Application::run() {
    // At the moment produces static image
    updateRenderWindow();
    displayRenderWindow();
    while (render_window_.isOpen()) {
        handleEvents();
    }
}

void Application::addObjects(std::vector<Triangle> triangles,
                             Point3d position) {
    world_.addObject(std::move(triangles), std::move(position));
}

void Application::handleEvents() {
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
    Image image = renderer_.renderImage(camera_, world_);
    render_window_.draw(&image[0], image.size(), sf::PrimitiveType::Points);
}

void Application::displayRenderWindow() {
    render_window_.display();
}

}  // namespace application
