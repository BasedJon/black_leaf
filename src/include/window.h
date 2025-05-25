#pragma once

#include "std.h"
#include <SDL3/SDL.h>

typedef struct {
    SDL_Window* ptr;
    uint32_t w, h;
    const char* title;
    SDL_Event event;
    const uint8_t* keystate;
    SDL_Surface* surface;
    SDL_PixelFormatDetails* format;
    uint32_t* pixel_buffer;
} window;

void window_clean_up();
void window_init();
void window_create(SDL_Window** window, const char *title, uint32_t width, uint32_t height);
void window_init_pixel_buffer(SDL_Window* window, SDL_Surface** surface, uint32_t** buffer, SDL_PixelFormatDetails** format, uint32_t window_width, uint32_t window_height);
void window_update(SDL_Window* window, SDL_Surface* surface, uint32_t* pixel_buffer, uint32_t window_width, uint32_t window_height);