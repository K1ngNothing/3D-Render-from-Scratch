#pragma once

#include <cstddef>
#include <numbers>

namespace application {

namespace settings {
constexpr char window_name[] = "3D Renderer from Scratch";
constexpr size_t k_window_w = 1000;
constexpr size_t k_window_h = 1000;

// maybe split in sub namespaces?
constexpr double k_fov_angle = std::numbers::pi / 2;
constexpr double k_near_plane_dist = 1.0;
constexpr double k_far_plane_dist = 10.0;
constexpr double aspect_ratio = static_cast<double>(k_window_w) / k_window_h;

}  // namespace settings

}  // namespace application
