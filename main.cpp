#include <application.h>

#include <iostream>

int main() {
    // just some testing
    using namespace application;
    Application app;

    Triangle triangle1 = Triangle{
        Point3d{-2,  4, -4},
        Point3d{ 6,  3, -8},
        Point3d{-8, -4, -9},
        sf::Color::Red
    };
    app.addObjects({triangle1});
    app.run();
}
