#include "std.h"
#include "3d_types.h"

void obj_parsed(const char* filename, vertex_buffer* out_vertex_buffer, uint32_t** out_index_buffer, size_t* out_index_count) {
    FILE* obj = fopen(filename, "r");
    if (!obj) {
        fprintf(stderr, "ERROR: obj_parse failed to open file: %s\n", filename);
        return;
    }

    vec4* positions = NULL; size_t position_count = 0, position_capacity = 0;
    vec3* normals = NULL; size_t normal_count = 0, normal_capacity = 0;
    vec2* uvs = NULL; size_t uv_count = 0, uv_capacity = 0;

    uint32_t* unique_position_indices = NULL;
    uint32_t* unique_normal_indices = NULL;
    uint32_t* unique_uv_indices = NULL;
    size_t unique_count = 0, unique_capacity = 0;

    uint32_t* indices = NULL;
    size_t indices_count = 0, indices_capacity = 0;

    char line[256];
    vec4 position = {0}; vec3 normal = {0}; vec2 uv = {0};
    uint32_t position_indices[3], normal_indices[3], uv_indices[3];
    uint32_t index = 0;
    bool vertex_unique;

    while (fgets(line, sizeof(line), obj)) {
        if (line[0] == 'v' && line[1] == ' ') {
            if (position_count >= position_capacity) {
                size_t new_capacity = position_capacity ? position_capacity * 2 : 64;
                vec4* temp = realloc(positions, new_capacity * sizeof(vec4));
                if (!temp) { fprintf(stderr, "ERROR: realloc failed for positions\n"); exit(1); }
                positions = temp;
                position_capacity = new_capacity;
            }
            sscanf(line, "v %f %f %f", &position.x, &position.y, &position.z);
            position.w = 1.0f;
            positions[position_count++] = position;
        }
        else if (line[0] == 'v' && line[1] == 'n') {
            if (normal_count >= normal_capacity) {
                size_t new_capacity = normal_capacity ? normal_capacity * 2 : 64;
                vec3* temp = realloc(normals, new_capacity * sizeof(vec3));
                if (!temp) { fprintf(stderr, "ERROR: realloc failed for normals\n"); exit(1); }
                normals = temp;
                normal_capacity = new_capacity;
            }
            sscanf(line, "vn %f %f %f", &normal.x, &normal.y, &normal.z);
            normals[normal_count++] = normal;
        }
        else if (line[0] == 'v' && line[1] == 't') {
            if (uv_count >= uv_capacity) {
                size_t new_capacity = uv_capacity ? uv_capacity * 2 : 64;
                vec2* temp = realloc(uvs, new_capacity * sizeof(vec2));
                if (!temp) { fprintf(stderr, "ERROR: realloc failed for uvs\n"); exit(1); }
                uvs = temp;
                uv_capacity = new_capacity;
            }
            sscanf(line, "vt %f %f", &uv.x, &uv.y);
            uvs[uv_count++] = uv;
        }
        else if (line[0] == 'f' && line[1] == ' ') {
            if (sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
                       &position_indices[0], &normal_indices[0], &uv_indices[0],
                       &position_indices[1], &normal_indices[1], &uv_indices[1],
                       &position_indices[2], &normal_indices[2], &uv_indices[2]) != 9) {
                fprintf(stderr, "ERROR: Unsupported face format: %s", line);
                fclose(obj);
                return;
            }

            for (size_t vertex_i = 0; vertex_i < 3; vertex_i++) {
                vertex_unique = true;
                for (size_t unique_i = 0; unique_i < unique_count; unique_i++) {
                    if (unique_position_indices[unique_i] == position_indices[vertex_i] - 1 &&
                        unique_normal_indices[unique_i] == normal_indices[vertex_i] - 1 &&
                        unique_uv_indices[unique_i] == uv_indices[vertex_i] - 1) {
                        vertex_unique = false;
                        index = unique_i;
                        break;
                    }
                }

                if (vertex_unique) {
                    if (unique_count >= unique_capacity) {
                        size_t new_capacity = unique_capacity ? unique_capacity * 2 : 64;

                        uint32_t* temp_pos = realloc(unique_position_indices, new_capacity * sizeof(uint32_t));
                        uint32_t* temp_norm = realloc(unique_normal_indices, new_capacity * sizeof(uint32_t));
                        uint32_t* temp_uv = realloc(unique_uv_indices, new_capacity * sizeof(uint32_t));
                        if (!temp_pos || !temp_norm || !temp_uv) {
                            fprintf(stderr, "ERROR: realloc failed for unique indices\n");
                            exit(1);
                        }

                        unique_position_indices = temp_pos;
                        unique_normal_indices = temp_norm;
                        unique_uv_indices = temp_uv;
                        unique_capacity = new_capacity;
                    }

                    unique_position_indices[unique_count] = position_indices[vertex_i] - 1;
                    unique_normal_indices[unique_count] = normal_indices[vertex_i] - 1;
                    unique_uv_indices[unique_count] = uv_indices[vertex_i] - 1;
                    index = unique_count++;
                }

                if (indices_count >= indices_capacity) {
                    size_t new_capacity = indices_capacity ? indices_capacity * 2 : 64;
                    uint32_t* temp = realloc(indices, new_capacity * sizeof(uint32_t));
                    if (!temp) { fprintf(stderr, "ERROR: realloc failed for indices\n"); exit(1); }
                    indices = temp;
                    indices_capacity = new_capacity;
                }

                // SAFETY CHECK
                if (indices_count < indices_capacity) {
                    indices[indices_count++] = index;
                } else {
                    fprintf(stderr, "ERROR: index write out of bounds (indices_count = %zu, capacity = %zu)\n", indices_count, indices_capacity);
                    exit(1);
                }
            }
        }
    }
    fclose(obj);

    size_t stride = sizeof(float) * (4 + 3 + 2);
    void* vertex_data = malloc(unique_count * stride);
    if (!vertex_data) { fprintf(stderr, "ERROR: malloc failed for vertex_data\n"); exit(1); }

    for (size_t i = 0; i < unique_count; i++) {
        uint8_t* destination = (uint8_t*)vertex_data + i * stride;
        memcpy(destination + 0 * sizeof(float), &positions[unique_position_indices[i]], sizeof(vec4));
        memcpy(destination + 4 * sizeof(float), &normals[unique_normal_indices[i]], sizeof(vec3));
        memcpy(destination + 7 * sizeof(float), &uvs[unique_uv_indices[i]], sizeof(vec2));
    }

    vertex_attributes_description* attributes = malloc(3 * sizeof(vertex_attributes_description));
    if (!attributes) { fprintf(stderr, "ERROR: malloc failed for attributes\n"); exit(1); }

    attributes[0] = (vertex_attributes_description){ ATTRIBUTE_POSITION, 4, 0, 0 };
    attributes[1] = (vertex_attributes_description){ ATTRIBUTE_NORMAL, 3, 4 * sizeof(float), 0 };
    attributes[2] = (vertex_attributes_description){ ATTRIBUTE_UV, 2, 7 * sizeof(float), 0 };

    out_vertex_buffer->data = vertex_data;
    out_vertex_buffer->stride = stride;
    out_vertex_buffer->count = unique_count;
    out_vertex_buffer->attributes = attributes;
    out_vertex_buffer->attribute_count = 3;

    *out_index_count = indices_count;
    *out_index_buffer = indices;

    free(positions);
    free(normals);
    free(uvs);
    free(unique_position_indices);
    free(unique_normal_indices);
    free(unique_uv_indices);
}