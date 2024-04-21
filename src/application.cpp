#include "application.h"

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
        FrameMovement camera_movement = getUserInputs(delta_time);
        camera_.moveCamera(camera_movement);
        drawFrame();
        checkWindowClosing();
    }
}

void Application::createScene() {
    // Pyramid
    Point3 A{0, 0, -2};
    Point3 B{0, 0, -6};
    Point3 C{2, 0, -4};
    Point3 D{-2, 0, -4};
    Point3 E{0, 2, -4};

    auto createFace = [](const Point3& A, const Point3& B, const Point3& C,
                         const sf::Color& color) {
        return Triangle{
            Vertex{A, color},
            Vertex{B, color},
            Vertex{C, color},
        };
    };
    auto createFaceGradient = [](const Point3& A, const Point3& B,
                                 const Point3& C) {
        return Triangle{
            Vertex{A,   sf::Color::Red},
            Vertex{B,  sf::Color::Blue},
            Vertex{C, sf::Color::Green},
        };
    };
    // std::vector<Triangle> triangles = {
    //     createFace(A, E, C, sf::Color::Blue),
    //     createFace(A, E, D, sf::Color::Magenta),
    //     createFace(B, E, D, sf::Color::Cyan),
    //     createFace(B, E, C, sf::Color::Green),
    //     createFace(A, B, D, sf::Color::Red),
    //     createFace(A, B, C, sf::Color::Red),
    // };
    std::vector<Triangle> triangles = {
        createFaceGradient(A, E, C),
        createFaceGradient(A, E, D),
        createFaceGradient(B, E, D),
        createFaceGradient(B, E, C),
        createFace(A, B, D, sf::Color::Red),
        createFace(A, B, C, sf::Color::Red),
    };
    world_.addObject(Object{std::move(triangles)});
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

void Application::drawFrame() {
    Image image = renderer_.renderImage(camera_, world_);
    render_window_.draw(&image[0], image.size(), sf::PrimitiveType::Points);
    render_window_.display();
}

}  // namespace render_app
