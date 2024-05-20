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
        FrameMovement camera_movement = getCameraMovementFromKeyboard();
        camera_movement *= frame_clock.restart().asSeconds();
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

FrameMovement Application::getCameraMovementFromKeyboard() const {
    return FrameMovement{
        .shift = getCameraShiftFromKeyboard(),
        .pitch = getCameraPitchFromKeyboard(),
        .yaw = getCameraYawFromKeyboard(),
        .roll = getCameraRollFromKeyboard()};
}

Point3 Application::getCameraShiftFromKeyboard() const {
    Point3 shift = Point3::Zero();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        shift.z() -= settings::k_camera_movement_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        shift.z() += settings::k_camera_movement_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        shift.x() += settings::k_camera_movement_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        shift.x() -= settings::k_camera_movement_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        shift.y() += settings::k_camera_movement_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        shift.y() -= settings::k_camera_movement_speed;
    }
    return shift;
}

double Application::getCameraPitchFromKeyboard() const {
    double pitch = 0.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pitch += settings::k_camera_turning_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pitch -= settings::k_camera_turning_speed;
    }
    return pitch;
}

double Application::getCameraYawFromKeyboard() const {
    double yaw = 0.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        yaw += settings::k_camera_turning_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        yaw -= settings::k_camera_turning_speed;
    }
    return yaw;
}

double Application::getCameraRollFromKeyboard() const {
    double roll = 0.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        roll += settings::k_camera_turning_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        roll -= settings::k_camera_turning_speed;
    }
    return roll;
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
