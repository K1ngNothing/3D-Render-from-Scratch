#pragma once

#include <cstddef>
#include <numbers>

namespace render_app {

namespace settings {
// window
constexpr char window_name[] = "3D Renderer from Scratch";
constexpr size_t k_window_w = 1000;
constexpr size_t k_window_h = 1000;
constexpr size_t k_framerate_limit = 30;

// camera
constexpr double k_fov_angle = std::numbers::pi / 2;
constexpr double k_near_plane_dist = 0.3;
constexpr double k_far_plane_dist = 10.0;
constexpr double k_aspect_ratio = static_cast<double>(k_window_h) / k_window_w;

// renderer
constexpr double k_min_distant_shade_coeff = 0.3;

// movement
constexpr double k_camera_movement_speed = 1.75;
constexpr double k_camera_turning_speed = 2.4 / std::numbers::pi * k_fov_angle;
}  // namespace settings

}  // namespace render_app
