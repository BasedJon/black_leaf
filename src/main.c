#include "window.h"
#include "std.h"
#include "obj_parser.h"
#include "rasterizer.h"
#include "3d_types.h"
#include "3d_math.h"
#include "graphics_pipeline.h"
#include "project.h"

vertex_buffer dvb;
uint32_t* dvb_indices = NULL;
uint32_t dvb_indices_count;
mat4 debug_model;
const char* debug_mesh = "obj_data/cube.obj";

camera debug_cam = {
{ 0.0f, 0.0f, 10.0f },
{ 0.0f, 0.0f, 0.0f },
{ 0.0f, 1.0f, 0.0f },
};

void debug_render(window* win) {
    for (size_t i = 0; i < dvb_indices_count; i += 3) {
        uint32_t line_color = SDL_MapRGBA(win->format, NULL, 255, 255, 255, 255);
        uint8_t* mem_ptr = (uint8_t*)dvb.data;

        vec4 va = *(vec4*)(mem_ptr + dvb_indices[i] * dvb.stride + 0);
        vec4 vb = *(vec4*)(mem_ptr + dvb_indices[i + 1] * dvb.stride + 0);
        vec4 vc = *(vec4*)(mem_ptr + dvb_indices[i + 2] * dvb.stride + 0);

        va = mat4_vec4_mult(&debug_model, va);
        vb = mat4_vec4_mult(&debug_model, vb);
        vc = mat4_vec4_mult(&debug_model, vc);

        va = mat4_vec4_mult(&debug_cam.view, va);
        vb = mat4_vec4_mult(&debug_cam.view, vb);
        vc = mat4_vec4_mult(&debug_cam.view, vc);

        va = mat4_vec4_mult(&debug_cam.projection, va);
        vb = mat4_vec4_mult(&debug_cam.projection, vb);
        vc = mat4_vec4_mult(&debug_cam.projection, vc);

        // back cull
        // normals
        // clipping

        vec3 va_viewport = ndc_to_viewport(vec4_to_ndc(va), win->w, win->h);
        vec3 vb_viewport = ndc_to_viewport(vec4_to_ndc(vb), win->w, win->h);
        vec3 vc_viewport = ndc_to_viewport(vec4_to_ndc(vc), win->w, win->h);

        draw_line(va_viewport.x, va_viewport.y, vb_viewport.x, vb_viewport.y, &win->pixel_buffer, line_color, win->w, win->h);
        draw_line(vb_viewport.x, vb_viewport.y, vc_viewport.x, vc_viewport.y, &win->pixel_buffer, line_color, win->w, win->h);
        draw_line(vc_viewport.x, vc_viewport.y, va_viewport.x, va_viewport.y, &win->pixel_buffer, line_color, win->w, win->h);
    }
}

void debug_controls(float speed, window* win) {

    if (win->keystate[SDL_SCANCODE_LEFT] == true) {
        mat4 yaw_matrix = mat4_rotate_yaw(speed * 0.5);
        debug_model = mat4_mult(&debug_model, &yaw_matrix);
    }
    if (win->keystate[SDL_SCANCODE_RIGHT] == true) {
        mat4 yaw_matrix = mat4_rotate_yaw(-speed * 0.5);
        debug_model = mat4_mult(&debug_model, &yaw_matrix);
    }
    if (win->keystate[SDL_SCANCODE_UP] == true) {
        mat4 pitch_matrix = mat4_rotate_pitch(speed * 0.5);
        debug_model = mat4_mult(&debug_model, &pitch_matrix);
    }
    if (win->keystate[SDL_SCANCODE_DOWN] == true) {
        mat4 pitch_matrix = mat4_rotate_pitch(-speed * 0.5);
        debug_model = mat4_mult(&debug_model, &pitch_matrix);
    }

    if (win->keystate[SDL_SCANCODE_D] == true) {
        vec3 translation_values = {-speed * 0.5, 0.0f, 0.0f};
        mat4 translation_matrix = mat4_translation(translation_values);
        debug_model = mat4_mult(&debug_model, &translation_matrix);
    }
    if (win->keystate[SDL_SCANCODE_A] == true) {
        vec3 translation_values = {speed * 0.5, 0.0f, 0.0f};
        mat4 translation_matrix = mat4_translation(translation_values);
        debug_model = mat4_mult(&debug_model, &translation_matrix);
    }
    if (win->keystate[SDL_SCANCODE_LSHIFT] == true) {
        vec3 translation_values = {0.0f, -speed * 0.5, 0.0f};
        mat4 translation_matrix = mat4_translation(translation_values);
        debug_model = mat4_mult(&debug_model, &translation_matrix);
    }
    if (win->keystate[SDL_SCANCODE_SPACE] == true) {
        vec3 translation_values = {0.0f, speed * 0.5, 0.0f};
        mat4 translation_matrix = mat4_translation(translation_values);
        debug_model = mat4_mult(&debug_model, &translation_matrix);
    }
    if (win->keystate[SDL_SCANCODE_W] == true) {
        vec3 translation_values = {0.0f, 0.0f, -speed * 0.5};
        mat4 translation_matrix = mat4_translation(translation_values);
        debug_model = mat4_mult(&debug_model, &translation_matrix);
    }
    if (win->keystate[SDL_SCANCODE_S] == true) {
        vec3 translation_values = {0.0f, 0.0f, speed * 0.5};
        mat4 translation_matrix = mat4_translation(translation_values);
        debug_model = mat4_mult(&debug_model, &translation_matrix);
    }
}


void loop(window* win, project* project) {
    bool running = true;
    size_t ticks_start = 0;
    size_t ticks_end = SDL_GetTicks();
    size_t ticks_counter = 0;

    while (running) {
        ticks_start = SDL_GetTicks();

        while (SDL_PollEvent(&win->event)) {
            if (win->event.type == SDL_EVENT_KEY_DOWN) {
                if (win->keystate[SDL_SCANCODE_ESCAPE] == true) {
                    running = false;
                }
            } else if (win->event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                running = false;
            }
        }

        memset(win->pixel_buffer, 0, win->w * win->h * sizeof(uint32_t));

        ticks_counter += ticks_start - ticks_end;
        if (ticks_counter >= project->tick_rate) {
            debug_controls(0.05, win);
            ticks_counter = 0;
        }
        debug_render(win);

        const char* fps[256];
        snprintf(fps, sizeof(fps), "ms: %zu", ticks_start - ticks_end);
        SDL_SetWindowTitle(win->ptr, fps);

        SDL_UpdateWindowSurface(win->ptr);
        ticks_end = ticks_start;
    }
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    window_init();
    window window;
    window.w = 1200;
    window.h = 900;
    window.title = "Black Leaf";
    window_create(&window.ptr, window.title, window.w, window.h);
    window.keystate = SDL_GetKeyboardState(NULL);
    window_init_pixel_buffer(window.ptr, &window.surface, &window.pixel_buffer, &window.format, window.w, window.h);
    project project;
    project.tick_rate = 1000 / 60;

    float fov = 40 * (PI / 180.0f);
    float aspect = (float)window.w / (float)window.h;
    float near = 0.0f;
    float far = 100.0f;

    debug_cam.view = mat4_view(debug_cam.pos, debug_cam.target, debug_cam.up);
    debug_cam.projection = mat4_perspective(fov, aspect, near, far);
    debug_model = mat4_identity();

    int result = obj_parse(debug_mesh, &dvb, &dvb_indices, &dvb_indices_count);
    if (result < 0) fprintf(stderr, "ERROR: obj_parse failed to load cube.obj.\n"); 

    loop(&window, &project);
}