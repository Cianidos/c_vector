#pragma once
#include <stdint.h>
#include <stdlib.h>




/*
 *  vector with abstract data structure
 */
struct void_vector
{
	/*
	 * private
	 * not for use
	 */
	size_t _element_size;

	/*
	 * private
	 * not for use
	 *
	 * size of internal buffer
	 * while size <= capacity
	 *	no data reallocation
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
	void* (*at)(const struct void_vector* const this, const size_t index);

	/*
	 *  makes new element in the end
	 *  return pointer to new element to modify
	 *
	 *  pointers invalidation possible
	 */
	void* (*push_back)(struct void_vector* const this);

	/*
	 *	if @new_size > @this->capacity
	 *		beforehand allocate memory for @new_size elements, to optimize reallocation
	 *  else do nothing
	 *
	 *  pointers invalidation possible
	 */
	void (*reserve)(struct void_vector* const this, const size_t new_capacity);

	/*
	 *	makes deep copy (new data made)
	 *
	 *  returns pointer to copy of this vector
	 */
	struct void_vector* (*copy)(const struct void_vector* const this);

	/*
	 *	returns pointer to first element 
	 */
	void* (*begin)(const struct void_vector* const this);

	/*
	 *  returns pointer to element after last
	 */
	void* (*end)(const struct void_vector* const this);

	/*
	 *  returns pointer to first element
	 */
	void* (*front)(const struct void_vector* const this);

	/*
	 *  returns pointer to first element
	 */
	void* (*back)(const struct void_vector* const this);
};

/*
 * public declaration section
 */

struct void_vector_error_t
{
	int code;

	/*
	 *  code by default = 0 - OK
	 */
} extern void_vector_error;

#define NEW_VECTOR_OF(NAME, TYPE, SIZE) struct void_vector NAME = init_void_vector((SIZE), sizeof(TYPE))
#define NEW_VECTOR_PTR_OF(NAME, TYPE, SIZE) struct void_vector* NAME = init_void_vector_ptr((SIZE), sizeof(TYPE))


struct void_vector init_void_vector(size_t size_of_vector, size_t size_of_one_element);
struct void_vector* init_void_vector_ptr(size_t size_of_vector, size_t size_of_one_element);



void delete_void_vector(struct void_vector vect);
void delete_void_vector_ptr(struct void_vector* vect);

/*
 * tests
 */

void test_void_vector(void);
