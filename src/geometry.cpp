#include "geometry.h"

namespace application {

namespace {
Point2 get2dPoint(const Point3& X) {
    return {X.x(), X.y()};
}
}  // namespace

Triangle& Triangle::operator+=(const Point3& shift) {
    for (Point3& point : points) {
        point += shift;
    }
    return *this;
}

bool isPointInsideTriangle2D(const Point2& X, const Triangle& triangle) {
    auto calcArea = [](const Point2& A, const Point2& B, const Point2& C) {
        return abs((B - A).cross(C - A) / 2);
    };
    Point2 A = get2dPoint(triangle.points[0]);
    Point2 B = get2dPoint(triangle.points[1]);
    Point2 C = get2dPoint(triangle.points[2]);
    double actual_area = calcArea(A, B, C);
    double supposed_area =
        calcArea(X, A, B) + calcArea(X, B, C) + calcArea(X, C, A);
    return abs(actual_area - supposed_area) < g_eps;
}

}  // namespace application
