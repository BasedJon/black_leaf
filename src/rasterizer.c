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

void draw_triangle(vec3 a, vec3 b, vec3 c, window* win, uint32_t** pixel_buffer, float* z_buffer, uint32_t viewport_width, uint32_t viewport_height) {
    int min_x = (int)fmaxf(0, floorf(fminf(fminf(a.x, b.x), c.x)));
    int max_x = (int)fminf((float)(viewport_width - 1), ceilf(fmaxf(fmaxf(a.x, b.x), c.x)));
    int min_y = (int)fmaxf(0, floorf(fminf(fminf(a.y, b.y), c.y)));
    int max_y = (int)fminf((float)(viewport_height - 1), ceilf(fmaxf(fmaxf(a.y, b.y), c.y)));

    float denom = (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
    uint8_t ar = 0, ag = 255, ab = 0;
    uint8_t br = 255, bg = 0, bb = 0;
    uint8_t cr = 0, cg = 0, cb = 255;

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float w0 = ((b.x - px)*(c.y - py) - (c.x - px)*(b.y - py)) / denom;
            float w1 = ((c.x - px)*(a.y - py) - (a.x - px)*(c.y - py)) / denom;
            float w2 = 1.0f - w0 - w1;

            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                float depth = w0 * a.z + w1 * b.z + w2 * c.z;

                int index = y * viewport_width + x;
                if (depth > z_buffer[index]) {
                    z_buffer[index] = depth;
                    uint8_t r = (uint8_t)(w0 * ar + w1 * br + w2 * cr);
                    uint8_t g = (uint8_t)(w0 * ag + w1 * bg + w2 * cg);
                    uint8_t b = (uint8_t)(w0 * ab + w1 * bb + w2 * cb);

                    (*pixel_buffer)[index] = SDL_MapRGBA(win->format, NULL, r, g, b, 255);
                }
            }
        }
    }
}
