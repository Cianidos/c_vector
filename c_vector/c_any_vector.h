#pragma once
#include <stdlib.h>

struct any_vector
{
	size_t _element_size;
	size_t size;
	size_t capacity;

	char* data;

	void* (*at)(const struct any_vector* const this, const size_t index);
	void* (*push_back)(struct any_vector* const this);
	struct any_vector* (*copy)(const struct any_vector* const this);
};

/*
 * public declaration section
 */

struct any_vector init_any_vector(size_t size_of_vector, size_t size_of_one_element);
struct any_vector* init_any_vector_ptr(size_t size_of_vector, size_t size_of_one_element);
void delete_any_vector(struct any_vector* vect);

/*
 * tests
 */

void test_any_vector(void);
