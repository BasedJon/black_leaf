#include "window.h"

// SDL
void window_clean_up() {
    // TO DO
}

void window_init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == false) {
        const char* error = SDL_GetError();
        printf("%s", error);
    }
}

void window_create(SDL_Window** window, const char *title, uint32_t width, uint32_t height) {
    *window = SDL_CreateWindow(title, width, height, 0);
    if (*window == NULL) {
        const char* error = SDL_GetError();
        printf("%s", error);
    }
}

void window_init_pixel_buffer(SDL_Window* window, SDL_Surface** surface, uint32_t** buffer, SDL_PixelFormatDetails** format, uint32_t window_width, uint32_t window_height) {
    *surface = SDL_GetWindowSurface(window);
    *format = SDL_GetPixelFormatDetails((*surface)->format);
    uint32_t* buffer_ptr = (uint32_t*)malloc(window_width * window_height * sizeof(uint32_t));
    *buffer = (*surface)->pixels;
}

void window_update(SDL_Window* window, SDL_Surface* surface, uint32_t* pixel_buffer, uint32_t window_width, uint32_t window_height) {
    memcpy(surface->pixels, pixel_buffer, window_width * window_height * sizeof(uint32_t)); // tehcnically unesesary 
    SDL_UpdateWindowSurface(window);
}