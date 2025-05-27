#include "rasterizer.h"

void draw_line(int v1_x, int v1_y, int v2_x, int v2_y, uint32_t** pixel_buffer, uint32_t color, uint32_t viewport_width, uint32_t viewport_height) {
    uint32_t buffer_index;
    int delta_x, delta_y, error_delta_y, error_value;
    bool slope_is_steep = false;

    v1_x = clamp_int(v1_x, 0, viewport_width);
    v2_x = clamp_int(v2_x, 0, viewport_width);
    v1_y = clamp_int(v1_y, 0, viewport_height);
    v2_y = clamp_int(v2_y, 0, viewport_height);


    if (abs(v1_y - v2_y) >  abs(v1_x - v2_x)) {
        swap_int(&v1_x, &v1_y);
        swap_int(&v2_x, &v2_y);
        slope_is_steep = true;
    }

    if (v1_x > v2_x) {
        swap_int(&v1_x, &v2_x);
        swap_int(&v1_y, &v2_y);
    }

    delta_x = v2_x - v1_x;
    delta_y = v2_y - v1_y;
    error_delta_y = abs(delta_y) * 2;
    error_value = 0;

    for (int x = v1_x, y = v1_y; x < v2_x; x++) {
        if (slope_is_steep) {
            buffer_index = x * viewport_width + y;
        }
        else { 
            buffer_index = y * viewport_width + x;
        }
        if (buffer_index >= viewport_width * viewport_height) continue;
        (*pixel_buffer)[buffer_index] = color;
        error_value += error_delta_y;
        if (error_value > delta_x) {
            if (v2_y > v1_y) y++;
            else y--;
            error_value -= delta_x * 2;
        }
    }
}
