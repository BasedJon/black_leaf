#pragma once

#include "std.h"
#include "3d_types.h"

int obj_parse(const char* filename, vertex_buffer* out_vertex_buffer, uint32_t** out_index_buffer, size_t* out_index_count);