#include "STD.h"

void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int clamp_int(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
size_t clamp_sizet(size_t value, size_t min, size_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void swap(void* a, void* b, size_t size) {
    void* temp = malloc(size);
    if (!temp) return; // TO DO: error handle
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}
