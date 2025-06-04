#include "window.h"
#include "std.h"
#include "obj_parser.h"
#include "rasterizer.h"
#include "3d_types.h"
#include "3d_math.h"
#include "graphics_pipeline.h"
#include "project.h"

float* z_buffer;
vertex_buffer dvb;
uint32_t* dvb_indices = NULL;
uint32_t dvb_indices_count;
mat4 debug_model;
const char* debug_mesh = "obj_data/cube.obj";
bool debug_bool = true;

camera debug_cam = {
{ 0.0f, 0.0f, 10.0f },
{ 0.0f, 0.0f, -1.0f },
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

        if (debug_bool) {
        if (triangle_backface_cull(va, vb, vc)) continue; 
        }

        vec4* polygon_out;
        int clipped_count = triangle_clip(va, vb, vc, &polygon_out);

       if (clipped_count > 0 && polygon_out) {
        for (int i = 1; i < clipped_count - 1; i++) {
            vec4 v0 = polygon_out[0];
            vec4 v1 = polygon_out[i];
            vec4 v2 = polygon_out[i + 1];

            vec3 v0_vp = ndc_to_viewport(vec4_to_ndc(v0), win->w, win->h);
            vec3 v1_vp = ndc_to_viewport(vec4_to_ndc(v1), win->w, win->h);
            vec3 v2_vp = ndc_to_viewport(vec4_to_ndc(v2), win->w, win->h);

            
            draw_triangle(v0_vp, v1_vp, v2_vp, win, &win->pixel_buffer, z_buffer, win->w, win->h);
            draw_line(v0_vp.x, v0_vp.y, v1_vp.x, v1_vp.y, &win->pixel_buffer, line_color, win->w, win->h);
            draw_line(v1_vp.x, v1_vp.y, v2_vp.x, v2_vp.y, &win->pixel_buffer, line_color, win->w, win->h);
            draw_line(v2_vp.x, v2_vp.y, v0_vp.x, v0_vp.y, &win->pixel_buffer, line_color, win->w, win->h);
        }
        free(polygon_out);
        }
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

    if (win->keystate[SDL_SCANCODE_W]) {
        vec3 forward = vec3_normalize(debug_cam.target);
        debug_cam.pos = vec3_add(debug_cam.pos, vec3_scalar(forward, speed));
    }
    if (win->keystate[SDL_SCANCODE_S]) {
        vec3 backward = vec3_normalize(debug_cam.target);
        debug_cam.pos = vec3_add(debug_cam.pos, vec3_scalar(backward, -speed));
    }
    if (win->keystate[SDL_SCANCODE_D]) {
        vec3 right = vec3_normalize(debug_cam.right);
        debug_cam.pos = vec3_add(debug_cam.pos, vec3_scalar(right, speed));
    }
    if (win->keystate[SDL_SCANCODE_A]) {
        vec3 left = vec3_normalize(debug_cam.right);
        debug_cam.pos = vec3_add(debug_cam.pos, vec3_scalar(left, -speed));
    }
    if (win->keystate[SDL_SCANCODE_SPACE]) {
        vec3 up = vec3_normalize(debug_cam.up);
        debug_cam.pos = vec3_add(debug_cam.pos, vec3_scalar(up, speed));
    }
    if (win->keystate[SDL_SCANCODE_LSHIFT]) {
        vec3 down = vec3_normalize(debug_cam.up);
        debug_cam.pos = vec3_add(debug_cam.pos, vec3_scalar(down, -speed));
    }

    vec3 forward = vec3_normalize(debug_cam.target);
    vec3 world_up = {0.0f, 1.0f, 0.0f};
    debug_cam.right = vec3_normalize(vec3_cross(forward, world_up));
    debug_cam.up = vec3_cross(debug_cam.right, forward);
    vec3 center = vec3_add(debug_cam.pos, forward);
    debug_cam.view = mat4_view(debug_cam.pos, center, debug_cam.up);
}


void loop(window* win, project* project) {
    bool running = true;
    size_t ticks_start = 0;
    size_t ticks_end = SDL_GetTicks();
    size_t ticks_counter = 0;

    float control_debug_speed = 0.05;

    while (running) {
        ticks_start = SDL_GetTicks();

        while (SDL_PollEvent(&win->event)) {
            if (win->event.type == SDL_EVENT_KEY_DOWN) {
                if (win->keystate[SDL_SCANCODE_ESCAPE] == true) { running = false; }
                if (win->keystate[SDL_SCANCODE_ESCAPE] == true) running = false;
                if (win->keystate[SDL_SCANCODE_1] == true) control_debug_speed = 0.05;
                if (win->keystate[SDL_SCANCODE_2] == true) control_debug_speed += 10;
                if (win->keystate[SDL_SCANCODE_3] == true) debug_bool = !debug_bool;
            } else if (win->event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                running = false;
            }
            
        }

        memset(win->pixel_buffer, 0, win->w * win->h * sizeof(uint32_t));
        memset(z_buffer, 0, win->w * win->h * sizeof(float));

        ticks_counter += ticks_start - ticks_end;
        if (ticks_counter >= project->tick_rate) {
            debug_controls(control_debug_speed, win);
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
    float near = 0.1f;
    float far = 10.0f;

    debug_cam.view = mat4_view(debug_cam.pos, debug_cam.target, debug_cam.up);
    debug_cam.projection = mat4_perspective(fov, aspect, near, far);
    debug_model = mat4_identity();

    int result = obj_parse(debug_mesh, &dvb, &dvb_indices, &dvb_indices_count);
    if (result < 0) fprintf(stderr, "ERROR: obj_parse failed to load cube.obj.\n"); 

    z_buffer = (float*)malloc(window.h * window.w * sizeof(float));
    loop(&window, &project);
}