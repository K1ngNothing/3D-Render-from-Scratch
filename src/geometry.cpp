#include "geometry.h"

namespace application {
namespace {
Point2d get2dPoint(const Point3d& X) {
    return {X.x(), X.y()};
}
}  // namespace

bool isPointInsideTriangle2D(const Point2d& X, const Triangle& triangle) {
    auto calcArea = [](const Point2d& A, const Point2d& B, const Point2d& C) {
        return abs((B - A).cross(C - A) / 2);
    };
    Point2d A = get2dPoint(triangle.points[0]);
    Point2d B = get2dPoint(triangle.points[1]);
    Point2d C = get2dPoint(triangle.points[2]);
    double actual_area = calcArea(A, B, C);
    double supposed_area = calcArea(X, A, B) + calcArea(X, B, C) + calcArea(X, C, A);
    return (abs(actual_area - supposed_area) < EPS);
}

}  // namespace application
