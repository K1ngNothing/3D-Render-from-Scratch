#include <application.h>

#include <iostream>

int main() {
    using namespace application;
    Application app;
    app.run();

    // TESTING
    // Triangle triangle{Point3d{0.8, 0.6, 1}, Point3d{0.3, 0.2, -1}, Point3d{0.5, 0.7, 0},
    //                   sf::Color::Red};
    // Point2d P{0.5, 0.5};
    // std::cout << interpolateZ(P, triangle) << "\n";
}
