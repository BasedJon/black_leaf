#pragma once

#include "std.h"
#include "3d_types.h"
#include "window.h"

void draw_line(int v1_x, int v1_y, int v2_x, int v2_y, uint32_t** pixel_buffer, uint32_t color, uint32_t viewport_width, uint32_t viewport_height);
void draw_triangle(vec3 a, vec3 b, vec3 c, window* win, uint32_t** pixel_buffer, float* z_buffer, uint32_t viewport_width, uint32_t viewport_height);