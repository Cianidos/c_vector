#pragma once
#include <stdint.h>
#include <stdlib.h>

struct any_vector
{
	/*
	 * private
	 * not for use
	 */
	size_t _element_size;
	/*
	 * private
	 * not for use
	 */
	size_t _capacity;

	/*
	 *	private
	 *  not for use
	 */
	int8_t* data;

	/*
	 *  length of container, read-only
	 */
	size_t size;

	/*
	 *  returns element at @index, read-write possible
	 */
	void* (*at)(const struct any_vector* const this, const size_t index);

	/*
	 *  makes new element in the end
	 *  return pointer to new element to modify
	 *
	 *  pointers invalidation possible
	 */
	void* (*push_back)(struct any_vector* const this);

	/*
	 *	if @new_size > size
	 *		beforehand allocate memory for @new_size elements, to optimize reallocation
	 *  else do nothing
	 *
	 *  pointers invalidation possible
	 */
	void (*reserve)(struct any_vector* const this, const size_t new_size);

	/*
	 *	makes deep copy (new data made)
	 *
	 *  returns pointer to copy of this vector
	 */
	struct any_vector* (*copy)(const struct any_vector* const this);

	/*
	 *	returns pointer to first element 
	 */
	void* (*begin)(const struct any_vector* const this);

	/*
	 *  returns pointer to element after last
	 */
	void* (*end)(const struct any_vector* const this);

	/*
	 *  returns pointer to first element
	 */
	void* (*front)(const struct any_vector* const this);

	/*
	 *  returns pointer to first element
	 */
	void* (*back)(const struct any_vector* const this);
};

/*
 * public declaration section
 */

#define NEW_VECTOR_OF(TYPE, SIZE) (init_any_vector((SIZE), sizeof((TYPE))))
#define NEW_VECTOR_PTR_OF(TYPE, SIZE) (init_any_vector_ptr((SIZE), sizeof((TYPE))))

struct any_vector init_any_vector(size_t size_of_vector, size_t size_of_one_element);
struct any_vector* init_any_vector_ptr(size_t size_of_vector, size_t size_of_one_element);

void delete_any_vector(struct any_vector vect);
void delete_any_vector_ptr(struct any_vector* vect);

/*
 * tests
 */

void test_any_vector(void);
