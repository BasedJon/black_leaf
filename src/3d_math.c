#include "3d_math.h"

// vec add sub scale
vec2 vec2_add(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}
vec3 vec3_add(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}
vec4 vec4_add(vec4 a, vec4 b) {
    vec4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}
vec2 vec2_sub(vec2 a, vec2 b) {
    vec2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}
vec3 vec3_sub(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}
vec4 vec4_sub(vec4 a, vec4 b) {
    vec4 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}
vec2 vec2_scalar(vec2 v, float scalar) {
    vec2 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    return result;
}
vec3 vec3_scalar(vec3 v, float scalar) {
    vec3 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}
vec4 vec4_scalar(vec4 v, float scalar) {
    vec4 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    result.w = v.w * scalar;
    return result;
}
// vec dot product
float vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}
float vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
float vec4_dot(vec4 a, vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
// vec length
float vec2_length(vec2 v) {
    return sqrtf(v.x * v.x + v.y * v.y); // TO DO: optimize sqrt maybe
}
float vec3_length(vec3 v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); // TO DO: optimize sqrt maybe
}
// vec center
vec2 vec2_center(vec2 a, vec2 b) {
    vec2 result;
    result.x = (a.x + b.x) / 2.0f;
    result.y = (a.y + b.y) / 2.0f;
    return result;
}
vec3 vec3_center(vec3 a, vec3 b, vec3 c) {
    vec3 result;
    result.x = (a.x + b.x + c.x) / 3.0f;
    result.y = (a.y + b.y + c.y) / 3.0f;
    result.z = (a.z + b.z + c.z) / 3.0f;
    return result;
}
// vec normalize
vec2 vec2_normalize(vec2 v) {
    vec2 result;
    float length = sqrtf(v.x * v.x + v.y * v.y); // TO DO: optimize sqrt maybe
    if (length < 1e-6f) {
        result.x = 0.0f;
        result.y = 0.0f;
        return result;
    }
    result.x = v.x / length;
    result.y = v.y / length;
    return result;
}
vec3 vec3_normalize(vec3 v) {
    vec3 result;
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z); // TO DO: optimize sqrt maybe
    if (length < 1e-6f) {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
        return result;
    }
    result.x = v.x / length;
    result.y = v.y / length;
    result.z = v.z / length;
    return result;
}
// vec cross
vec3 vec3_cross(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}
// vec interpolate
vec2 vec2_interpolate(vec2 a, vec2 b, float f) {
    vec2 result;
    result.x = a.x + f * (b.x - a.x);
    result.y = a.y + f * (b.y - a.y);
    return result;
}
vec3 vec3_interpolate(vec3 a, vec3 b, float f) {
    vec3 result;
    result.x = a.x + f * (b.x - a.x);
    result.y = a.y + f * (b.y - a.y);
    result.z = a.z + f * (b.z - a.z);
    return result;
}
vec4 vec4_interpolate(vec4 a, vec4 b, float f) {
    vec4 result;
    result.x = a.x + f * (b.x - a.x);
    result.y = a.y + f * (b.y - a.y);
    result.z = a.z + f * (b.z - a.z);
    result.w = a.w + f * (b.w - a.w);
    return result;
}
// vec direction
vec3 vec3_direction(vec3 from, vec3 to) {
    vec3 result;
    result.x = to.x - from.x;
    result.y = to.y - from.y;
    result.z = to.z - from.z;
    float length = sqrtf(result.x * result.x + result.y * result.y + result.z * result.z); // TO DO: optimize sqrt maybe
    if (length < 1e-6f) {
        result.x = 0.0f;
        result.y = 0.0f;
        result.z = 0.0f;
    } else {
        result.x /= length;
        result.y /= length;
        result.z /= length;
    }
    return result;
}
// mat vec multiplication
vec3 mat3_vec3_mult(const mat3* m, vec3 v) {
    vec3 result;
    result.x = m->m[0] * v.x + m->m[3] * v.y + m->m[6] * v.z;
    result.y = m->m[1] * v.x + m->m[4] * v.y + m->m[7] * v.z;
    result.z = m->m[2] * v.x + m->m[5] * v.y + m->m[8] * v.z;
    return result;
}
vec3 mat4_vec3_mult(const mat4* m, vec3 v) {
    vec3 result;
    result.x = m->m[0] * v.x + m->m[4] * v.y + m->m[8] * v.z + m->m[12];
    result.y = m->m[1] * v.x + m->m[5] * v.y + m->m[9] * v.z + m->m[13];
    result.z = m->m[2] * v.x + m->m[6] * v.y + m->m[10] * v.z + m->m[14];
    return result;
}
vec4 mat4_vec4_mult(const mat4* m, vec4 v) {
    vec4 result;
    result.x = m->m[0] * v.x + m->m[4] * v.y + m->m[8] * v.z + m->m[12] * v.w;
    result.y = m->m[1] * v.x + m->m[5] * v.y + m->m[9] * v.z + m->m[13] * v.w;
    result.z = m->m[2] * v.x + m->m[6] * v.y + m->m[10] * v.z + m->m[14] * v.w;
    result.w = m->m[3] * v.x + m->m[7] * v.y + m->m[11] * v.z + m->m[15] * v.w;
    return result;
}
// mat identity
mat4 mat4_identity() {
    mat4 result  = {0.0f};
    result.m[0]  = 1.0f;
    result.m[5]  = 1.0f;
    result.m[10] = 1.0f;
    result.m[15] = 1.0f;
    return result;
}
mat3 mat4_get_upper3x3(const mat4* m) {
    mat3 result;
    result.m[0] = m->m[0];
    result.m[1] = m->m[1];
    result.m[2] = m->m[2];
    result.m[3] = m->m[4];
    result.m[4] = m->m[5];
    result.m[5] = m->m[6];
    result.m[6] = m->m[8];
    result.m[7] = m->m[9];
    result.m[8] = m->m[10];
    return result;
}
// mat transpose
mat3 mat3_transpose(const mat3* m) {
    mat3 result;
    result.m[0] = m->m[0];
    result.m[1] = m->m[3];
    result.m[2] = m->m[6];
    result.m[3] = m->m[1];
    result.m[4] = m->m[4];
    result.m[5] = m->m[7];
    result.m[6] = m->m[2];
    result.m[7] = m->m[5];
    result.m[8] = m->m[8];
    return result;
}
mat4 mat4_transpose(const mat4* m) {
    mat4 result = { 0 };
    result.m[1]  = m->m[4];
    result.m[2]  = m->m[8];
    result.m[3]  = m->m[12];
    result.m[4]  = m->m[1];
    result.m[5]  = m->m[5];
    result.m[6]  = m->m[9];
    result.m[7]  = m->m[13];
    result.m[8]  = m->m[2];
    result.m[9]  = m->m[6];
    result.m[10] = m->m[10];
    result.m[11] = m->m[14];
    result.m[12] = m->m[3];
    result.m[13] = m->m[7];
    result.m[14] = m->m[11];
    result.m[15] = m->m[15];
    result.m[0]  = m->m[0];
    return result;
}
// mat multiplication
mat4 mat4_mult(const mat4* a, const mat4* b) { // TO DO: cache the matrix 
    mat4 result;
    result.m[0] = a->m[0] * b->m[0] + a->m[1] * b->m[4] + a->m[2] * b->m[8] + a->m[3] * b->m[12];
    result.m[1] = a->m[0] * b->m[1] + a->m[1] * b->m[5] + a->m[2] * b->m[9] + a->m[3] * b->m[13];
    result.m[2] = a->m[0] * b->m[2] + a->m[1] * b->m[6] + a->m[2] * b->m[10] + a->m[3] * b->m[14];
    result.m[3] = a->m[0] * b->m[3] + a->m[1] * b->m[7] + a->m[2] * b->m[11] + a->m[3] * b->m[15];
    result.m[4] = a->m[4] * b->m[0] + a->m[5] * b->m[4] + a->m[6] * b->m[8] + a->m[7] * b->m[12];
    result.m[5] = a->m[4] * b->m[1] + a->m[5] * b->m[5] + a->m[6] * b->m[9] + a->m[7] * b->m[13];
    result.m[6] = a->m[4] * b->m[2] + a->m[5] * b->m[6] + a->m[6] * b->m[10] + a->m[7] * b->m[14];
    result.m[7] = a->m[4] * b->m[3] + a->m[5] * b->m[7] + a->m[6] * b->m[11] + a->m[7] * b->m[15];
    result.m[8] = a->m[8] * b->m[0] + a->m[9] * b->m[4] + a->m[10] * b->m[8] + a->m[11] * b->m[12];
    result.m[9] = a->m[8] * b->m[1] + a->m[9] * b->m[5] + a->m[10] * b->m[9] + a->m[11] * b->m[13];
    result.m[10] = a->m[8] * b->m[2] + a->m[9] * b->m[6] + a->m[10] * b->m[10] + a->m[11] * b->m[14];
    result.m[11] = a->m[8] * b->m[3] + a->m[9] * b->m[7] + a->m[10] * b->m[11] + a->m[11] * b->m[15];
    result.m[12] = a->m[12] * b->m[0] + a->m[13] * b->m[4] + a->m[14] * b->m[8] + a->m[15] * b->m[12];
    result.m[13] = a->m[12] * b->m[1] + a->m[13] * b->m[5] + a->m[14] * b->m[9] + a->m[15] * b->m[13];
    result.m[14] = a->m[12] * b->m[2] + a->m[13] * b->m[6] + a->m[14] * b->m[10] + a->m[15] * b->m[14];
    result.m[15] = a->m[12] * b->m[3] + a->m[13] * b->m[7] + a->m[14] * b->m[11] + a->m[15] * b->m[15];
    return result;
}
// mat inverse
mat3 mat3_inverse(const mat3* m) { // TO DO: is this effeicent?
    mat3 result;
    float m0 = m->m[0];
    float m3 = m->m[3];
    float m6 = m->m[6];
    float m1 = m->m[1];
    float m4 = m->m[4];
    float m7 = m->m[7];
    float m2 = m->m[2];
    float m5 = m->m[5];
    float m8 = m->m[8];
    float c0 = m4 * m8 - m5 * m7;
    float c1 = m3 * m8 - m5 * m6;
    float c2 = m3 * m7 - m4 * m6;
    float c3 = m1 * m8 - m2 * m7;
    float c4 = m0 * m8 - m2 * m6;
    float c5 = m0 * m7 - m1 * m6;
    float c6 = m1 * m5 - m2 * m4;
    float c7 = m0 * m5 - m2 * m3;
    float c8 = m0 * m4 - m1 * m3;
    float inverse_determinant = 1.0f / (m0 * c0 - m1 * c1 + m2 * c2);
    result.m[0] =  c0 * inverse_determinant;
    result.m[1] = -c3 * inverse_determinant;
    result.m[2] =  c6 * inverse_determinant;
    result.m[3] = -c1 * inverse_determinant;
    result.m[4] =  c4 * inverse_determinant;
    result.m[5] = -c7 * inverse_determinant;
    result.m[6] =  c2 * inverse_determinant;
    result.m[7] = -c5 * inverse_determinant;
    result.m[8] =  c8 * inverse_determinant;
    return result;
}
mat4 mat4_inverse(const mat4* m) { // TO DO: is this effeicent?
    mat4 result;
    float m0 = m->m[0];
    float m4 = m->m[4];
    float m8 = m->m[8];
    float m12 = m->m[12];
    float m1 = m->m[1];
    float m5 = m->m[5];
    float m9 = m->m[9];
    float m13 = m->m[13];
    float m2 = m->m[2];
    float m6 = m->m[6];
    float m10 = m->m[10];
    float m14 = m->m[14];
    float m3 = m->m[3];
    float m7 = m->m[7];
    float m11 = m->m[11];
    float m15 = m->m[15];
    float c0 = m0 * m5 - m1 * m4;
    float c1 = m0 * m6 - m2 * m4;
    float c2 = m0 * m7 - m3 * m4;
    float c3 = m1 * m6 - m2 * m5;
    float c4 = m1 * m7 - m3 * m5;
    float c5 = m2 * m7 - m3 * m6;
    float c6 = m8 * m13 - m9 * m12;
    float c7 = m8 * m14 - m10 * m12;
    float c8 = m8 * m15 - m11 * m12;
    float c9 = m9 * m14 - m10 * m13;
    float c10 = m9 * m15 - m11 * m13;
    float c11 = m10 * m15 - m11 * m14;
    float inverse_determinant = 1.0f / (c0 * c11 - c1 * c10 + c2 * c9 + c3 * c8 - c4 * c7 + c5 * c6);
    result.m[0] = (m5 * c11 - m6 * c10 + m7 * c9) * inverse_determinant;
    result.m[1] = -(m1 * c11 - m2 * c10 + m3 * c9) * inverse_determinant;
    result.m[2] = (m13 * c5 - m14 * c4 + m15 * c3) * inverse_determinant;
    result.m[3] = -(m9 * c5 - m10 * c4 + m11 * c3) * inverse_determinant;
    result.m[4] = -(m4 * c11 - m6 * c8 + m7 * c7) * inverse_determinant;
    result.m[5] = (m0 * c11 - m2 * c8 + m3 * c7) * inverse_determinant;
    result.m[6] = -(m12 * c5 - m14 * c2 + m15 * c1) * inverse_determinant;
    result.m[7] = (m8 * c5 - m10 * c2 + m11 * c1) * inverse_determinant;
    result.m[8] = (m4 * c10 - m5 * c8 + m7 * c6) * inverse_determinant;
    result.m[9] = -(m0 * c10 - m1 * c8 + m3 * c6) * inverse_determinant;
    result.m[10] = (m12 * c4 - m13 * c2 + m15 * c0) * inverse_determinant;
    result.m[11] = -(m8 * c4 - m9 * c2 + m11 * c0) * inverse_determinant;
    result.m[12] = -(m4 * c9 - m5 * c7 + m6 * c6) * inverse_determinant;
    result.m[13] = (m0 * c9 - m1 * c7 + m2 * c6) * inverse_determinant;
    result.m[14] = -(m12 * c3 - m13 * c1 + m14 * c0) * inverse_determinant;
    result.m[15] = (m8 * c3 - m9 * c1 + m10 * c0) * inverse_determinant;
    return result;
}
// mat view, perspective projection, orthographic matrices
mat4 mat4_view(vec3 pos, vec3 target, vec3 up) {
    vec3 f = vec3_normalize(vec3_sub(target, pos));
    vec3 r = vec3_normalize(vec3_cross(up, f));
    vec3 u = vec3_cross(f, r);
    mat4 result;
    result.m[0]  = r.x;
    result.m[4]  = r.y;
    result.m[8]  = r.z;
    result.m[12] = -vec3_dot(r, pos);
    result.m[1]  = u.x;
    result.m[5]  = u.y;
    result.m[9]  = u.z;
    result.m[13] = -vec3_dot(u, pos);
    result.m[2]  = f.x;
    result.m[6]  = f.y;
    result.m[10] = f.z;
    result.m[14] = -vec3_dot(f, pos);
    result.m[3]  = 0.0f;
    result.m[7]  = 0.0f;
    result.m[11] = 0.0f;
    result.m[15] = 1.0f;
    return result;
}
mat4 mat4_perspective(float fov, float aspect, float near, float far) { // TO DO: is tan fast enough?
    mat4 result = {0.0f};
    float tangent_half_fov = tan(fov / 2.0f);
    result.m[0]  = 1.0f / (aspect * tangent_half_fov);
    result.m[5]  = 1.0f / tangent_half_fov;
    result.m[10] = far / (far - near);
    result.m[11] = 1.0f;
    result.m[14] = -(far * near) / (far - near);
    return result;
}
mat4 mat4_orthographic(float left, float right, float bottom, float top, float near, float far) {
    mat4 result = {0.0f};
    result.m[0] = 2.0f / (right - left);
    result.m[5] = 2.0f / (top - bottom);
    result.m[10] = 1.0f / (far - near);
    result.m[12] = -(right + left) / (right - left);
    result.m[13] = -(top + bottom) / (bottom - top);
    result.m[14] = -near / (far - near);
    result.m[15] = 1.0f;
    return result;
}
// camera right update
vec3 camera_right(vec3 pos, vec3 target, vec3 up) {
    vec3 forward = vec3_direction(pos, target);
    vec3 right = vec3_normalize(vec3_cross(forward, up));
    return right;
}
// translation, rotation
mat4 mat4_translation(vec3 translation) {
    mat4 result = mat4_identity();
    result.m[12] = translation.x;
    result.m[13] = translation.y;
    result.m[14] = translation.z;
    return result;
}
mat4 mat4_rotate_yaw(float angle_radians) { // TO DO: is cos/sin fast enough?
    mat4 result = mat4_identity();
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    result.m[0] = cos_angle;
    result.m[2] = sin_angle;
    result.m[8] = -sin_angle;
    result.m[10] = cos_angle;
    return result;
}
mat4 mat4_rotate_pitch(float angle_radians) { // TO DO: is cos/sin fast enough?
    mat4 result = mat4_identity();
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    result.m[5] = cos_angle;
    result.m[6] = sin_angle;
    result.m[9] = -sin_angle;
    result.m[10] = cos_angle;
    return result;
}
mat4 mat4_rotate_roll(float angle_radians) {
    mat4 result = mat4_identity();
    float cos_angle = cosf(angle_radians);
    float sin_angle = sinf(angle_radians);
    result.m[0] = cos_angle;
    result.m[1] = sin_angle;
    result.m[4] = -sin_angle;
    result.m[5] = cos_angle;
    return result;
}
// vec4 to ndc
vec3 vec4_to_ndc(vec4 v) { // probs not in math lib
    vec3 result;
    result.x = v.x / v.w;
    result.y = v.y / v.w;
    result.z = v.z / v.w;
    return result;
}
// ndc to viewport
vec3 ndc_to_viewport(const vec3 ndc, uint32_t viewport_width, uint32_t viewport_height) { // probs not in math lib
    vec3 result;
    result.x = (ndc.x + 1.0f) * 0.5f * viewport_width;
    result.y = (1.0f - ndc.y) * 0.5f * viewport_height;
    result.z = ndc.z;
    return result;
}
// triangle backface culling (using winding order)
bool triangle_backface_cull(vec4 a, vec4 b, vec4 c) { // probs not in math lib
    a.x = a.x / a.w;
    a.y = a.y / a.w;
    a.z = a.z / a.w;
    b.x = b.x / b.w;
    b.y = b.y / b.w;
    b.z = b.z / b.w;
    c.x = c.x / c.w;
    c.y = c.y / c.w;
    c.z = c.z / c.w;
    return ((b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)) > 0.0f;
}
// triangle normal
vec3 triangle_normal (vec3 a, vec3 b, vec3 c) { // probs not in math lib
    vec3 ba = vec3_sub(b, a);
    vec3 ca = vec3_sub(c, a);
    vec3 result = vec3_normalize(vec3_cross(ba, ca));
    return result;
}
// find singed distance for clipping
float vec4_signed_clip_plane_distance(vec4 v, uint8_t plane_index) { // probs not in math lib
    switch (plane_index) {
    case 0: return v.x + v.w;  // x >= -w
    case 1: return v.w - v.x;  // x <= w
    case 2: return v.y + v.w;  // y >= -w
    case 3: return v.w - v.y;  // y <= w
    case 4: return v.z + v.w;  // z >= -w
    case 5: return v.w - v.z;  // z <= w
    default: return 0.0f;
    }
}