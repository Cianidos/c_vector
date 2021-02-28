#pragma once
#include <stdlib.h>


/*
 *	simple vector typed ONLY for int
 */
struct int_vector
{
	size_t size;
	size_t capacity;
	int* data;

	int* (*at)(const struct int_vector* const this, const size_t index);
	int (*push_back)(struct int_vector* const this, int value);

	struct int_vector* (*copy)(const struct int_vector* const this);
};

/*
 * public declaration section
 */

struct int_vector init_int_vector(size_t size);
struct int_vector* init_int_vector_ptr(size_t size);
void delete_int_vector(struct int_vector* vect);



/*
 * tests
 */

void test_int_vector(void);


