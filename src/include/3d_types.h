#pragma once

#include "std.h"

// PRIMITIVES
typedef union {
    struct { float x; };
    float i[1];
} vec1;
typedef union {
    struct { float x, y; };
    float i[2];
} vec2;
typedef union {
    struct { float x, y, z; };
    struct { vec2 xy; };
    float i[3];
} vec3;
typedef union {
    struct { float x, y, z, w; };
    struct { vec2 xy; };
    struct { vec3 xyz; };
    float i[4];
} vec4;
typedef struct {
    float m[9];
} mat3;
typedef struct {
    float m[12];
} mat3x4; // TO DO: add math funcs for this mat
typedef struct {
    float m[16];
} mat4;

// STRUCTURES
typedef enum vertex_attribute_type {
    ATTRIBUTE_POSITION = 0,
    ATTRIBUTE_NORMAL   = 1,
    ATTRIBUTE_UV       = 2,
    ATTRIBUTE_COLOR    = 3,
    ATTRIBUTE_TANGENT  = 4,
} vertex_attribute_type;
typedef struct {
    uint32_t type;
    uint32_t dimension;
    size_t offset;
    uint32_t binding;
} vertex_attributes_description;
typedef struct {
    void* data;
    size_t stride;
    uint32_t* attribute_dimensions;
    size_t count;
    vertex_attributes_description* attributes;
    size_t attribute_count;
} vertex_buffer;
typedef struct {
    vec3 pos;
    vec3 target;
    vec3 up;
    vec3 right;
    mat4 view;
    mat4 projection;
} camera;