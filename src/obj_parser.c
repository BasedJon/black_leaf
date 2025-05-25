#include "obj_parser.h"

int obj_parse(const char* filename, vertex_buffer* out_vertex_buffer, uint32_t** out_index_buffer, size_t* out_index_count) {
    FILE* obj = fopen(filename, "r");
    if (!obj) { fprintf(stderr, "ERROR: obj_parse failed to open file: %s\n", filename); return -1; }
    
    vec4* positions = NULL; size_t positions_count = 0;
    vec3* normals = NULL; size_t normals_count = 0;
    vec2* uvs = NULL; size_t uvs_count = 0;
    uint32_t* indices = NULL; size_t indices_count = 0;
    uint32_t* vertex_buffer_indices = NULL;
    uint32_t* vertex_buffer_template = NULL;


    char line[256];
    while (fgets(line, sizeof(line), obj)) {
        if (line[0] == 'v' && line[1] == ' ') positions_count++;
        else if (line[0] == 'v' && line[1] == 'n') normals_count++;
        else if (line[0] == 'v' && line[1] == 't') uvs_count++;
        else if (line[0] == 'f' && line[1] == ' ') indices_count++;
    }

    positions = (vec4*)malloc(positions_count * sizeof(vec4));
    if (!positions) { fclose(obj); fprintf(stderr, "ERROR: obj_parse failed at malloc positions.\n"); return -1; }
    normals = (vec3*)malloc(normals_count * sizeof(vec3));
    if (!normals) { fclose(obj); fprintf(stderr, "ERROR: obj_parse failed at malloc normals.\n"); return -1; }
    uvs = (vec2*)malloc(uvs_count * sizeof(vec2));
    if (!uvs) { fclose(obj); fprintf(stderr, "ERROR: obj_parse failed at malloc uvs.\n"); return -1; }
    indices = (uint32_t*)malloc(indices_count * 9 * sizeof(uint32_t));
    if (!indices) { fclose(obj); fprintf(stderr, "ERROR: obj_parse failed at malloc indices.\n"); return -1; }
    vertex_buffer_indices = (uint32_t*)malloc(indices_count * 3 * sizeof(uint32_t));
    if (!vertex_buffer_indices) { fclose(obj); fprintf(stderr, "ERROR: obj_parse failed at malloc vertex_buffer_indices.\n"); return -1; }
    vertex_buffer_template = (uint32_t*)malloc(indices_count * 9 * sizeof(uint32_t));
    if (!vertex_buffer_template) { fclose(obj); fprintf(stderr, "ERROR: obj_parse failed at malloc vertex_buffer_template.\n"); return -1; }
    rewind(obj);

    size_t positions_index = 0, normals_index = 0, uvs_index = 0, indices_index = 0;
    while (fgets(line, sizeof(line), obj)) {
    if (line[0] == 'v' && line[1] == ' ') {
        sscanf(line, "v %f %f %f", &positions[positions_index].x, &positions[positions_index].y, &positions[positions_index].z);
        positions[positions_index].w = 1.0f;
        positions_index++;
    }
    else if (line[0] == 'v' && line[1] == 'n') {
        sscanf(line, "vn %f %f %f", &normals[normals_index].x, &normals[normals_index].y, &normals[normals_index].z);
        normals_index++;
    }
    else if (line[0] == 'v' && line[1] == 't') {
        sscanf(line, "vt %f %f", &uvs[uvs_index].x, &uvs[uvs_index].y);
        uvs_index++;
    }
    else if (line[0] == 'f' && line[1] == ' ') { 
         sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u",
                &indices[indices_index], &indices[indices_index + 1], &indices[indices_index + 2],
                &indices[indices_index + 3], &indices[indices_index + 4], &indices[indices_index + 5],
                &indices[indices_index + 6], &indices[indices_index + 7], &indices[indices_index + 8]);
        indices[indices_index]--;
        indices[indices_index + 1]--;
        indices[indices_index + 2]--;
        indices[indices_index + 3]--;
        indices[indices_index + 4]--;
        indices[indices_index + 5]--;
        indices[indices_index + 6]--;
        indices[indices_index + 7]--;
        indices[indices_index + 8]--;
        indices_index += 9;
    }
    }

    bool unique; size_t unique_count = 0;
    for (size_t i = 0; i < indices_count * 9; i += 3) {
        unique = true;
            for (size_t j = 0; j < unique_count * 3; j += 3) {
                if (indices[i] == vertex_buffer_template[j] &&
                    indices[i + 1] == vertex_buffer_template[j + 1] &&
                    indices[i + 2] == vertex_buffer_template[j + 2]) {
                    vertex_buffer_indices[i / 3] = j / 3;
                    unique = false;
                    break;
                }
            }
        if (unique) {
            vertex_buffer_template[unique_count * 3] = indices[i];
            vertex_buffer_template[unique_count * 3 + 1] = indices[i + 1];
            vertex_buffer_template[unique_count * 3 + 2] = indices[i + 2];
            vertex_buffer_indices[i / 3] = unique_count;
            unique_count++;
        }
    }

    size_t stride = sizeof(float) * (4 + 3 + 2);
    void* vertex_data = malloc(unique_count * stride);
    if (!vertex_data) { 
        free(positions);
        free(normals);
        free(uvs);
        free(indices);
        free(vertex_buffer_indices);
        free(vertex_buffer_template);
        fclose(obj); 
        fprintf(stderr, "ERROR: obj_parse failed at malloc vertex_data.\n"); 
        return -1; 
    }
    vertex_attributes_description* attributes = malloc(3 * sizeof(vertex_attributes_description));
    if (!attributes) { 
        free(positions);
        free(normals);
        free(uvs);
        free(indices);
        free(vertex_buffer_indices);
        free(vertex_buffer_template);
        free(vertex_data);
        fclose(obj); 
        fprintf(stderr, "ERROR: obj_parse failed at malloc attributes.\n"); 
        return -1; 
    }

    for (size_t i = 0; i < unique_count; i++) {
        uint8_t* mem_ptr = (uint8_t*)vertex_data + i * stride;
        memcpy(mem_ptr + 0 * sizeof(float), &positions[vertex_buffer_template[i * 3]], sizeof(vec4));
        memcpy(mem_ptr + 4 * sizeof(float), &normals[vertex_buffer_template[i * 3 + 2]], sizeof(vec3));
        memcpy(mem_ptr + 7 * sizeof(float), &uvs[vertex_buffer_template[i * 3 + 1]], sizeof(vec2));
    }
    attributes[0] = (vertex_attributes_description){ ATTRIBUTE_POSITION, 4, 0, 0 };
    attributes[1] = (vertex_attributes_description){ ATTRIBUTE_NORMAL, 3, 4 * sizeof(float), 0 };
    attributes[2] = (vertex_attributes_description){ ATTRIBUTE_UV, 2, 7 * sizeof(float), 0 };

    out_vertex_buffer->data = vertex_data;
    out_vertex_buffer->stride = stride;
    out_vertex_buffer->count = unique_count;
    out_vertex_buffer->attributes = attributes;
    out_vertex_buffer->attribute_count = 3;

    *out_index_count = indices_count * 3;
    *out_index_buffer = vertex_buffer_indices;

    fclose(obj); 
    free(positions);
    free(normals);
    free(uvs);
    free(indices);
    free(vertex_buffer_template);
    return 1;
}

