#pragma once
#include <stdio.h>

#include "c_void_vector.h"

struct void_vector* where(const struct void_vector* const vector, int(*predicate)(void*));

struct void_vector* map(const struct void_vector* const vector, void* (*producer)(void*), size_t size_of_produced_type);

void* reduce(const struct void_vector* const vector, void* (*reducer)(void*, void*), void* init_value);


void test_functional(void);


