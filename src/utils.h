#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "geometry.h"

namespace render_app {

inline sf::Color& operator*=(sf::Color& color, double coeff) {
    color.r *= coeff;
    color.g *= coeff;
    color.b *= coeff;
    return color;
}

inline sf::Color operator*(const sf::Color& color, double coeff) {
    sf::Color res = color;
    res.r *= coeff;
    res.g *= coeff;
    res.b *= coeff;
    return res;
}

inline std::ostream& operator<<(std::ostream& os, const sf::Color& color) {
    os << "(" << static_cast<int>(color.r) << ", " << static_cast<int>(color.g)
       << ", " << static_cast<int>(color.b) << ")";
    return os;
}

inline bool inRange(double x, double lb, double rb) {
    return lb - g_eps <= x && x <= rb + g_eps;
}

inline sf::Vector2f operator*(sf::Vector2f vec1, sf::Vector2f vec2) {
    return sf::Vector2f{vec1.x * vec2.x, vec1.y * vec2.y};
}

inline std::ostream& operator<<(std::ostream& os, const Point3& point) {
    os << "(" << point.x() << ", " << point.y() << ", " << point.z() << ")";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Point4& point) {
    os << "(" << point.x() << ", " << point.y() << ", " << point.z() << ", "
       << point.w() << ")";
    return os;
}

}  // namespace render_app
