#include "application.h"

#include "scenes.h"
#include "settings.h"

namespace render_app {

Application::Application()
    : render_window_(
          sf::VideoMode(settings::k_window_w, settings::k_window_h),
          settings::window_name) {
    render_window_.setFramerateLimit(settings::k_framerate_limit);
    createScene();
}

void Application::run() {
    sf::Clock frame_clock;
    while (render_window_.isOpen()) {
        double delta_time = frame_clock.restart().asSeconds();
        FrameMovement camera_movement = calculateCameraMovement(delta_time);
        camera_.moveCamera(camera_movement);
        Image image = renderer_.renderImage(camera_, world_);
        draw(image);
        closeWindowIfAsked();
    }
}

void Application::createScene() {
    // world_.addObject(createGradientPyramid());
    world_.addObject(createEgyptianPyramid(world_));
}

FrameMovement Application::calculateCameraMovement(double delta_time) const {
    double movement_val = settings::k_camera_movement_speed * delta_time;
    double turning_val = settings::k_camera_turning_speed * delta_time;

    // movement
    Point3 shift = Point3::Zero();
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

    // turning
    double turn_up = 0, turn_right = 0, turn_clockwise = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        turn_up += turning_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        turn_up -= turning_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        turn_right += turning_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        turn_right -= turning_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        turn_clockwise += turning_val;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        turn_clockwise -= turning_val;
    }
    return FrameMovement{
        .shift = shift,
        .turn_up = turn_up,
        .turn_right = turn_right,
        .turn_clockwise = turn_clockwise};
}

void Application::draw(const Image& image) {
    render_window_.draw(&image[0], image.size(), sf::PrimitiveType::Points);
    render_window_.display();
}

void Application::closeWindowIfAsked() {
    sf::Event event;
    while (render_window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed ||
            (event.KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            render_window_.close();
            return;
        }
    }
}

}  // namespace render_app
