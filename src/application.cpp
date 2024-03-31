#include "application.h"

#include "settings.h"

namespace application {

Application::Application()
    : render_window_(sf::VideoMode(settings::k_window_w, settings::k_window_h),
                     settings::window_name) {
    render_window_.setFramerateLimit(settings::k_framerate_limit);
    createScene();
}

void Application::run() {
    sf::Clock frame_clock;
    while (render_window_.isOpen()) {
        double delta_time = frame_clock.restart().asSeconds();
        FrameMovement camera_movement = getUserInputs(delta_time);
        camera_.moveCamera(camera_movement);
        drawFrame();
        checkWindowClosing();
    }
}

void Application::createScene() {
    // Pyramid
    Vertex A{
        Point3{0, 0, -1},
        sf::Color::Blue
    };
    Vertex B{
        Point3{0, 0, -5},
        sf::Color::Cyan
    };
    Vertex C{
        Point3{3, 0, -3},
        sf::Color::Magenta
    };
    Vertex D{
        Point3{-3, 0, -3},
        sf::Color::Yellow
    };
    Vertex E{
        Point3{0, 3, -3},
        sf::Color::Green
    };
    std::vector<Triangle> triangles = {
        Triangle{A, B, C},
        Triangle{A, B, D},
        Triangle{A, C, E},
        Triangle{C, B, E},
        Triangle{B, D, E},
        Triangle{D, A, E},
    };
    // std::vector<Triangle> triangles = {
    //     Triangle{D, E, C},
    // };
    //     Vertex A{
    //         Point3{-0.9, 0, -1},
    //         sf::Color::Red
    //     };
    //     Vertex B{
    //         Point3{0.9, 0, -1},
    //         sf::Color::Green
    //     };
    //     Vertex C{
    //         Point3{0, 2, -1},
    //         sf::Color::Blue
    //     };
    //     Vertex D{
    //         Point3{0, -2, -1},
    //         sf::Color::Blue
    //     };
    //     std::vector<Triangle> triangles = {
    //         Triangle{A, B, C},
    //  // Triangle{A, B, D}
    //     };
    world_.addObject(Object{triangles});
}

void Application::checkWindowClosing() {
    sf::Event event;
    while (render_window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            render_window_.close();
            return;
        }
    }
}

FrameMovement Application::getUserInputs(double delta_time) {
    Point3 shift = Point3::Zero();
    double movement_val = settings::k_camera_movement_speed * delta_time;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        shift.z() -= movement_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        shift.z() += movement_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        shift.x() += movement_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        shift.x() -= movement_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shift.y() += movement_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        shift.y() -= movement_val;
    }
    return FrameMovement{shift};
}

void Application::drawFrame() {
    Image image = renderer_.renderImage(camera_, world_);
    render_window_.draw(&image[0], image.size(), sf::PrimitiveType::Points);
    render_window_.display();
}

}  // namespace application
