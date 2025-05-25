#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define PI 3.14159265358979323846

void swap_int(int* a, int* b);
int clamp_int(int value, int min, int max);
size_t clamp_sizet(size_t value, size_t min, size_t max);
void swap(void* a, void* b, size_t size);