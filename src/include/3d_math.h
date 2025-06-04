#pragma once

#include "3d_types.h"

// vector operations
vec2 vec2_add(vec2 a, vec2 b);
vec3 vec3_add(vec3 a, vec3 b);
vec4 vec4_add(vec4 a, vec4 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec4 vec4_sub(vec4 a, vec4 b);
vec2 vec2_scalar(vec2 v, float scalar);
vec3 vec3_scalar(vec3 v, float scalar);
vec4 vec4_scalar(vec4 v, float scalar);
float vec2_dot(vec2 a, vec2 b);
float vec3_dot(vec3 a, vec3 b);
float vec4_dot(vec4 a, vec4 b);
float vec2_length(vec2 v);
float vec3_length(vec3 v);
vec2 vec2_center(vec2 a, vec2 b);
vec3 vec3_center(vec3 a, vec3 b, vec3 c);
vec2 vec2_normalize(vec2 v);
vec3 vec3_normalize(vec3 v);
vec3 vec3_cross(vec3 a, vec3 b);
vec2 vec2_interpolate(vec2 a, vec2 b, float f);
vec3 vec3_interpolate(vec3 a, vec3 b, float f);
vec4 vec4_interpolate(vec4 a, vec4 b, float f);
vec3 vec3_direction(vec3 from, vec3 to);
// matrix-vector multiplication
vec3 mat3_vec3_mult(const mat3* m, vec3 v);
vec3 mat4_vec3_mult(const mat4* m, vec3 v);
vec4 mat4_vec4_mult(const mat4* m, vec4 v);
// matrix operations
mat4 mat4_identity(void);
mat3 mat4_get_upper3x3(const mat4* m);
mat3 mat3_transpose(const mat3* m);
mat4 mat4_transpose(const mat4* m);
mat4 mat4_mult(const mat4* a, const mat4* b);
mat3 mat3_inverse(const mat3* m);
mat4 mat4_inverse(const mat4* m);
mat4 mat4_view(vec3 pos, vec3 target, vec3 up);
mat4 mat4_perspective(float fov, float aspect, float near, float far);
mat4 mat4_orthographic(float left, float right, float bottom, float top, float near, float far);
// camera utility
vec3 camera_right(vec3 pos, vec3 target, vec3 up);
// matrix transformations
mat4 mat4_translation(vec3 translation);
mat4 mat4_rotate_yaw(float angle_radians);
mat4 mat4_rotate_pitch(float angle_radians);
mat4 mat4_rotate_roll(float angle_radians);
// coordinate transformations
vec3 vec4_to_ndc(vec4 v);
vec3 ndc_to_viewport(const vec3 ndc, uint32_t viewport_width, uint32_t viewport_height);
// triangle utilities
bool triangle_backface_cull(vec4 a, vec4 b, vec4 c);
vec3 triangle_normal(vec3 a, vec3 b, vec3 c);
float vec4_signed_clip_plane_distance(vec4 v, uint8_t plane_index);
int triangle_clip(vec4 a, vec4 b, vec4 c, vec4** polygon_out);