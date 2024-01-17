#include "application.h"

namespace application {

void Application::run() {
    // Testing renderer functionality
    renderer_.rasterizeTriangle(Triangle{Point3d{0.8, 0.6, 1}, Point3d{0.3, 0.2, -1},
                                         Point3d{0.5, 0.7, 0}, sf::Color::Red});
    renderer_.rasterizeTriangle(Triangle{Point3d{0.4, 0.6, -0.5}, Point3d{0.5, 0.1, 0.5},
                                         Point3d{0.9, 0.7, 0.5}, sf::Color::Blue});
    renderer_.render(render_window_);
    render_window_.display();
    while (render_window_.isOpen()) {
        sf::Event event;
        while (render_window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                render_window_.close();
                return;
            }
        }
    }
}

}  // namespace application
