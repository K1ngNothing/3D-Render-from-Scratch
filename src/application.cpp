#include "application.h"

#include "settings.h"

namespace application {

Application::Application()
    : render_window_(sf::VideoMode(settings::k_window_w, settings::k_window_h),
                     settings::window_name) {
    // some scene for testing
    Triangle triangle1 = Triangle{
        Point3{-2,  4, -4},
        Point3{ 6,  3, -8},
        Point3{-8, -4, -9},
        sf::Color::Red
    };
    world_.addObject(Object{std::vector<Triangle>{triangle1}});
}

void Application::run() {
    // At the moment produces static image
    // Therefore we draw one frame and then waiting for window's closing
    drawFrame();
    while (render_window_.isOpen()) {
        handleEvents();
    }
}

void Application::handleEvents() {
    // At the moment only checks for window's closing
    sf::Event event;
    while (render_window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            render_window_.close();
            return;
        }
    }
}

void Application::drawFrame() {
    Image image = renderer_.renderImage(camera_, world_);
    render_window_.draw(&image[0], image.size(), sf::PrimitiveType::Points);
    render_window_.display();
}

}  // namespace application
