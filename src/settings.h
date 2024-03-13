#pragma once

#include <math.h>

namespace application {

namespace settings {
static constexpr char window_name[] = "3D Renderer from Scratch";
static constexpr size_t k_window_w = 1000;
static constexpr size_t k_window_h = 1000;

// maybe split in sub namespaces?
static constexpr double k_fov_angle = M_PI / 2;
static constexpr double k_near_plane_dist = 1.0;
static constexpr double k_far_plane_dist = 10.0;
static constexpr double aspect_ratio =
    static_cast<double>(k_window_w) / k_window_h;

}  // namespace settings

}  // namespace application
