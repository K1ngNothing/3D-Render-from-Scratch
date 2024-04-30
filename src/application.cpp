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
    // TODO: create scene from json or smth

    // Obama Pyramid
    Point3 A{2, 0, -2};
    Point3 B{-2, 0, -2};
    Point3 C{-2, 0, -6};
    Point3 D{2, 0, -6};
    Point3 E{0, 2, -4};

    // path is relative to build folder
    const sf::Image* obama_ptr =
        texture_manager_.loadFromFile("../../resources/textures/obama.jpg");
    auto [obama_w, obama_h] = obama_ptr->getSize();
    std::vector<TextureCoords> obama_coords{
        TextureCoords{          0, obama_h - 1, obama_ptr},
        TextureCoords{          0,           0, obama_ptr},
        TextureCoords{obama_w - 1,           0, obama_ptr},
        TextureCoords{obama_w - 1, obama_h - 1, obama_ptr},
        TextureCoords{obama_w / 2, obama_h / 2, obama_ptr},
    };

    auto createFaceTextures = [&obama_coords](
                                  const Point3& A, const Point3& B,
                                  const Point3& C, size_t t1, size_t t2,
                                  size_t t3) {
        return Triangle{
            Vertex{.pos = A, .tcoords = obama_coords[t1]},
            Vertex{.pos = B, .tcoords = obama_coords[t2]},
            Vertex{.pos = C, .tcoords = obama_coords[t3]},
        };
    };
    auto createFaceColor = [](const Point3& A, const Point3& B, const Point3& C,
                              const sf::Color& color) {
        return Triangle{
            Vertex{.pos = A, .color = color},
            Vertex{.pos = B, .color = color},
            Vertex{.pos = C, .color = color},
        };
    };
    // auto createFaceGradient = [](const Point3& A, const Point3& B,
    //                              const Point3& C) {
    //     return Triangle{
    //         Vertex{A,   sf::Color::Red},
    //         Vertex{B,  sf::Color::Blue},
    //         Vertex{C, sf::Color::Green},
    //     };
    // };
    sf::Color brown{94, 59, 41};
    std::vector<Triangle> triangles = {
        createFaceTextures(A, B, E, 3, 0, 4),
        createFaceTextures(B, C, E, 0, 1, 4),
        createFaceTextures(C, D, E, 1, 2, 4),
        createFaceTextures(D, A, E, 2, 3, 4),
        createFaceColor(A, B, C, brown),
        createFaceColor(A, C, D, brown),
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
