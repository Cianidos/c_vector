// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "c_macro_vector.h"

#ifndef NDEBUG
DEFINE_VECTOR_OF(int)

/*
 * tests
 */

#include <assert.h>

void test_vector_int_at(void)
{
	struct vector_int v = init_vector_int(5);
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*v.at(&v, i) = expected[i];
	}
	for (int i = 0; i < 5; ++i)
	{
		assert(*v.at(&v, i) == expected[i]);
	}
	assert(v.at(&v, 10) == NULL);
}

void test_vector_int_init(void)
{
	struct vector_int a = init_vector_int(20);
	assert(a.size == 20);
	assert(a.capacity == 20);

	struct vector_int* b = init_vector_int_ptr(20);
	assert(b->size == 20);
	assert(b->capacity == 20);
	free(b);
}

void test_vector_int_push_back(void)
{
	struct vector_int v = init_vector_int(0);
	v.push_back(&v, 2);
	assert(*v.at(&v, 0) == 2);
	v.push_back(&v, 7);
	assert(*v.at(&v, 1) == 7);
	v.push_back(&v, 100);
	assert(*v.at(&v, 2) == 100);
	v.push_back(&v, 1000);
	assert(*v.at(&v, 3) == 1000);
	v.push_back(&v, 10000);
	assert(*v.at(&v, 4) == 10000);

	assert(*v.at(&v, 0) == 2);
	assert(*v.at(&v, 1) == 7);
	assert(*v.at(&v, 2) == 100);
	assert(*v.at(&v, 3) == 1000);
	assert(*v.at(&v, 4) == 10000);
}

void test_vector_int_copy(void)
{
	struct vector_int v = init_vector_int(5);
	int expected[5] = { 1, 3, 2, 4, 5 };
	for (int i = 0; i < 5; ++i)
	{
		*v.at(&v, i) = expected[i];
	}

	struct vector_int* v2 = v.copy(&v);

	assert(v.data != v2->data);
	assert(v.size == v2->size);
	assert(v.capacity == v2->capacity);

	for (int i = 0; i < 5; ++i)
	{
		assert(*v.at(&v, i) == *v2->at(v2, i));
	}
	free(v2);
}

void test_macro_vector(void)
{
	test_vector_int_at();
	test_vector_int_init();
	test_vector_int_push_back();
	test_vector_int_copy();
}
#else

test_macro_vector(void)

#endif

