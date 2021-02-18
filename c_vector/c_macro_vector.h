#pragma once

#include <stdlib.h>

/*
 *	macros that define vector typed for @TYPE
 *	with name "vector_@TYPE"
 */
#define DEFINE_VECTOR_OF(TYPE) \
\
\
typedef struct vector##_##TYPE\
{\
	size_t size;\
	size_t capacity;\
	TYPE* data;\
\
	TYPE* (*at)(const struct vector##_##TYPE* const this, const size_t index);\
	int (*push_back)(struct vector##_##TYPE* const this, TYPE value);\
\
	struct vector##_##TYPE* (*copy)(const struct vector##_##TYPE* const this);\
};\
\
/*\
 * public declaration section\
 */\
\
struct vector##_##TYPE init_vector##_##TYPE(size_t size);\
struct vector##_##TYPE* init_vector_##TYPE##_ptr(size_t size);\
void delete_vector##_##TYPE(struct vector##_##TYPE* vect);\
\
\
/*\
 * private declaration section\
 */\
\
int* data_alloc_vector##_##TYPE\
(size_t size);\
\
void data_copy_vector##_##TYPE\
(const struct vector##_##TYPE* const from, struct vector##_##TYPE* to);\
\
void data_double_capacity##_##TYPE\
(struct vector##_##TYPE* const this);\
\
\
TYPE* at_vector##_##TYPE\
(const struct vector##_##TYPE* const this, const size_t index);\
\
int push_back_vector##_##TYPE\
(struct vector##_##TYPE* const this, TYPE value);\
\
\
struct vector##_##TYPE* copy_vector##_##TYPE\
(const struct vector##_##TYPE* const this);\
\
/*\
 *private definition section\
 */\
\
void data_double_capacity##_##TYPE\
(struct vector##_##TYPE* const this)\
{\
	if (this->capacity == 0)\
		this->capacity = 1;\
\
	this->capacity *= 2;\
	struct vector##_##TYPE* tmp = init_vector##_##TYPE##_ptr(this->capacity);\
	data_copy_vector##_##TYPE(this, tmp);\
	free(this->data);\
	this->data = tmp->data;\
	free(tmp);\
}\
\
int* data_alloc_vector##_##TYPE\
(size_t size)\
{\
	return (TYPE*) malloc(size * sizeof(TYPE));\
}\
\
void data_copy_vector##_##TYPE\
(const struct vector##_##TYPE* const from, struct vector##_##TYPE* to)\
{\
	for (size_t i = 0; i < from->size; ++i)\
	{\
		*to->at(to, i) = *from->at(from, i);\
	}	\
}\
\
TYPE* at_vector##_##TYPE\
(const struct vector##_##TYPE * const this, const size_t index)\
{\
	if (index >= this->size)\
	{\
		return NULL;\
	}\
	return &this->data[index];\
}\
\
int push_back_vector##_##TYPE\
(struct vector##_##TYPE* const this, TYPE value)\
{\
	if (this->capacity >= this->size)\
	{\
		data_double_capacity##_##TYPE(this);\
	}\
	this->data[this->size++] = value;\
	return 0;\
}\
\
\
struct vector##_##TYPE* copy_vector##_##TYPE\
(const struct vector##_##TYPE* const this)\
{\
	struct vector##_##TYPE* res = init_vector_##TYPE##_ptr(this->capacity);\
	res->size = this->size;\
	data_copy_vector##_##TYPE(this, res);\
	return res;\
}\
/*\
 * public definition section\
 */\
\
\
struct vector##_##TYPE init_vector##_##TYPE\
(size_t size)\
{\
	struct vector##_##TYPE result;\
	result.size = size;\
	result.capacity = size;\
	result.data = data_alloc_vector##_##TYPE(size);\
	result.at = &at_vector##_##TYPE;\
	result.copy = &copy_vector##_##TYPE;\
	result.push_back = &push_back_vector##_##TYPE;\
	return result;\
}\
\
struct vector##_##TYPE* init_vector_##TYPE##_ptr\
(size_t size)\
{\
	struct vector##_##TYPE* res = \
		(struct vector##_##TYPE*) malloc(sizeof(struct vector##_##TYPE));\
	*res = init_vector##_##TYPE(size);\
	return res;\
}\
\
void delete_vector##_##TYPE\
(struct vector##_##TYPE* vect)\
{\
	free(vect->data);\
	free(vect);\
}\


/*
 * tests
 */

void test_macro_vector(void);
